#include "AreaEnemySpawn.h"
#include "EnemyColumn.h"
#include "EnemyKobae.h"
#include "../mode/ModeMainGame.h"
#include "../ApplicationGlobal.h"
namespace
{
  constexpr int AREAENEMYSPAWN_ID = 14;
  constexpr int KOBAE_ID = 11;
  constexpr int SKYHUNTER_ID = 10;

}
AreaEnemySpawn::AreaEnemySpawn(ApplicationBase& game, int layer, ModeMainGame& mode, int spawnfream, int typeenemy)
  :ActorMainGame(game, layer, mode)
{
  _iSpawnFream = spawnfream;
  _iEnemyType = typeenemy;
  _handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(AREAENEMYSPAWN_ID));
  MV1DeleteModel(ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(KOBAE_ID)));
  MV1DeleteModel(ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(SKYHUNTER_ID)));

  Initialize();
}

AreaEnemySpawn::~AreaEnemySpawn()
{
  MV1DeleteModel(_handle);
}

void AreaEnemySpawn::Initialize()
{
  ActorMainGame::Initialize();
  _stateEnemySpawn = State::NUM;

  _isAddKobae = false;
  _fScale = 3.f;
  _collision._fRadius = 1500.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 20.f;

  _iLife = 150;
}

bool AreaEnemySpawn::Update()
{
  ActorMainGame::Update();

  if (_stateEnemySpawn == State::NUM)
  {
    _vEvent = _vPos;
    _collision._vCenter = _vPos;
    UpdateCollision();  // �R���W�����X�V
    _stateEnemySpawn = State::WAIT;
  }

  // �X�|�[�������������J�E���g
  int countEnemy = 0;

  for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
  {
    if (obje->GetType() == Type::kPlayer
        || obje->GetType() == Type::kBullet
        || obje->GetType() == Type::kEnemySkyhunter)
    {
      if (obje->GetType() == Type::kPlayer)
      {
        if (Intersect(_collisionEvent, obje->_collision))
        {
          _coll = true;
          _fire = true;
        }
        else
        {
          _coll = false;
        }
      }
      if (obje->GetType() == Type::kBullet)
      {
        if (IsHitObject(*obje))
        {
          if (obje->_iType == 2)
          {
            PlaySoundMem(gGlobal._se["se_gunlanding"], DX_PLAYTYPE_BACK);
            _mode.AddEffectHitEnemy(obje->GetPosition());
            _overlap = true;
            obje->Damage();
            _iLife -= obje->_iDamage;
          }
        }
      }
      if (obje->GetType() == Type::kEnemySkyhunter)
      {
        ++countEnemy;
      }
    }
  }

  if (countEnemy > 20)
  {
    _fire = false;
  }

  // ���Ԋu�ŃX�|�[��������
  if (_fire && _CT == 0)
  {
    switch (_iEnemyType)
    {
      case 1:
        AddEnemyColumn();
        break;
      case 2:
        AddEnemyKobae();
        break;
      case 3:
        if (_isAddKobae)
        {
          AddEnemyKobae();
        }
        else
        {
          AddEnemyColumn();
        }
        _isAddKobae = !_isAddKobae;
        break;
      default:
        break;
    }
    _CT = _iSpawnFream;
  }

  if (_iLife < 0)
  {
    Damage();
  }

  _collision._fRadius = 1500.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 20.f;
  _vEvent = _vPos;
  UpdateCollision();  // �R���W�����X�V

  return true;
}

bool AreaEnemySpawn::Draw()
{
  ActorMainGame::Draw();

  // ���f���g��
  MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
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

void AreaEnemySpawn::Damage()
{
  PlaySoundMem(gGlobal._se["gunship_death"], DX_PLAYTYPE_BACK);
  _mode.AddEffectDeathObject(_vPos);
  _mode.GetObjectServer3D().Del(*this);
}

void AreaEnemySpawn::AddEnemyColumn()
{
  auto column = std::make_shared<EnemyColumn>(_game, static_cast<int>(ActorMainGame::Type::kEnemySkyhunter), _mode, _vPos);
  column->SetPosition(_vPos);
  _mode.GetObjectServer3D().Add(column);
}

void AreaEnemySpawn::AddEnemyKobae()
{
  auto kobae = std::make_shared<EnemyKobae>(_game, static_cast<int>(ActorMainGame::Type::kEnemySkyhunter), _mode);
  kobae->SetPosition(_vPos);
  _mode.GetObjectServer3D().Add(kobae);
}
