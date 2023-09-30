#include "EffectDeathObject.h"
EffectDeathObject::EffectDeathObject( ApplicationBase& game, int layer, ModeMainGame& mode )
  :EffectBase( game, layer,mode )
{
  Initialize();
  // ���\�[�X�T�[�o�[����n���h�����擾����
  ResourceServer::GetHandles( "effect_death_object",_grAllHandles );
  _animeMax = static_cast<int>(_grAllHandles.size());
}

EffectDeathObject::~EffectDeathObject()
{}

void EffectDeathObject::Initialize()
{
  EffectBase::Initialize();

  _animeNo = 0;
  _animeCnt = 0;

}

bool EffectDeathObject::Update()
{
  EffectBase::Update();

  if ( _animeCnt == _animeMax )
  {
    _mode.GetObjectServer3D().Del( *this );
  }
  _animeNo = _animeCnt % _animeMax;
  _animeCnt++;
  return true;
}

bool EffectDeathObject::Draw()
{
  EffectBase::Draw();
    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D( false );
  DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,40000.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D( true );
  return true;
}