#ifndef CSERIALCHANNEL1_H
#define CSERIALCHANNEL1_H

#include "CComm.h"
#include "stdint.h"

namespace NComm
{
  class CSerialChannel1 : public CComm
  {
  public:
    CSerialChannel1();
    ~CSerialChannel1() {};
   
    virtual CComm* initCommChannel(const void* channelProp);
    virtual bool send(uint8_t* data, uint8_t size);
    virtual bool receive(uint8_t* data, uint8_t size);
  };
}

#endif // !CSERIALCHANNEL1_H