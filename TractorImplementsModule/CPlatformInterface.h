#ifndef CPLATFORMINTERFACE_H
#define CPLATFORMINTERFACE_H

#include <stdint.h>
//#include <thread>
//#include <chrono>

//#include "CComm.h"
#include "CImplementModule.h"

namespace NPlatform
{
  static const uint32_t IMPLEMENT_MODULE_RATE = 500; // mSec

  enum EPlatformState
  {
    INIT,
    OPER,
    COMPLETE
  };

  struct SImplementCommand
  {
    SImplementCommand() : turnOn{ false },
      turnOff{ false }
    {}

    bool turnOn;
    bool turnOff;
  };

  struct SImplementReport
  {
    SImplementReport() : isOn{ false },
      fuelLevel{ 0 }
    {}

    bool isOn;
    uint32_t fuelLevel;
  };

  class CPlatformInterface
  {
  public:
    CPlatformInterface() : m_platformState{ INIT },
      m_implementModule{nullptr},
      m_prevImplementCommands1(),
      m_implementReport1()
    {};
    ~CPlatformInterface() { delete m_implementModule; };

    void runPlatform();
    void runImplementModule1();

   private:
     // Function that identifies the Implement connected 
     NImplement::EImplement identifyImplement(NComm::EChannelType& channelType) { return NImplement::BLADE; };

     // Function that reads channel properties according to type (identified above)
     // from configuration file.
     // The function returns a pointer to the channel properties.
     // The properties need to be red according to their type.
     uint8_t* readPropFromConfig(NImplement::EImplement& implement) { return new uint8_t; };

     const SImplementCommand* getPlatformCommands1();
     void sendPlatformReport1(const SImplementReport& implementReport) { /* Send report implementReport */ };
     
     EPlatformState m_platformState;

     NImplement::CImplementModule* m_implementModule;

     // Option of adding commands for additional modules
     SImplementCommand m_prevImplementCommands1;

     // Option of adding reports for additional modules
     SImplementReport m_implementReport1;
  };
}

#endif // !CPLATFORMINTERFACE_H