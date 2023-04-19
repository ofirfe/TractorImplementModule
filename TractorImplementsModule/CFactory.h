#ifndef CFACTORY_H
#define CFACTORY_H

#include "CUdpChannel1.h"
#include "CTcpChannel1.h"
#include "CSerialChannel1.h"
#include "CBlade.h"
#include "CPlanter.h"
#include "CPlow.h"
#include "CImplementModule.h"

namespace NFactory
{
  class CFactory
  {
  public:
    CFactory() {};
    ~CFactory() {};

    static NComm::CComm* createCommChannel(const NComm::EChannelType& channelType, const void* channelProp);
    static NImplement::CImplement* createImplement(const NImplement::EImplement& implement, 
                                                  const NComm::EChannelType& channelType, 
                                                  const void* channelProp);
    static NImplement::CImplementModule* createImplementModule(const NImplement::EImplement& implement,
                                                              const NComm::EChannelType& channelType, 
                                                              const void* channelProp);
 
  };
}

#endif // !CFACTORY_H

