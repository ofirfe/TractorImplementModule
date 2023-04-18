#ifndef CTCPCHANNEL1_H
#define CTCPCHANNEL1_H

#include "CComm.h"

namespace NComm
{
  class CTcpChannel1 : public CComm
  {
  public:
    CTcpChannel1();
    ~CTcpChannel1() {};
   
    virtual CComm* initCommChannel(const void* channelProp);
    virtual bool send(uint8_t* data, uint8_t size);
    virtual bool receive(uint8_t* data, uint8_t size);
  };
}

#endif // !CTCPCHANNEL1_H