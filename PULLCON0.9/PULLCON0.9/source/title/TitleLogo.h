/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  �^�C�g�����S�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class TitleLogo:public ActorTitle
{
public:
  TitleLogo( ApplicationBase& game,int layer,ModeTitle& mode );
  ~TitleLogo();
  virtual Type GetType()//���������҂�
  {
    return Type::KTITLELOGO;
  }

  void Initialize();//������
  bool Update();
  bool Draw();

private:
  int _cg;// �摜
};

