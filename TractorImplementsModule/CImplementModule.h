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
    CImplementModule() {};
    ~CImplementModule() {};

    CImplement* addImplement(const EImplement& implement,
      const NComm::EChannelType& channelType,
      const void* channelProp)
    {
      // Add implements to module
      return (NFactory::CFactory().createImplement(implement, channelType, channelProp));
    }
  };
}

#endif // !CIMPLEMENTMODULE_H