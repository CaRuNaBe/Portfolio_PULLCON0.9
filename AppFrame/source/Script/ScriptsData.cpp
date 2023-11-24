/*****************************************************************//**
 * \file   scripts_data.cpp
 * \brief  �X�N���v�g�̓ǂݍ��ݎ���
 *
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/

#include "ScriptsData.h"
#include "ScriptsString.h"
#include <windows.h>
#include <fstream>
#include "picojson.h"

namespace
{
  constexpr auto EMPTY_STR = _T("");
  constexpr auto EMPTY_WSTR = L"";
  constexpr auto DELIMITER = _T(",");
}
//!
//! @fn bool ScriptsData::LoadJson(const TCHAR* path)
//! @brief �X�N���v�g�p Json �t�@�C���̓Ǎ�
//! @param[in] path �p�X�t�̃X�N���v�g�p Json �t�@�C����
//! @return �����̐���
//! @details Json �t�@�C���� BOM ���� UTF-8 ��z�肵�Ă��܂��B
//! ��{�I�ɂ͕t���̃G�N�Z��(amg_scripts.xlsm)���o�͂���鎖��z�肵�Ă��܂��B
//! �{�v���W�F�N�g���g�p���Ă��� DX ���C�u�����̎w���
//! VisualStudio �̕����R�[�h�w��̓}���`�o�C�g�����ƂȂ��Ă���
//! �Ǎ����� Json(UTF-8) -> ���j�R�[�h(UTF-16) -> �}���`�o�C�g����
//! �̗l�ɕ����R�[�h�̕ϊ����s���܂��B
//!
bool ScriptsData::LoadJson(std::string filepath,std::string storyname,std::string filename)
{
  // UTF-8 BOM���� Json file
  std::ifstream ifs(filepath);
  if( scripts == nullptr )
  {
    scripts.reset(new std::vector<std::string>());
  }
  //�����Ȃ������ꍇ�V�K�쐬
  if( !ifs )
  {
    std::ofstream writing_file;
    writing_file.open(filename,std::ios::out);
    picojson::array datalist;

    picojson::object license;
    license.insert(std::make_pair(storyname,picojson::value(datalist)));

    picojson::array loot;
    loot.push_back(picojson::value(license));
    std::cout << picojson::value(loot) << std::endl;
    writing_file << picojson::value(loot).serialize() << std::endl;
    writing_file.close();
  } else
  {
    picojson::value json_value;

    ifs >> json_value;

    const auto& err = picojson::get_last_error();

    if( !err.empty() )
    {
      return false;
    }
    std::cout << picojson::value(json_value) << std::endl;
    auto& root = json_value.get<picojson::array>();
    auto& object = root[0].get<picojson::object>();
    const auto& array = object[storyname].get<picojson::array>();

    // UTF-8 -> Wide(UTF-16) -> MultiByte �ƕ����R�[�h��ϊ����Ȃ���X�N���v�g�������擾
    for( auto i = array.begin(); i != array.end(); ++i )
    {
      const auto& utf8 = (*i).get<std::string>();
      const auto utf16 = ConvertUTF8ToWide(utf8);
      const auto mbs = ConvertWideToMultiByte(utf16);

      scripts->emplace_back(mbs);
    }

  }
  ifs.close();
  return true;
}

bool ScriptsData::WriteJson(std::string newfilename,std::string storyname)
{
  std::ofstream writing_file;
  writing_file.open(newfilename,std::ios::out);

  picojson::array datalist;
  for( auto i = scripts->begin(); i != scripts->end(); ++i )
  {
    const auto& mbs = *i;//�}���`�o�C�g�����擾
    const auto utf16 = ConvertMultiByteToWide(mbs);//�}���`�o�C�g��������UTF-16
    const auto utf8 = ConvertWideToUTF8(utf16);//utf-16����utf-8
    datalist.push_back(picojson::value(utf8));
  }

  picojson::object license;
  license.insert(std::make_pair(storyname,picojson::value(datalist)));

  picojson::array loot;
  loot.push_back(picojson::value(license));

  writing_file << picojson::value(loot).serialize() << std::endl;
  writing_file.close();
  return true;
}
//!
//! @fn std::wstring ScriptsData::ConvertUTF8ToWide(const std::string& utf8) const
//! @brief UTF-8 �����R�[�h�� std::string �� std::wstring(UTF-16) �ɕϊ�����
//! @param[in] utf8 UTF-8 �����R�[�h�� std::string
//! @return UTF-16 �����R�[�h�� std::wstring
//!
std::wstring ScriptsData::ConvertUTF8ToWide(const std::string& utf8) const
{
  if( utf8.empty() )
  {
    return EMPTY_WSTR;
  }

  const auto in_length = static_cast<int>(utf8.length());
  const auto out_length = MultiByteToWideChar(CP_UTF8,0,utf8.c_str(),in_length,0,0);

  if( out_length <= 0 )
  {
    return EMPTY_WSTR;
  }

  std::vector<wchar_t> buffer(out_length);

  MultiByteToWideChar(CP_UTF8,0,utf8.c_str(),in_length,&(buffer[0]),out_length);

  std::wstring utf16(buffer.begin(),buffer.end());

  return std::move(utf16);
}

std::string ScriptsData::ConvertWideToUTF8(const std::wstring& utf16)const
{
  if( utf16.empty() )
  {
    return EMPTY_STR;
  }

  const auto in_length = static_cast<int>(utf16.length());
  const auto out_length = WideCharToMultiByte(CP_UTF8,0,utf16.c_str(),in_length,0,0,0,0);

  if( out_length <= 0 )
  {
    return EMPTY_STR;
  }

  std::vector<char> buffer(out_length);

  WideCharToMultiByte(CP_UTF8,0,utf16.c_str(),in_length,&(buffer[0]),out_length,0,0);

  std::string mbs(buffer.begin(),buffer.end());

  return std::move(mbs);
}
//!
//! @fn std::string ScriptsData::ConvertWideToMultiByte(const std::wstring& utf16) const
//! @brief std::wstring(UTF-16) ���}���`�o�C�g�����R�[�h�� std::string �ɕϊ�����
//! @param[in] utf16 UTF-16 �����R�[�h�� std::wstring
//! @return �}���`�o�C�g�����R�[�h�� std::string
//!
std::string ScriptsData::ConvertWideToMultiByte(const std::wstring& utf16) const
{
  if( utf16.empty() )
  {
    return EMPTY_STR;
  }

  const auto in_length = static_cast<int>(utf16.length());
  const auto out_length = WideCharToMultiByte(CP_ACP,0,utf16.c_str(),in_length,0,0,0,0);

  if( out_length <= 0 )
  {
    return EMPTY_STR;
  }

  std::vector<char> buffer(out_length);

  WideCharToMultiByte(CP_ACP,0,utf16.c_str(),in_length,&(buffer[0]),out_length,0,0);

  std::string mbs(buffer.begin(),buffer.end());

  return std::move(mbs);
}

std::wstring ScriptsData::ConvertMultiByteToWide(const std::string& mbs)const
{
  if( mbs.empty() )
  {
    return EMPTY_WSTR;
  }

  const auto in_length = static_cast<int>(mbs.length());
  const auto out_length = MultiByteToWideChar(CP_ACP,0,mbs.c_str(),in_length,0,0);

  if( out_length <= 0 )
  {
    return EMPTY_WSTR;
  }

  std::vector<wchar_t> buffer(out_length);

  MultiByteToWideChar(CP_ACP,0,mbs.c_str(),in_length,&(buffer[0]),out_length);

  std::wstring utf16(buffer.begin(),buffer.end());

  return std::move(utf16);
}
//!
//! @fn unsigned int ScriptsData::GetScriptNum()  const
//! @brief �ǂݍ��� Json �̃X�N���v�g����Ԃ�
//! @return �X�N���v�g��
//! @details �X�N���v�g�̓C���^�v���^������ 1 �X�N���v�g 1 �s�ƂȂ�܂��B
//!
unsigned int ScriptsData::GetScriptNum()  const
{
  if( scripts == nullptr )
  {
    return 0;
  }

  return static_cast<unsigned int>(scripts->size());
}

//!
//! @fn std::string ScriptsData::GetScriptLine(const unsigned int index) const
//! @brief �w��s�̃X�N���v�g��Ԃ�
//! @param[in] index �X�N���v�g���̎w��s��
//! @return �X�N���v�g����
//! @details �G���[���͋󕶎����Ԃ�܂��B
//!
std::string ScriptsData::GetScriptLine(const unsigned int index) const
{
  const auto size = GetScriptNum();

  if( size <= 0 || size <= index )
  {
    return EMPTY_STR;
  }

  return (*scripts)[index];
}

//!
//! @fn std::vector<std::string> ScriptsData::GetScript(const unsigned int index) const
//! @brief �w��s�̃X�N���v�g���p�����[�^�ɕ������ĕԂ�
//! @param[in] index �X�N���v�g���̎w��s��
//! @return �������ꂽ�X�N���v�g����
//! @details �G���[���͋󕶎����Ԃ�܂��B
//! �X�N���v�g�̓J���}(',')�ŋ�؂��Ă���
//! "�R�}���h����, �p�����[�^1, �p�����[�^2, ..."
//! (�p�����[�^���̓R�}���h�ɂ��Ⴄ)
//! �̗l�ȃt�H�[�}�b�g�ɂȂ��Ă��܂��B
//! ����� ',' �ŋ�؂��� vector �� string �z��Ƃ��ĕԂ��܂��B
//!
std::vector<std::string> ScriptsData::GetScript(const unsigned int index,const std::string delimiter) const
{
  const auto line = GetScriptLine(index);

  return string::Split(line,delimiter);
}

bool ScriptsData::ScriptAdd(std::string Sclipts)
{
  scripts->emplace_back(Sclipts);
  return true;
};
bool ScriptsData::ScriptDelete(int line)
{
  scripts->erase(scripts->begin() + line);
  return true;
};
bool ScriptsData::ScriptClear()
{
  scripts->clear();
  return true;
};

