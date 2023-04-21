#ifndef CPLATFORMINTERFACE_H
#define CPLATFORMINTERFACE_H

#include <stdint.h>
#include <thread>
#include <chrono>

#include "CComm.h"
#include "CImplementModule.h"

namespace NPlatform
{
  using std::chrono::operator""ms;
  static const std::chrono::milliseconds PLATFORM_MODULE1_RATE = 16ms;

  enum EPlatformState
  {
    INIT,
    OPER
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
      m_implementModule1{nullptr},
      m_prevImplementCommands1(),
      m_implementReport1()
    {};
    ~CPlatformInterface() { delete m_implementModule1; };

    static void runPlatform();

   private:
     // Function that identifies the Implement connected 
     NImplement::EImplement identifyImplement(NComm::EChannelType& channelType) { };

     // Function that reads channel properties according to type (identified above)
     // from configuration file.
     // The function returns a pointer to the channel properties.
     // The properties need to be red according to their type.
     uint8_t* readPropFromConfig(NImplement::EImplement& implement) {};

     const SImplementCommand& getPlatformCommands1();
     void sendPlatformReport1(const SImplementReport& implementReport) { /* Send report implementReport */ };
     void runImplementModule1();
     auto now() { return std::chrono::steady_clock::now(); }
     auto awake_time() {
       using std::chrono::operator""ms;
       return now() + PLATFORM_MODULE1_RATE;
      }
      EPlatformState m_platformState;
    
      // Option of adding additional modules as needed
      NImplement::CImplementModule* m_implementModule1;

      // Option of adding commands for additional modules
      SImplementCommand m_prevImplementCommands1;

      // Option of adding reports for additional modules
      SImplementReport m_implementReport1;
  };
}

#endif // !CPLATFORMINTERFACE_H