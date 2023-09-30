#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyKobae :public ActorMainGame
{
public:
  EnemyKobae(ApplicationBase& game, int layer, ModeMainGame& mode);
  virtual ~EnemyKobae();
  virtual Type GetType()
  {
    return Type::kEnemySkyhunter;
  }
  // �R�o�G�̏��
  enum class State
  {
    WAIT,//�ҋ@���
    PLAY,//�}���̐�
  };
  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

  virtual void Damage();
  void SetVelocity();   // ���x�x�N�g��
  void AddBullet();

protected:
  State   _stateEnemyKobae;

  int    _handle;
  int    _handleStage;
};

