#include "CPlatformInterface.h"

using namespace NPlatform;


//***********************************************************************
//* Function name : runPlatform                                         *
//* Purpose       : Run platform states                                 *
//***********************************************************************
void CPlatformInterface::runPlatform()
{
  switch (m_platformState)
  {
    case INIT:
    {
      // Channel type is initiated here but will be properly selected
      // on creation of the desired implement
      NComm::EChannelType channelType{ NComm::SERIAL };
      NImplement::EImplement implement = identifyImplement(channelType);
      uint8_t* channelProp = readPropFromConfig(implement);

      // Option of adding additional modules as needed
      m_implementModule1 = new NImplement::CImplementModule(implement, channelType, channelProp); 
      m_platformState = OPER;
      break;
    }
      
    case OPER:
    {
      // Add additional threads according to number of modules and functions for thos modules
      std::thread tModuleImplement1([this] {this->runImplementModule1(); });

      tModuleImplement1.join();
      break;
    }
    
    default:
      break;
  }
}

//***********************************************************************
//* Function name : runImplementModule1                                 *
//* Purpose       : Module1 operational function                        *
//***********************************************************************
void CPlatformInterface::runImplementModule1()
{
  bool endThread{ false };

  while ((m_implementModule1->isChannelOpen()) && (!endThread))
  {
    // Receive cycle
    auto lowFuelLevel = m_implementModule1->checkFuelLevelLow();
    auto isOn = m_implementModule1->checkImplementOn();
    auto currentCommads1 = getPlatformCommands1();

    // Logic cycle
    // If fuel level is low turn off implement
    if (lowFuelLevel)
    {
      m_implementModule1->turnImplementOff();
      endThread = true;
    }

    if ((currentCommads1->turnOn != m_prevImplementCommands1.turnOn) &&
      (!isOn))
    {
      // Turn implement on
      if (currentCommads1->turnOn == 1)
      {
        m_implementModule1->turnImplementOn();
      }
    }

    if ((currentCommads1->turnOff != m_prevImplementCommands1.turnOff) &&
      (isOn))
    {
      // Turn implement off
      if (currentCommads1->turnOff == 1)
      {
        m_implementModule1->turnImplementOff();
        endThread = true;
      }
    }

    m_prevImplementCommands1 = *currentCommads1;

    //Send cycle
    m_implementReport1.fuelLevel = m_implementModule1->getFuelLevel();
    m_implementReport1.isOn = isOn;

    sendPlatformReport1(m_implementReport1);

    if (!endThread)
    {
      std::this_thread::sleep_for(PLATFORM_MODULE1_RATE);
    }
  }
}

//***********************************************************************
//* Function name : getPlaformCommands1                                 *
//* Purpose       : Get operation commands for Implement Module 1       *
//***********************************************************************
const SImplementCommand* CPlatformInterface::getPlatformCommands1()
{
  SImplementCommand* newCommands = new SImplementCommand;

  // Read new commands for Implement1

  return newCommands;
}