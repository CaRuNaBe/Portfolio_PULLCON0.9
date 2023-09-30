/*****************************************************************//**
 * \file   command_drawin.h
 * \brief  'di' �X�N���v�g����������N���X��`
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandDrawIn : public CommandBase
{
public:
  CommandDrawIn(unsigned int line,const std::vector<std::string>& script);
  CommandDrawIn(const CommandDrawIn&) = default;
  CommandDrawIn(CommandDrawIn&&) noexcept = default;

  virtual ~CommandDrawIn() = default;

  CommandDrawIn& operator=(const CommandDrawIn& right) = default;
  CommandDrawIn& operator=(CommandDrawIn&& right) noexcept = default;

  bool Check() override;

  inline std::string GetLabel() const
  {
    return script[5];
  }

  inline int GetIndex() const
  {
    return index;
  }
  inline int GetX() const
  {
    return x;
  }
  inline int GetY() const
  {
    return y;
  }
  inline int GetHandle() const
  {
    return handle;
  }
  inline void SetHandle(const int handle)
  {
    this->handle = handle;
  }

  inline int GetinCount() const
  {
    return in_count;
  }

  inline double GetDrawAlphain()const
  {
    return _DrawAlphain;
  }

  inline void SetDrawAlphain(double new_DrawAlphain)
  {
    this->_DrawAlphain = new_DrawAlphain;
  };

  inline bool GetDrawcomplete()
  {
    return isdrawincomplete;
  }

  inline void SetDrawcomplete(bool completedraw)
  {
    this->isdrawincomplete = completedraw;
  }

private:
  int index;
  int x;
  int y;
  int in_count;
  int handle;
  double _DrawAlphain;
  bool isdrawincomplete;
};

