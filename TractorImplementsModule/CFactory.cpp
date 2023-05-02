#include "CFactory.h"

using namespace NFactory;

//***********************************************************************
//* Function name : createImplement                                     *
//* Purpose       : Create implement object and return pointer          *
//***********************************************************************
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

//***********************************************************************
//* Function name : createCommChannel                                   *
//* Purpose       : Create comm channel object and return pointer       *
//***********************************************************************
NComm::CComm* CFactory::createCommChannel(const NComm::EChannelType& channelType, const void* channelProp)
{
  NComm::CComm* rv{ nullptr };

  switch (channelType)
  {
  case NComm::SERIAL:
  {
    const NComm::SSerialChannelProp* pSerialChannelProp = reinterpret_cast<const NComm::SSerialChannelProp*>(channelProp);
    NComm::CSerialChannel1* pSerialChannel1 = new NComm::CSerialChannel1;
    pSerialChannel1->openCommChannel(pSerialChannelProp);
    rv = pSerialChannel1;
    break;
  }

  case NComm::UDP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CUdpChannel1* pUdpChannel = new NComm::CUdpChannel1;
    pUdpChannel->openCommChannel(pEthChannelProp);
    rv = pUdpChannel;
    break;
  }

  case NComm::TCP:
  {
    const NComm::SEthChannelProp* pEthChannelProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
    NComm::CTcpChannel1* pTcpChannel = new NComm::CTcpChannel1;
    pTcpChannel->openCommChannel(pEthChannelProp);
    rv = pTcpChannel;
    break;
  }

  default:
    break;
  }

  return rv;
}