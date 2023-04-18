#ifndef COMM_H
#define COMM_H

namespace NComm
{
  enum EChannelType
  {
    SERIAL,
    UDP,
    TCP
  };

  class CComm
  {
    CComm() {};
    ~CComm() {};

    virtual CComm* createCommChannel(const void* channelProp) = 0;
    virtual bool send(uint8_t* data, uint8_t size) = 0;
    virtual bool receive(uint8_t* data, uint8_t size) = 0;
    bool initChannel
    const EChannelType& getChannelType() { return m_channelType; };

  private:

    EChannelType m_channelType;
  };
}
#endif