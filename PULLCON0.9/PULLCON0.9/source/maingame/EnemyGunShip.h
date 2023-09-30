#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyGunShip :public ActorMainGame
{
public:
  EnemyGunShip(ApplicationBase& game, int layer, ModeMainGame& mode, float _radius);
  virtual ~EnemyGunShip();
  virtual Type GetType()
  {
    return Type::kEnemyGunShip;
  }
  // �K���V�b�v�̏��
  enum class State
  {
    NUM, //�������
    WAIT,//�ҋ@���
    PLAY,//�}���̐�
  };
  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

  virtual void Damage();
  void AddBullet();

protected:
  State   _stateClearObject;

  Vector4 _vObjective;  // �~�O�����S���W

  int    _handle;
  float radius;
};

