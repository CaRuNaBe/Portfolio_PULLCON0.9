#pragma once
#include "ActorMainGame.h"
#include "appframe.h"
#include "../mode/ModeMainGame.h"
class EffectBase :public ActorMainGame
{
public:
  EffectBase(ApplicationBase& game, int layer, ModeMainGame& mode);
  virtual ~EffectBase();
  virtual Type GetType()
  {
    return Type::kEffect;
  }

  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

protected:
  int _grHandle;  // ���݂̃O���t�B�b�N�n���h��
  std::vector<int>_grAllHandles;// �S�ẴO���t�B�b�N�n���h��
  int _animeNo;// �A�j���ԍ�
  int _animeMax;// �A�j���ő吔
  int _animeCnt;// �A�j���J�E���g
};

