#ifndef CPLATFORMINTERFACE_H
#define CPLATFORMINTERFACE_H

#include <stdint.h>
#include "CComm.h"

namespace NPlatform
{
  class CPlatformInterface
  {
  public:

    CPlatformInterface() {};
    ~CPlatformInterface() {};

    // Function that identifies the channel type of the Implement connected 
    NComm::EChannelType identifyChannelType() { };

    // Function that reads channel properties according to type (identified above)
    // from configuration file.
    // The function returns a pointer to the channel properties.
    // The properties need to be red according to their type.
    uint8_t* readPropFromConfig(NComm::EChannelType& channelType) {};

    void runPlatform();
  };
}

#endif // !CPLATFORMINTERFACE_H