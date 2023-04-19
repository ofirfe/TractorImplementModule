#ifndef CPLOW_H
#define CPLOW_H

#include "CImplement.h"

namespace NImplement
{
  class CPlow : public CImplement
  {
  public:

    CPlow() {};
    CPlow(const NComm::EChannelType& channelType, const void* channelProp) {};
    ~CPlow() = default;

    // May add additional functionality for the
    // implement.
  };
}

#endif // !CPLOW_H
