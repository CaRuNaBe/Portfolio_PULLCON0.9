#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class EndLogo:public ActorTitle
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
  EndLogo( ApplicationBase& game,int layer,ModeTitle& mode );
  ~EndLogo();
  virtual Type GetType()//���������҂�
  {
    return Type::KENDLOGO;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜
};

