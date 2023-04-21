#ifndef CFACTORY_H
#define CFACTORY_H


#include "CBlade.h"
#include "CPlanter.h"
#include "CPlow.h"

namespace NFactory
{
  class CFactory
  {
  public:
    CFactory() {};
    ~CFactory() {};

    static NImplement::CImplement* createImplement(const NImplement::EImplement& implement, 
                                                  const NComm::EChannelType& channelType, 
                                                  const void* channelProp);
  };
}

#endif // !CFACTORY_H

