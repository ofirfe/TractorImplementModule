#include "CPlatformInterface.h"
#include <iostream>

using namespace NPlatform;


//***********************************************************************
//* Function name : runPlatform                                         *
//* Purpose       : Run platform states                                 *
//***********************************************************************
void CPlatformInterface::runPlatform()
{
  while (m_platformState != COMPLETE)
  {
    switch (m_platformState)
    {
    case INIT:
    {
      m_implementModule = new NImplement::CImplementModule();

      // Channel type is initiated here but will be properly selected
      // on creation of the desired implement
      NComm::EChannelType channelType{ NComm::SERIAL };
      NImplement::EImplement implement = identifyImplement(channelType);
      uint8_t* channelProp = readPropFromConfig(implement);
      
      // Option of adding additional implements as needed
      m_pImplement1 = m_implementModule->addImplement(implement, channelType, channelProp);
      m_platformState = OPER;
      break;
    }

    case OPER:
    {
      // Implement operation and simualate fuel usage
      std::thread tImplement([this] {m_pImplement1->runImplement(); });

      // Add additional threads according to number of implements and functions for them
      std::thread tModuleImplement1([this] {this->runImplementModule1(); });

      tImplement.join();
      tModuleImplement1.join();
      m_platformState = COMPLETE;
      
      break;
    }

    default:
      break;
    }
  }

  std::cout << "Implement Module shutting down..." << std::endl;
}

//***********************************************************************
//* Function name : runImplementModule1                                 *
//* Purpose       : Module1 operational function                        *
//***********************************************************************
void CPlatformInterface::runImplementModule1()
{
  bool endThread{ false };
  std::this_thread::sleep_for(std::chrono::seconds(5));

  while ((m_pImplement1->isChannelOpen()) && (!endThread))
  {
    // Receive cycle
    auto lowFuelLevel = m_pImplement1->checkFuelLevelLow();
    auto isOn = m_pImplement1->checkImplementOn();
    auto currentCommads1 = getPlatformCommands1();

    // Logic cycle
    // If fuel level is low turn off implement
    if (lowFuelLevel)
    {
      std::cout << "Fuel Low! - Implement auto shutdown procedure" << std::endl;
      m_pImplement1->deactivateImplement();
      endThread = true;
    }

    if ((currentCommads1->turnOn != m_prevImplementCommands1.turnOn) &&
      (!isOn))
    {
      // Turn implement on
      if (currentCommads1->turnOn == 1)
      {
        std::cout << "Implement On" << std::endl;
        m_pImplement1->activateImplement();
      }
    }

    if ((currentCommads1->turnOff != m_prevImplementCommands1.turnOff) &&
      (isOn))
    {
      // Turn implement off
      if (currentCommads1->turnOff == 1)
      {
        std::cout << "Implement Off" << std::endl;
        m_pImplement1->deactivateImplement();
        endThread = true;
      }
    }

    m_prevImplementCommands1 = *currentCommads1;

    //Send cycle
    //Send commands to Implement
    m_implementReport1.fuelLevel = m_pImplement1->getFuelLevel();
    m_implementReport1.isOn = isOn;

    // Send report to operator
    sendPlatformReport1(m_implementReport1);

    std::cout << "Fuel Level: " << m_implementReport1.fuelLevel <<
      " Is implement on: " << ((m_implementReport1.isOn) ? "Yes" : "No") << std::endl;

    if (!endThread)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(IMPLEMENT_MODULE_RATE));
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