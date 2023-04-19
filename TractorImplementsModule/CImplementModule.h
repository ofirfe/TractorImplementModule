#ifndef CIMPLEMENTMODULE_H
#define CIMPLEMENTMODULE_H

#include "CImplement.h"
#include "CFactory.h"

namespace NImplement
{
  class CImplementModule
  {
  public:
    CImplementModule() {};
    CImplementModule(const EImplement& implement, const NComm::EChannelType& channelType, const void* channelProp) : m_implement{ nullptr }
    {
      m_implement = NFactory::CFactory().createImplement(implement, channelType, channelProp);
    };

    ~CImplementModule()
    { 
      delete m_implement; 
    };

    void turnImplementOn() { m_implement->activateImplement(); };
    void trunImplementOff() { m_implement->deactivateImplement(); };
    bool checkFuelLevelLow() { return m_implement->checkFuelLevelLow(); };
    bool checkImplementOn() { return m_implement->checkImplementOn(); };

  private:
    CImplement* m_implement;
  };
}

#endif // !CIMPLEMENTMODULE_H