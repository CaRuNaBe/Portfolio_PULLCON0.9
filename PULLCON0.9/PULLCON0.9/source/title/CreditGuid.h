#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class CreditGuid: public ActorTitle
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
  CreditGuid( ApplicationBase& game,int layer,ModeTitle& mode );
  ~CreditGuid();
  virtual Type GetType()//���������҂�
  {
    return Type::KCREDITGUID;
  }

  void Initialize();//������
  bool Update( );
  bool Draw( );

private:
  int _cg;// �摜
};
