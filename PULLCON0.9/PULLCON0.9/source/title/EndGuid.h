#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class EndGuid:public ActorTitle
{
     /**
    * �I�u�W�F�N�g�̏��.
    */
  enum class State
  {
    IDLING,//�ҋ@
    PULLED//���������Ă���
  };
public:
  EndGuid( ApplicationBase& game,int laysr,ModeTitle& mode );
  ~EndGuid();
  virtual Type GetType()//���������҂�
  {
    return Type::KENDGUID;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜
};

