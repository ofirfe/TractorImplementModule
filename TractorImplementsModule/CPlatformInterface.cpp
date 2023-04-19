#include "CPlatformInterface.h"

using namespace NPlatform;

CPlatformInterface::CPlatformInterface() : m_platformState{ INIT },
m_implement{NImplement::PLOW},
m_channelType{NComm::SERIAL}
{

}

void CPlatformInterface::runPlatform()
{
  switch (m_platformState)
  {
    case INIT:
    {
      NComm::EChannelType channelType{ NComm::SERIAL };
      NImplement::EImplement implement = identifyImplement(channelType);
      uint8_t* channelProp = readPropFromConfig(implement);
      m_implementModule = NFactory::CFactory().createImplementModule(implement, channelType, channelProp); 
      m_platformState = OPER;
      
      break;
    }
      
    case OPER:
      break;
    
    default:
      break;
  }
}