#ifndef CIMPLEMENT_H
#define CIMPLEMENT_H

#include <stdint.h>
#include <thread>
#include <chrono>
#include "CComm.h"

namespace NImplement
{
  static const uint32_t MIN_FUEL_LEVEL = 10;  // Percentage
  static const uint32_t MAX_FUEL_LEVEL = 15; // Percentage
  static const uint32_t IMPLEMENT_RATE = 6; //Seconds

  enum EImplement
  {
    PLOW,
    PLANTER,
    BLADE
  };

  struct SCmdMsg
  {
    SCmdMsg() : turnOn{ false },
      turnOff{ false }
    {}

    void clear()
    {
      turnOn = false;
      turnOff = false;
    }

    bool turnOn;
    bool turnOff;
  };

  struct SRptMsg
  {
    SRptMsg() : isOn{false},
      fuelLevel{0}
    {}

    void clear()
    {
      isOn = false;
      fuelLevel = 0;
    }

    bool isOn;
    uint32_t fuelLevel;
  };

  class CImplement
  {
  public:
    CImplement() : m_cmdMsg{ new SCmdMsg }, m_rptMsg{ new SRptMsg }, m_commChannel{nullptr} {};
    CImplement(const NComm::EChannelType& channelType, const void* channelProp);
    virtual ~CImplement() 
    { 
      delete m_cmdMsg;
      delete m_rptMsg;
      delete m_commChannel; 
    };

    void activateImplement() { m_cmdMsg->turnOn = true; m_rptMsg->isOn = true; };
    void deactivateImplement() { m_cmdMsg->turnOff = true; m_rptMsg->isOn = false; };
    bool checkFuelLevelLow() { return (m_rptMsg->fuelLevel < MIN_FUEL_LEVEL) ? true : false; }
    bool checkImplementOn() { return m_rptMsg->isOn; };
    uint32_t getFuelLevel() { return m_rptMsg->fuelLevel; };
    bool isChannelOpen() { return m_commChannel->isChannelOpen();};
    bool sendCmd();
    bool receiveRpt();
    void runImplement();

  protected:
    SCmdMsg* m_cmdMsg;
    SRptMsg* m_rptMsg;
    NComm::CComm* m_commChannel;
  };
}

#endif // !CIMPLEMENT_H