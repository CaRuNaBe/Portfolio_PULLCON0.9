/*****************************************************************//**
 * \file   scripts_string.h
 * \brief  std::string �ɑ΂��Ẵ��[�e�B���e�B������`
 *
 *
 * \author �^���搶
 * \date   August 2022
 *********************************************************************/
#pragma once

#include <vector>
#include <string>

namespace string
{
  bool ToInt(const std::string& str,int& integer);

  bool ToFloat(const std::string& str,float& floatnum);

  std::vector<std::string> Split(const std::string& str,const std::string& delimiter);

  std::string Combine(std::vector<std::string>& script,const std::string& delimiter);
}