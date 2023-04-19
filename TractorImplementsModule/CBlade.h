#ifndef CBLADE_H
#define CBLADE_H

#include "CImplement.h"

namespace NImplement
{
  class CBlade : public CImplement
  {
  public:
    CBlade() {};
    CBlade(const NComm::EChannelType& channelType, const void* channelProp) {};
    ~CBlade() = default;

    // May add additional functionality for the
    // implement.
  };
}

#endif // !CBLADE_H
