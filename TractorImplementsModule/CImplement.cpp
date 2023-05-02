#include <mutex>
#include "CFactory.h"

using namespace NImplement;

//***********************************************************************
//* Function name : CImplement                                          *
//* Purpose       : Constructor                                         *
//***********************************************************************
CImplement::CImplement(const NComm::EChannelType& channelType, const void* channelProp) : m_cmdMsg{ new SCmdMsg },
m_rptMsg{ new SRptMsg },
m_commChannel{ nullptr }
{
  m_commChannel = NFactory::CFactory::createCommChannel(channelType, channelProp);
}

//***********************************************************************
//* Function name : checkFuelLevelLow                                   *
//* Purpose       : Check if fuel level is lower than minimum required  *
//***********************************************************************
bool CImplement::checkFuelLevelLow()
{
  auto fLowFuel = [this]()->bool
  {
    bool rv{ false };

    m_l.lock();
    rv = (m_rptMsg->fuelLevel < MIN_FUEL_LEVEL) ? true : false;
    m_l.unlock();

    return rv;
  };

  return fLowFuel();
}

//***********************************************************************
//* Function name : runImplement                                        *
//* Purpose       : Operational thread function for implement           *
//***********************************************************************
void CImplement::runImplement()
{
  m_l.lock();
  m_rptMsg->fuelLevel = MAX_FUEL_LEVEL;
  m_l.unlock();

  // Function created to allow mutex lock operation.
  // The function is the condition for the fuel level check.
  auto fFuel = [this]() -> bool
  {
    bool rv{ false };
    m_l.lock();
    rv = ((m_rptMsg->fuelLevel > 0) && (m_rptMsg->isOn)) ? true : false;
    m_l.unlock();
    return rv;
  };

  // Function created to allow mutex lock operation.
  // The function checks if implement is on.
  auto fOn = [this]() -> bool
  {
    bool rv{ false };
    m_l.lock();
    rv = (m_rptMsg->isOn) ? true : false;
    m_l.unlock();
    return rv;
  };

  // Wait for power on
  while (!fOn())
  {
    std::this_thread::sleep_for(std::chrono::seconds(IMPLEMENT_RATE));
  }

  while (fFuel())
  {
    //Receive cycle
    receiveRpt();

    // Logic cycle
    m_l.lock();
    --m_rptMsg->fuelLevel;
    m_l.unlock();

    //Send Commnads
    sendCmd();

    std::this_thread::sleep_for(std::chrono::seconds(IMPLEMENT_RATE));
  }
}

//***********************************************************************
//* Function name : sendCmd                                             *
//* Purpose       : Dummy function for sending commands to implement    *
//***********************************************************************
bool CImplement::sendCmd()
{
  bool rv{ false };

  if (m_commChannel->send(reinterpret_cast<uint8_t*>(m_cmdMsg), sizeof(SCmdMsg)))
  {
    m_cmdMsg->clear();
    rv = true;
  }

  // Error handling: If no data receieved or bad message return false
  return rv;
};

//***********************************************************************
//* Function name : receiveRpt                                          *
//* Purpose       : Dummy function for receiving reports from implement *
//***********************************************************************
bool CImplement::receiveRpt()
{
  bool rv{ false };

  uint8_t* pData{ nullptr };
  uint8_t receievedLength{ 0 };

  if (m_commChannel->receive(pData, receievedLength))
  {
    //Markered out because receiev is an API
    //m_rptMsg = reinterpret_cast<SRptMsg*>(pData);

    // Error handling: If no data receieved or bad message return false
    rv = true;
  }

  return rv;
}