#ifndef CPLANTER_H
#define CPLANTER_H

#include "CImplement.h"

namespace NImplement
{
  class CPlanter : public CImplement
  {
  public:

    CPlanter() {};
    CPlanter(const NComm::EChannelType& channelType, const void* channelProp) {};
    ~CPlanter() = default;

    // May add additional functionality for the
    // implement.
  };
}

#endif // !CPLANTER_H