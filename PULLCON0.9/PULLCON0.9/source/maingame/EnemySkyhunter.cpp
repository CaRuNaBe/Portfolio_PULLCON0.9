#include  "EnemySkyhunter.h"
#include  "Bullet.h"
#include  "GameStage.h"
#include "../ApplicationGlobal.h"
namespace
{
  constexpr int SKYHUNTER_ID = 10;
}
EnemySkyhunter::EnemySkyhunter(ApplicationBase& game, int layer, ModeMainGame& mode, EnemyColumn& skyhunter)
  :ActorMainGame(game, layer, mode)
  , _column(skyhunter)
{
  _handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(SKYHUNTER_ID));

  Initialize();
}

EnemySkyhunter::~EnemySkyhunter()
{
  MV1DeleteModel(_handle);
}

void EnemySkyhunter::Initialize()
{
  ActorMainGame::Initialize();

  _stateEnemySkyhunter = State::WAIT;

  _fScale = 4.f;
  _fSpeed = 300.f;
  _collision._fRadius = 1000.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 26.f;

  _iLife = 2;

}

bool EnemySkyhunter::Update()
{
  ActorMainGame::Update();

  if (_stateEnemySkyhunter == State::WAIT)
  {
    _collision._vCenter = _vPos;
    _collisionEvent._vCenter = _vPos;
    _stateEnemySkyhunter = State::PLAY;
  }

  // �O�����ɍ��W(r(length3D),��(theta),��(rad))
  float sx = 0.f, sz = 0.f, sy = 0.f;
  float length3D = 0.f;
  float rad = 0.f;
  float theta = 0.f;

  for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
  {
    if (obje->GetType() == Type::kPlayer
        || obje->GetType() == Type::kBullet
        || obje->GetType() == Type::kGameStage)
    {
      if (obje->GetType() == Type::kPlayer)
      {
        if (Intersect(_collisionEvent, obje->_collision))
        {
          _fire = true;
          _vTarget = obje->_vPos;
          // �e�Ƀo��������������
          float randomX = static_cast<float>(utility::get_random(-700, 700));
          float randomY = static_cast<float>(utility::get_random(-700, 1400));
          float randomZ = static_cast<float>(utility::get_random(-700, 700));
          _vTarget = { _vTarget.x + randomX, _vTarget.y + randomY, _vTarget.z + randomZ };
        }
      }
      if (obje->GetType() == Type::kBullet)
      {
        if (IsHitObject(*obje))
        {
          if (obje->_iType == 2)
          {
            PlaySoundMem(gGlobal._se["se_gunlanding"], DX_PLAYTYPE_BACK);//��������炷
            _mode.AddEffectHitEnemy(obje->GetPosition());
            _CT = 10;
            _overlap = true;
            obje->Damage();
            _iLife -= obje->_iDamage;
          }
        }
      }
      if ((obje->GetType() == Type::kGameStage))
      {
        auto stage = std::static_pointer_cast<GameStage>(obje);
        _handleStage = stage->GetHandle();
        MV1RefreshCollInfo(_handleStage, 0);
      }
    }
  }

  // �O�����ɍ��W
  sx = _vTarget.x - _vPos.x;
  sz = _vTarget.z - _vPos.z;
  sy = _vTarget.y - _vPos.y;
  length3D = sqrt(sx * sx + sy * sy + sz * sz);
  rad = atan2(sz, sx);
  theta = acos(sy / length3D);

  // �e�̐i�s�����̌�����ݒ�
  _vDir.x = cos(rad);
  _vDir.z = sin(rad);
  _vDir.y = cos(theta);
  _vDir.Normalized();

  // ���Ԋu�Œe������
  if (_fire && _CT == 0)
  {
    AddBullet();
    SeGunShotPlay();
    _CT = 120;
  }

  if (_column._synchronize != _synchronize)
  {
    _ST = 30 * _iPart + 1;
    _synchronize = !_synchronize;
  }
  if (_ST == 1)
  {
    _vVelocity = _column._vVelocity;
  }

  MV1_COLL_RESULT_POLY hitPoly;
  Vector4 move = _vVelocity * _fSpeed;
  Vector4 posStart = _vPos + move;
  Vector4 posEnd = { posStart.x, posStart.y - 6000.f, posStart.z };
  hitPoly = MV1CollCheck_Line(_handleStage, 0, ToDX(posStart), ToDX(posEnd));
  if (hitPoly.HitFlag)
  {
    move += ToMath(hitPoly.HitPosition) - posEnd;
  }
  _vPos += move;

  if (_iLife < 0)
  {
    Damage();
  }

  _collision._fRadius = 1000.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 26.f;
  _vEvent = _vPos;
  UpdateCollision();  // �R���W�����X�V

  return true;
}

void EnemySkyhunter::Damage()
{
  --_column._iPieces;
  _mode.GetObjectServer3D().Del(*this);
}

bool EnemySkyhunter::Draw()
{
  ActorMainGame::Draw();

  // ���f���g��
  MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
  // ���f����]
  MV1SetRotationYUseDir(_handle, ToDX(_vVelocity), 0.f);
  // ���f���ړ�
  MV1SetPosition(_handle, ToDX(_vPos));
  // ���f���`��
  MV1DrawModel(_handle);

  // �R���W�����`��
  Vector4 color = { 255,255,255 };
  if (!_mode._dbgCollisionDraw)
  {
    DrawCollision(color);
    DrawCollisionEvent(color);
    if (_overlap)
    {
      color = { 255, 0, 0 };
      DrawCollision(color);
    }
  }
  return true;
}

void EnemySkyhunter::AddBullet()
{
  Vector4 vBullet = { _vPos.x, _vPos.y - 500.f, _vPos.z };
  auto bullet = std::make_shared<Bullet>(_game, static_cast<int>(ActorMainGame::Type::kBullet), _mode);
  bullet->SetPosition(vBullet);
  bullet->SetDir(_vDir);
  bullet->_iType = 1;
  _mode.GetObjectServer3D().Add(bullet);
}
