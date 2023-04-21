#include "CSerialChannel1.h"

using namespace NComm;

CComm* CSerialChannel1::openCommChannel(const void* channelProp)
{
  const NComm::SSerialChannelProp* serialProp = reinterpret_cast<const NComm::SSerialChannelProp*>(channelProp);
  // Set SERIAL comm channel according to channelProp

  // If openening channel was successful return pointer and update m_isOpenChannel
  // otherwise return nullptr
  CComm* pChannel = new CSerialChannel1;
  m_isChannelOpen = true;
  return pChannel;
}

bool CSerialChannel1::send(uint8_t* data, uint8_t size)
{
  // Send data and size using wrapper function for serial comm
  // according to the hardware available and relevant SERIAL COMM function.

  return true;
}

bool CSerialChannel1::receive(uint8_t* data, uint8_t size)
{
  // Receive data using relevant SERIAL COMM function
  // and update data and size received.

  return true;
}