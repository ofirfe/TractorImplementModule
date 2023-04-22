#include "CImplement.h"
#include "CUdpChannel1.h"
#include "CTcpChannel1.h"
#include "CSerialChannel1.h"
#include <mutex>

using namespace NImplement;

CImplement::CImplement(const NComm::EChannelType& channelType, const void* channelProp) : m_cmdMsg{ new SCmdMsg },
m_rptMsg{ new SRptMsg },
m_commChannel{ nullptr }
{
  switch (channelType)
  {
  case NComm::SERIAL:
  {
    const NComm::SSerialChannelProp* pSerialChannelProp = reinterpret_cast<const NComm::SSerialChannelProp*>(channelProp);
    NComm::CSerialChannel1* pSerialChannel1 = new NComm::CSerialChannel1;
    pSerialChannel1->openCommChannel(pSerialChannelProp);
    m_commChannel = pSerialChannel1;
    break;
  }

  case NComm::UDP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CUdpChannel1* pUdpChannel = new NComm::CUdpChannel1;
    pUdpChannel->openCommChannel(pEthChannelProp);
    m_commChannel = pUdpChannel;
    break;
  }

  case NComm::TCP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CTcpChannel1* pTcpChannel = new NComm::CTcpChannel1;
    pTcpChannel->openCommChannel(pEthChannelProp);
    m_commChannel = pTcpChannel;
    break;
  }

  default:
    break;
  }
}

void CImplement::runImplement()
{
  std::mutex l;

  l.lock();
  m_rptMsg->fuelLevel = MAX_FUEL_LEVEL;
  l.unlock();

  auto fFuel = [this, &l]() -> bool
  {
    bool rv{ false };
    l.lock();
    ((m_rptMsg->fuelLevel > 0) && (m_rptMsg->isOn)) ? rv = true : rv = false;
    l.unlock();
    return rv;
  };

  auto fOn = [this, &l]() -> bool
  {
    bool rv{ false };
    l.lock();
    (m_rptMsg->isOn) ? rv = true : rv = false;
    l.unlock();
    return rv;
  };

  // Wait for power on
  while (!fOn())
  {
    std::this_thread::sleep_for(std::chrono::seconds(IMPLEMENT_RATE));
  }

  while (fFuel())
  {
    //Receive cycle
    receiveRpt();

    // Logic cycle
    l.lock();
    --m_rptMsg->fuelLevel;
    l.unlock();

    //Send Commnads
    sendCmd();

    std::this_thread::sleep_for(std::chrono::seconds(IMPLEMENT_RATE));
  }
}

bool CImplement::sendCmd()
{
  bool rv{ false };

  if (m_commChannel->send(reinterpret_cast<uint8_t*>(m_cmdMsg), sizeof(SCmdMsg)))
  {
    m_cmdMsg->clear();
    rv = true;
  }

  return rv;
};

bool CImplement::receiveRpt()
{
  bool rv{ false };

  uint8_t* pData{ nullptr };
  uint8_t receievedLength{ 0 };

  if (m_commChannel->receive(pData, receievedLength))
  {
    //Markered out because receiev is an API
    //m_rptMsg = reinterpret_cast<SRptMsg*>(pData);
    rv = true;
  }

  return rv;
}