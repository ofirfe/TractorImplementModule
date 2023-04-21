#include "CTcpChannel1.h"

using namespace NComm;

void CTcpChannel1::openCommChannel(const void* channelProp)
{
  const NComm::SEthChannelProp* ethProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
  // Set TCP/IP comm channel according to channelProp

  m_isChannelOpen = true;
}

bool CTcpChannel1::send(uint8_t* data, uint8_t size)
{
  // Send data and size using wrapper function for serial comm
  // according to the hardware available and relevant SERIAL COMM function.

  return true;
}

bool CTcpChannel1::receive(uint8_t* data, uint8_t size)
{
  // Receive data using relevant SERIAL COMM function
  // and update data and size received.

  return true;
}