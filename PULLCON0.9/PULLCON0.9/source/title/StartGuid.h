#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class StartGuid:public ActorTitle
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
  StartGuid( ApplicationBase& game,int layer,ModeTitle& mode );
  ~StartGuid();
  virtual Type GetType()//���������҂�
  {
    return Type::KGAMESTARTGUID;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜
};

