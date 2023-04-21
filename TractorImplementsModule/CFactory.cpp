#include "CFactory.h"

using namespace NFactory;

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