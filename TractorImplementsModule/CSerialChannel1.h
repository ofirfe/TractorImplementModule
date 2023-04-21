#ifndef CSERIALCHANNEL1_H
#define CSERIALCHANNEL1_H

#include "CComm.h"
#include "stdint.h"

namespace NComm
{
  class CSerialChannel1 : public CComm
  {
  public:
    CSerialChannel1() : CComm() {};
    ~CSerialChannel1() = default;
   
    virtual bool send(uint8_t* data, uint8_t size);
    virtual bool receive(uint8_t* data, uint8_t size);
    virtual void openCommChannel(const void* channelProp);

  private:
    
  };
}

#endif // !CSERIALCHANNEL1_H