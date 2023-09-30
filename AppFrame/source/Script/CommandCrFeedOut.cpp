/*****************************************************************//**
 * @file   CommandCrFeedout.cpp
 * @brief  'CrFeedout' �X�N���v�g����������N���X����
 *
 *
 * @author ���������Y
 * @date   August 2022
 *********************************************************************/
#include "CommandCrFeedOut.h"
#include "ScriptsString.h"

namespace
{
  constexpr size_t SCRIPT_NUM = 5;
}

CommandCrFeedOut::CommandCrFeedOut(unsigned int line,const std::vector<std::string>& script)
  : CommandBase(line,script)
{
  out_count = 0;
  out_red = 0;
  out_green = 0;
  out_blue = 0;
}

bool CommandCrFeedOut::Check()
{
  const auto size = script.size();

  if( size != SCRIPT_NUM )
  {
    return false;
  }

  auto value = 0;

  if( !string::ToInt(script[1],value) )
  {
    return false;
  }

  out_count = value;

  if( !string::ToInt(script[2],value) )
  {
    return false;
  }

  out_red = value;

  if( !string::ToInt(script[3],value) )
  {
    return false;
  }

  out_green = value;

  if( !string::ToInt(script[4],value) )
  {
    return false;
  }

  out_blue = value;
  return true;
}
