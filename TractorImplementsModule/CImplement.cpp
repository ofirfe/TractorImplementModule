#include "CImplement.h"
#include "CUdpChannel1.h"
#include "CTcpChannel1.h"
#include "CSerialChannel1.h"

using namespace NImplement;

CImplement::CImplement(const NComm::EChannelType& channelType, const void* channelProp) : m_cmdMsg(new SCmdMsg),
m_rptMsg(new SRptMsg),
m_commChannel(nullptr)
{
  switch (channelType)
  {
  case NComm::SERIAL:
  {
    const NComm::SSerialChannelProp* pSerialChannelProp = reinterpret_cast<const NComm::SSerialChannelProp*>(channelProp);
    NComm::CSerialChannel1 pSerialChannel1;
    m_commChannel = pSerialChannel1.openCommChannel(pSerialChannelProp);
    break;
  }

  case NComm::UDP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CUdpChannel1 pUdpChannel;
    m_commChannel = pUdpChannel.openCommChannel(pEthChannelProp);
    break;
  }

  case NComm::TCP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CTcpChannel1 pTcpChannel;
    m_commChannel = pTcpChannel.openCommChannel(pEthChannelProp);
    break;
  }

  default:
    break;
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
    m_rptMsg = reinterpret_cast<SRptMsg*>(pData);
    rv = true;
  }

  return rv;
}