#include "CImplement.h"

using namespace NImplement;

bool CImplement::sendCmd()
{
  bool rv{ false };

  if (m_commChannel->send(reinterpret_cast<uint8_t*>(m_cmdMsg), sizeof(SCmdMsg)))
  {
    m_cmdMsg->clear();
    rv = true;
  }

  return rv;
};

bool CImplement::receiveRpt()
{
  bool rv{ false };

  uint8_t* pData{ nullptr };
  uint8_t receievedLength{ 0 };

  if (m_commChannel->receive(pData, receievedLength))
  {
    m_rptMsg = reinterpret_cast<SRptMsg*>(pData);
    rv = true;
  }

  return rv;
}