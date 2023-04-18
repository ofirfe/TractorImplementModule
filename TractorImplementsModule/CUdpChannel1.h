#ifndef UDPCHANNEL1_H
#define UDPCHANNEL1_H

#include "CComm.h"

namespace NComm
{
  class CUdpChannel1 : public CComm
  {
  public:
    CUdpChannel1() {};
    ~CUdpChannel1() {};
   
    virtual CComm* initCommChannel(const void* channelProp);
    virtual bool send(uint8_t* data, uint8_t size);
    virtual bool receive(uint8_t* data, uint8_t size);
  };
}

#endif