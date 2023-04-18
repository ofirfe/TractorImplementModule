#ifndef CFACTORY_H
#define CFACTORY_H

#include "CUdpChannel1.h"
#include "CTcpChannel1.h"
#include "CSerialChannel1.h"

namespace NFactory
{
  class CFactory
  {
  public:
    CFactory() = default;
    ~CFactory() {};

    NComm::CComm* const createCommChannel(NComm::EChannelType& channelType, void* channelProp);
  };
}

#endif // !CFACTORY_H

