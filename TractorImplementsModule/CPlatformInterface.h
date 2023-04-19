#ifndef CPLATFORMINTERFACE_H
#define CPLATFORMINTERFACE_H

#include <stdint.h>
#include "CComm.h"
#include "CImplementModule.h"

namespace NPlatform
{
  enum EPlatformState
  {
    INIT,
    OPER
  };

  class CPlatformInterface
  {
  public:

    CPlatformInterface() : m_platformState{ INIT },
      m_implementModule{nullptr}
    {};
    ~CPlatformInterface() {};

    // Function that identifies the Implement connected 
    NImplement::EImplement identifyImplement(NComm::EChannelType& channelType) { };

    // Function that reads channel properties according to type (identified above)
    // from configuration file.
    // The function returns a pointer to the channel properties.
    // The properties need to be red according to their type.
    uint8_t* readPropFromConfig(NImplement::EImplement& implement) {};

    void runPlatform();

   private:
    EPlatformState m_platformState;
    NImplement::CImplementModule* m_implementModule;
  };
}

#endif // !CPLATFORMINTERFACE_H