#include "CUdpChannel1.h"

using namespace NComm;

CComm* CUdpChannel1::initCommChannel(const void* channelProp)
{
  const NComm::SEthChannelProp* ethProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
  // Set UDP comm channel according to channelProp

  CComm* pChannel = new CUdpChannel1;
  return pChannel;
}

bool CUdpChannel1::send(uint8_t* data, uint8_t size)
{
  // Send data and size using wrapper function for serial comm
  // according to the hardware available and relevant SERIAL COMM function.

  return true;
}

bool CUdpChannel1::receive(uint8_t* data, uint8_t size)
{
  // Receive data using relevant SERIAL COMM function
  // and update data and size received.

  return true;
}