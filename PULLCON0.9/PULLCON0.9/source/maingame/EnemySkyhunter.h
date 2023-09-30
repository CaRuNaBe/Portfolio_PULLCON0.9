#pragma once
#include "appframe.h"
#include "EnemyColumn.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemySkyhunter : public ActorMainGame
{
public:
  EnemySkyhunter(ApplicationBase& game, int layer, ModeMainGame& mode, EnemyColumn& skyhunter);
  virtual ~EnemySkyhunter();
  virtual Type GetType()
  {
    return Type::kEnemySkyhunter;
  }
  // �X�J�C�n���^�[�̏��
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
  EnemyColumn& _column;

  State   _stateEnemySkyhunter;

  int    _handle;
  int    _handleStage;
};
