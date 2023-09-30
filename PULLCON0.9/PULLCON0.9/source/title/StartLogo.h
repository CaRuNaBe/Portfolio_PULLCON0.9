/*****************************************************************//**
 * \file   StartLogo.h
 * \brief  �Q�[���X�^�[�g���S�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class StartLogo:public ActorTitle
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
  StartLogo( ApplicationBase& game,int layer,ModeTitle& mode );
  ~StartLogo();
  virtual Type GetType()//���������҂�
  {
    return Type::KGAMESTARTLOGO;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜

};