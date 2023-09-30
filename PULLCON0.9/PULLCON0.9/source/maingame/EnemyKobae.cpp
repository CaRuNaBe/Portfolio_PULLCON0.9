#include  "EnemyKobae.h"
#include  "Bullet.h"
#include  "GameStage.h"
#include "../ApplicationGlobal.h"
namespace
{
  constexpr int KOBAE_ID = 11;
}

EnemyKobae::EnemyKobae(ApplicationBase& game, int layer, ModeMainGame& mode)
  :ActorMainGame(game, layer, mode)
{
  Initialize();
}

EnemyKobae::~EnemyKobae()
{
  MV1DeleteModel(_handle);
}

void EnemyKobae::Initialize()
{
  ActorMainGame::Initialize();

  _handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(KOBAE_ID));

  _stateEnemyKobae = State::WAIT;

  _vEvent = _vPos;
  _fScale = 4.f;
  _fSpeed = 400.f;
  _collision._vCenter = _vPos;
  _collision._fRadius = 1000.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 26.f;
  _collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;

  _iLife = 2;

}

bool EnemyKobae::Update()
{
  ActorMainGame::Update();

  if (_stateEnemyKobae == State::WAIT)
  {
    _collision._vCenter = _vPos;
    _collisionEvent._vCenter = _vPos;
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
        if (IsSearch(*obje))
        {
          if (_stateEnemyKobae == State::WAIT)
          {
            _vRelation = obje->_vPos;
            SetVelocity();
            _stateEnemyKobae = State::PLAY;
          }
        }
        else
        {
          if (_ST == 0)
          {
            _vRelation = obje->_vPos;
            SetVelocity();
            _stateEnemyKobae = State::PLAY;
            _ST = 300;
          }
        }
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
  _collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
  _vEvent = _vPos;
  UpdateCollision();  // �R���W�����X�V

  return true;
}

void EnemyKobae::Damage()
{
  _mode.GetObjectServer3D().Del(*this);
}

bool EnemyKobae::Draw()
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
  if (!((ModeMainGame&)_mode)._dbgCollisionDraw)
  {
    DrawCollision(color);
    DrawCollisionEvent(color);
    DrawCollisionSearch(color);
    if (_overlap)
    {
      color = { 255, 0, 0 };
      DrawCollision(color);
    }
  }
  return true;
}

void EnemyKobae::SetVelocity()
{
  // �O�����ɍ��W
  float sx = _vRelation.x - _vPos.x;
  float sz = _vRelation.z - _vPos.z;
  float sy = _vRelation.y - _vPos.y;
  float length3D = sqrt(sx * sx + sy * sy + sz * sz);
  float rad = atan2(sz, sx);
  float theta = acos(sy / length3D);

  float randomDeg = static_cast<float>(utility::get_random(-30, 30));
  float randomRad = utility::degree_to_radian(randomDeg);
  // ���f���̐i�s�����ݒ�p
  _vVelocity.x = cos(rad + randomRad);
  _vVelocity.z = sin(rad + randomRad);
  _vVelocity.y = cos(theta);
  _vVelocity.Normalized();
}


void EnemyKobae::AddBullet()
{
  Vector4 vBullet = { _vPos.x, _vPos.y - 500.f, _vPos.z };
  auto bullet = std::make_shared<Bullet>(_game, static_cast<int>(ActorMainGame::Type::kBullet), _mode);
  bullet->SetPosition(vBullet);
  bullet->SetDir(_vDir);
  bullet->_iType = 1;
  _mode.GetObjectServer3D().Add(bullet);
}
