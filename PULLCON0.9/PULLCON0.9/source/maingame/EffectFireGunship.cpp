#include "EffectFireGunship.h"
EffectFireGunship::EffectFireGunship(ApplicationBase& game, int layer, ModeMainGame& mode)
  :EffectBase(game, layer, mode)
{
  Initialize();
  // ���\�[�X�T�[�o�[����n���h�����擾����
  ResourceServer::GetHandles("effect_fire_gunship", _grAllHandles);
  _animeMax = static_cast<int>(_grAllHandles.size());
}

EffectFireGunship::~EffectFireGunship()
{}

void EffectFireGunship::Initialize()
{
  EffectBase::Initialize();
}

bool EffectFireGunship::Update()
{
  EffectBase::Update();
  if (_animeCnt == _animeMax)
  {
    _mode.GetObjectServer3D().Del(*this);
  }
  _animeNo = _animeCnt % _animeMax;
  _animeCnt++;

  return true;
}

bool EffectFireGunship::Draw()
{
  EffectBase::Draw();
  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(false);
  DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 8000.0f, 0.f, _grAllHandles[_animeNo], TRUE);
  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(true);
  return true;
}