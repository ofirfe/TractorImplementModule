#ifndef CIMPLEMENTMODULE_H
#define CIMPLEMENTMODULE_H

#include <thread>
#include <chrono>
#include "CImplement.h"
#include "CFactory.h"
#include "CComm.h"

namespace NImplement
{
  class CImplementModule
  {
  public:
    CImplementModule() : m_implement{ nullptr } {};
    ~CImplementModule()
    { 
      delete m_implement; 
    };

    void turnImplementOn() { m_implement->activateImplement(); };
    void turnImplementOff() { m_implement->deactivateImplement(); };
    bool checkFuelLevelLow() { return m_implement->checkFuelLevelLow(); };
    bool checkImplementOn() { return m_implement->checkImplementOn(); };
    bool isChannelOpen() { return m_implement->isChannelOpen(); };
    uint32_t getFuelLevel() { return m_implement->getFuelLevel(); };
    bool sendCommand() { return m_implement->sendCmd(); };
    bool receiveRpt() { return m_implement->receiveRpt(); };
    const auto runImplement() { return m_implement->runImplement(); };
    void addImplement(const EImplement& implement,
      const NComm::EChannelType& channelType,
      const void* channelProp)
    {
      // Add implements to module
      m_implement = NFactory::CFactory().createImplement(implement, channelType, channelProp);
    }
    
  private:
    CImplement* m_implement;
  };
}

#endif // !CIMPLEMENTMODULE_H