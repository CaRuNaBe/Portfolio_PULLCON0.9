#include  "EnemyColumn.h"
#include  "EnemySkyhunter.h"
#include  "GameStage.h"
EnemyColumn::EnemyColumn(ApplicationBase& game, int layer, ModeMainGame& mode, Vector4 pos)
  :ActorMainGame(game, layer, mode)
{
  Initialize();
  AddPieces(pos);
}

EnemyColumn::~EnemyColumn()
{}

void EnemyColumn::Initialize()
{
  ActorMainGame::Initialize();
  _stateEnemyColumn = State::WAIT;

  _iPieces = 3;
  _fSpeed = 300.f;
  _fScale = 2.0f;

  _collision._fRadius = 500.f * _fScale;
  _collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
  _collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
}

bool EnemyColumn::Update()
{
  ActorMainGame::Update();

  for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
  {
    if (obje->GetType() == Type::kPlayer)
    {
      if (IsSearch(*obje))
      {
        if (_stateEnemyColumn == State::WAIT)
        {
          _vRelation = obje->_vPos;
          SetVelocity();
          _stateEnemyColumn = State::PLAY;
          _synchronize = !_synchronize;
        }
      }
      else
      {
        if (_ST == 0)
        {
          _vRelation = obje->_vPos;
          SetVelocity();
          _stateEnemyColumn = State::PLAY;
          _synchronize = !_synchronize;
          _ST = 300;
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

  if (_iPieces == 0)
  {
    Damage();
  }

  _collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
  UpdateCollision();  // �R���W�����X�V

  return true;
}

void EnemyColumn::Damage()
{
  _mode.GetObjectServer3D().Del(*this);
}

bool EnemyColumn::Draw()
{
  ActorMainGame::Draw();

  // �R���W�����`��
  Vector4 color = { 255,255,255 };
  if (!((ModeMainGame&)_mode)._dbgCollisionDraw)
  {
    color = { 255,0,255 };
    DrawCollisionSearch(color);
  }
  return true;
}

void EnemyColumn::SetVelocity()
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

void EnemyColumn::AddPieces(Vector4 pos)
{
  for (auto i = 0; i < _iPieces; ++i)
  {
    auto skyhunter = std::make_shared<EnemySkyhunter>(_game, static_cast<int>(ActorMainGame::Type::kEnemySkyhunter), _mode, *this);
    skyhunter->SetPosition(pos);
    skyhunter->_iPart = i;
    skyhunter->_ST = 30 * i + 1;
    _mode.GetObjectServer3D().Add(skyhunter);
  }
}

