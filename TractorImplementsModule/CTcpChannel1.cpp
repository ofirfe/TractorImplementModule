#include "CTcpChannel1.h"

using namespace NComm;

//***********************************************************************
//* Function name : openCommChannel                                     *
//* Purpose       : Initialize and open communication channel           * 
//*                 for implement                                       *
//***********************************************************************
void CTcpChannel1::openCommChannel(const void* channelProp)
{
  const NComm::SEthChannelProp* ethProp = reinterpret_cast<const NComm::SEthChannelProp*>(channelProp);
  // Set TCP/IP comm channel according to channelProp

  // Error handling: If channel cannot be opened return false
  m_isChannelOpen = true;
}

//***********************************************************************
//* Function name : send                                                *
//* Purpose       : Send command message to implement - dummy API       *
//***********************************************************************
bool CTcpChannel1::send(uint8_t* data, uint8_t size)
{
  // Send data and size using wrapper function for serial comm
  // according to the hardware available and relevant SERIAL COMM function.

  // Error handling: If channel cannot be opened return false
  return true;
}

bool CTcpChannel1::receive(uint8_t* data, uint8_t size)
{
  // Receive data using relevant SERIAL COMM function
  // and update data and size received.

  // Error handling: If channel cannot be opened return false
  return true;
}