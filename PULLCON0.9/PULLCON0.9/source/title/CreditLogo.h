/*****************************************************************//**
 * \file   CreditLogo.h
 * \brief  �N���W�b�g���S�I�u�W�F�N�g�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class CreditLogo:
  public ActorTitle
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
  CreditLogo( ApplicationBase& game,int layer,ModeTitle& mode );
  ~CreditLogo();
  virtual Type GetType()//���������҂�
  {
    return Type::KCREDITLOGO;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜
};

