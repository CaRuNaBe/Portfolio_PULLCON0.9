#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class StageObject :public ActorMainGame
{
public:
  StageObject(ApplicationBase& game, int layer, ModeMainGame& mode, int objectid, int collision, int pieces_coll);
  virtual ~StageObject();
  virtual Type GetType()
  {
    return Type::kStageObject;
  }
  // �X�e�[�W�I�u�W�F�N�g�̏��
  enum class State
  {
    NUM, //�������
    STATE,//�v���C�A�u�����
  };

  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

  void AddCollision();

protected:
  State  _stateStageObject;

  int    _iPiecesColl;
  int    _handle;
};

