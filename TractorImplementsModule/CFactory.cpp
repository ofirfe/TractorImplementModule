#include "CFactory.h"

using namespace NFactory;

NComm::CComm* CFactory::createCommChannel(const NComm::EChannelType& channelType, const void* channelProp)
{
  NComm::CComm* pCommChannel {nullptr};

  switch (channelType)
  {
  case NComm::SERIAL:
  {
    const NComm::SSerialChannelProp* pSerialChannelProp = reinterpret_cast<const NComm::SSerialChannelProp*>(channelProp);
    NComm::CSerialChannel1 pSerialChannel1;
    pCommChannel = pSerialChannel1.initCommChannel(pSerialChannelProp);
    break;
  }

  case NComm::UDP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CUdpChannel1 pUdpChannel;
    pCommChannel = pUdpChannel.initCommChannel(pEthChannelProp);
    break;
  }

  case NComm::TCP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CTcpChannel1 pTcpChannel;
    pCommChannel = pTcpChannel.initCommChannel(pEthChannelProp);
    break;
  }

  default:
    break;
  }

  return pCommChannel;
}

NImplement::CImplement* CFactory::createImplement(const NImplement::EImplement& implement,
                                                  const NComm::EChannelType& channelType, 
                                                  const void* channelProp)
{
  NImplement::CImplement* pImplement{ nullptr };

  switch (implement)
  {
  case NImplement::BLADE:
  {
    pImplement = new NImplement::CBlade(channelType, channelProp);
    break;
  }

  case NImplement::PLOW:
  {
    pImplement = new NImplement::CPlow(channelType, channelProp);
    break;
  }

  case NImplement::PLANTER:
  {
    pImplement = new NImplement::CPlanter(channelType, channelProp);
    break;
  }

  default:
    break;
  }

  return pImplement;
}

NImplement::CImplementModule* CFactory::createImplementModule(const NImplement::EImplement& implement, 
                                                              const NComm::EChannelType& channelType, 
                                                              const void* channelProp)
{
  return (new NImplement::CImplementModule(implement, channelType, channelProp));
}