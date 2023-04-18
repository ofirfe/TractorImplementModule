#include "CFactory.h"

using namespace NFactory;

NComm::CComm* const CFactory::createCommChannel(NComm::EChannelType& channelType, void* channelProp)
{
  switch (channelType)
  {
  case NComm::SERIAL:
  {
    NComm::SSerialChannelProp* pSerialChannelProp = static_cast<NComm::SSerialChannelProp*>(channelProp);
    NComm::CSerialChannel1 pSerialChannel;
    NComm::CComm* pCommChannel = pSerialChannel.initCommChannel(pSerialChannelProp);
    break;
  }

  case NComm::UDP:
  {
    NComm::SEthChannelProp* pEthChannelProp = static_cast<NComm::SEthChannelProp*>(channelProp);
    NComm::CUdpChannel1 pUdpChannel;
    NComm::CComm* pCommChannel = pUdpChannel.initCommChannel(pEthChannelProp);
    break;
  }

  case NComm::TCP:
  {
    NComm::SEthChannelProp* pEthChannelProp = static_cast<NComm::SEthChannelProp*>(channelProp);
    NComm::CTcpChannel1 pTcpChannel;
    NComm::CComm* pCommChannel = pTcpChannel.initCommChannel(pEthChannelProp);
    break;
  }

  default:
    break;
  }
}