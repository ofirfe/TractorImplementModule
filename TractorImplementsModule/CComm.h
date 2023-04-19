#ifndef CCOMM_H
#define CCOMM_H

#include <stdint.h>
#include <string>

namespace NComm
{
  enum EChannelType
  {
    SERIAL,
    UDP,
    TCP
  };

  struct SSerialChannelProp
  {
    SSerialChannelProp(): comId{"None"},
      baudRate{ 0 },
      dataBits{ 0 },
      parity{ 0 },
      stopBits{ 0 }
    {};
    ~SSerialChannelProp() {};

    std::string comId;
    uint8_t baudRate;
    uint8_t dataBits;
    uint8_t parity;
    uint8_t stopBits;
  };

  struct SEthChannelProp
  {
    SEthChannelProp() : id{ "No ID" },
    hostIp{"0.0.0.0"},
    hostPort{0},
    localIp{ "0.0.0.0" },
    localPort{ 0 },
    multicast{ 0 }
    { };
    ~SEthChannelProp() {};

    std::string id;
    std::string hostIp;
    uint8_t hostPort;
    std::string localIp;
    uint8_t localPort;
    uint8_t multicast;
  };
  

  class CComm
  {
  public:
    CComm() : m_channelType{SERIAL} {};
    virtual ~CComm() {};

    virtual bool send(uint8_t* data, uint8_t size) = 0;
    virtual bool receive(uint8_t* data, uint8_t size) = 0;
    const EChannelType& getChannelType() { return m_channelType; };
    virtual CComm* initCommChannel(const void* channelProp) = 0;

  protected:
    EChannelType m_channelType;
  };
}
#endif