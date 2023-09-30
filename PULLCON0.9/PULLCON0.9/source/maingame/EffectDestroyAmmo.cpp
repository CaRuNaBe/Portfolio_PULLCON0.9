#include "EffectDestroyAmmo.h"
EffectDestroyAmmo::EffectDestroyAmmo(ApplicationBase& game, int layer, ModeMainGame& mode)
  :EffectBase(game, layer, mode)
{
  Initialize();
  // ���\�[�X�T�[�o�[����n���h�����擾����
  ResourceServer::GetHandles("effect_destroy_ammo", _grAllHandles);
  _animeMax = static_cast<int>(_grAllHandles.size());
}

EffectDestroyAmmo::~EffectDestroyAmmo()
{}

void EffectDestroyAmmo::Initialize()
{
  EffectBase::Initialize();
}

bool EffectDestroyAmmo::Update()
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

bool EffectDestroyAmmo::Draw()
{
  EffectBase::Draw();
  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(false);
  DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 4000.0f, 0.f, _grAllHandles[_animeNo], TRUE);
  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(true);
  return true;
}
