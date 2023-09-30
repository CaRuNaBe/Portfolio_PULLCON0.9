#include "Bullet.h"


Bullet::Bullet(ApplicationBase& game, int layer, ModeMainGame& mode)
  :ActorMainGame(game, layer, mode)
{
  _handleYellow = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo.mv1");
  _handleBlue = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo_Blue.mv1");
  _handlePurple = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo_Purple.mv1");
  _handle = 0;
  Initialize();
}

Bullet::~Bullet()
{
  MV1DeleteModel(_handleBlue);
  MV1DeleteModel(_handlePurple);
  MV1DeleteModel(_handleYellow);
}

void Bullet::Initialize()
{
  ActorMainGame::Initialize();

  _iDamage = 25;
  _fSpeed = 1200.f;
  _fScale = 3.f;

  _collision._fRadius = 150.f * _fScale;

  _ST = 90;
}

bool Bullet::Update()
{
  ActorMainGame::Update();

  // ��������
  if (_ST == 0)
  {
    Damage();
  }

  // �ݒ肳�ꂽ�����ɐi��
  Vector4 _vd = _vDir;
  _vd *= _fSpeed;
  _vPos += _vd;

  _collision._fRadius = 150.f * _fScale;
  UpdateCollision();    // �R���W�����A�b�v�f�[�g

  switch (_iType)
  {
    case 1:
      _handle = _handleBlue;
      break;
    case 2:
      _handle = _handlePurple;
      break;
    default:
      _handle = _handleYellow;
      break;
  }

  return true;
}

void Bullet::Damage()
{
  if (_ST > 0)
  {
    for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
    {
      if (obje->GetType() == Type::kPlayer)
      {
        obje->_takeIn = true;
        obje->_ST = 10;
      }
    }
  }
  _mode.AddEffectDestroyAmmo(_vPos);
  _mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw()
{
  ActorMainGame::Draw();

  float length3D = sqrt(_vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z);
  float theta = acos(_vDir.y / length3D);
  MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
  MV1SetRotationZYAxis(_handle, VGet(_vDir.z, 0.f, -(_vDir.x)), VGet(0.f, 1.f, 0.f), theta - utility::PiOver2);
  MV1SetPosition(_handle, ToDX(_vPos));
  MV1DrawModel(_handle);
  // �R���W�����`��
  Vector4 color = { 255, 255, 255 };
  if (!_mode._dbgCollisionDraw)
  {
    if (_CT == 0)
    {
      DrawCollision(color);
    }
  }
  return true;
}
