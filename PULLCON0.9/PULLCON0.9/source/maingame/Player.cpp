#include "appframe.h"
#include "../ApplicationGlobal.h"
#include "Player.h"
#include "Bullet.h"
#include "GameStage.h"

namespace
{
  const float CAMERATARGET_Y = 1000.f;  // �J�����̒����_�̊�{�ʒu�v���C���[�̍��W�{�v���C���[��Y���W�{CAMERATARGET_Y
  const float CAMERADEFAULT_POS_Y = 2500.f;   // �v���C���[�����_�Ƃ����Ƃ��̃J������Y���W
  const float CAMERADEFAULT_POS_XZ = -4000.f;   // �v���C���[�����_�Ƃ����Ƃ��̃J������XZ���W�̃x�N�g���̒���
  const float PLAYERLENGTH = 2000.f;   // �v���C���[�̉��s���̒���
  const float AXIALROTATION = utility::degree_to_radian(20.f);   // �v���C���[�̈ړ����̌X��
  const int   LIFEMAX = 300;   // �v���C���[�̃��C�t�ő吔
  constexpr int PLAYER_ID = 0;
  const std::string DELIMITER = ",";
}

Player::Player(ApplicationBase& game, int layer, ModeMainGame& mode)
  :ActorMainGame(game, layer, mode)
{
  auto file_pass = string::Split(gGlobal.object_pass_date->GetScriptLine(PLAYER_ID), DELIMITER);
  _handleBody = ResourceServer::LoadMV1Model(file_pass[0].c_str());
  _handleAirscrew = ResourceServer::LoadMV1Model(file_pass[1].c_str());
  _handleMagnet = ResourceServer::LoadMV1Model(file_pass[2].c_str());
  _handleBackAirscrew = ResourceServer::LoadMV1Model(file_pass[3].c_str());

  Initialize();
}

Player::~Player()
{
  MV1DeleteModel(_handleBody);
  MV1DeleteModel(_handleAirscrew);
  MV1DeleteModel(_handleMagnet);
  MV1DeleteModel(_handleBackAirscrew);
}

void Player::Initialize()
{
  ActorMainGame::Initialize();
  _statePlayer = State::NUM;

  _vMoveDir = { 0.f, 0.f, -100.f };
  _fSpeed = 90.f;
  _fRotatY = utility::PI;
  _iFuel = 400;
  _iLife = LIFEMAX;
  _push = 0;
  _isLerp = false;
  _isHit = false;
  _isHitObject = false;
  _fTime = 0.f;
  _fRotateAirscrew = 0.f;
  _fRotateBackAirscrew = 0.f;
  _fAxialX = 0.f;
  _fAxialZ = 0.f;

  _collision._fRadius = 500.f * _fScale;
  _cam._clipNear = 100.f;
  _cam._clipFar = 30000000.f;
}

bool Player::Update()
{
  ActorMainGame::Update();
  // NUM��ԂȂ�PLAY��ԂɈڍs����
  if (_statePlayer == State::NUM)
  {
    ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["player_hovering"]);
    PlaySoundMem(gGlobal._se["player_hovering"], DX_PLAYTYPE_LOOP);
    // �J�����̐ݒ�
    _cam._vPos.x = _vPos.x;
    _cam._vPos.y = _vPos.y + CAMERADEFAULT_POS_Y;
    _cam._vPos.z = _vPos.z + CAMERADEFAULT_POS_XZ;
    _cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
    // ���x�����l�L�^
    _fSpeedIint = _fSpeed;
    _collision._vCenter = _vPos;
    _statePlayer = State::PLAY;
  }

  for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
  {
    if (obje->GetType() == Type::kEnemyAAA
        || obje->GetType() == Type::kBullet
        || obje->GetType() == Type::kStageObject
        || obje->GetType() == Type::kGameStage)
    {
      if (obje->GetType() == Type::kEnemyAAA)
      {
        if (obje->_pull == true && _pull)
        {
          // �I�u�W�F�N�g�܂ňړ�����
          Vector4 objective = obje->_vPos;
          // �΋�C�p�[�c�̌��ŕϓ�������
          objective.y += _collision._fRadius + static_cast<float>(_iPieces + 1) * obje->_collision._fRadius;
          Vector4 dir = objective - _vPos;
          dir.Normalized();
          _vPos += dir * static_cast<float>(_CT);
          if (_CT == 0)
          {
            _vPos = objective;
          }
        }
        if (obje->_finish == true)
        {
          // �΋�C�Ɏw��ʒu��_�킹��
          obje->_vTarget = _vTarget;
        }
        if (IsHitEvent(*obje))
        {
          _event = true;
          if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_X) && !_pull)
          {
            _push = 0;
            _event = false;
            _pull = true;
            obje->_pull = true;
            obje->_coll = false;
            _CT = 10;
          }
        }
      }
      if (obje->GetType() == Type::kBullet)
      {
        if (IsHitObject(*obje))
        {
          if (obje->_iType != 2 && !_isHit)
          {
            _mode.AddEffectHitPlayerFrame(_vPos);
            _iLife -= obje->_iDamage;
            obje->Damage();
            _isHit = true;
            _ST = 20;
          }
        }
      }
      if ((obje->GetType() == Type::kStageObject))
      {
        if (IsHitObject(*obje))
        {
          if (!_isHitObject)
          {
            ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["player_object_crash"]);
            PlaySoundMem(gGlobal._se["player_object_crash"], DX_PLAYTYPE_BACK);
            _iLife -= 5;
          }
          _isHit = true;
          _isHitObject = true;
          _ST = 10;
        }
      }
      if ((obje->GetType() == Type::kGameStage))
      {
        auto stage = std::static_pointer_cast<GameStage>(obje);
        _handleStage = stage->GetHandle();
        MV1RefreshCollInfo(_handleStage, -1);
      }
    }
  }

  // �J�����X�V
  CameraUpdate();

  if (_statePlayer == State::PLAY)
  {

    if (_finish)
    {
      _finish = false;
    }

    float axialX = _fAxialX;
    float axialZ = _fAxialZ;
    if (_game.Getinput().GetLstickY() > 0)
    {  // �O����
      axialX -= AXIALROTATION / 20.f;
    }
    else if (_game.Getinput().GetLstickY() < 0)
    {  // �����
      axialX += AXIALROTATION / 20.f;
    }
    else
    {
      if (abs(axialX) < utility::degree_to_radian(1.f))
      {
        axialX = 0.f;
      }
      else if (axialX < 0.f)
      {
        axialX += AXIALROTATION / 20.f;
      }
      else
      {
        axialX -= AXIALROTATION / 20.f;
      }
    }
    if (_game.Getinput().GetLstickX() < 0)
    {  // �E����
      axialZ -= AXIALROTATION / 20.f;
    }
    else if (_game.Getinput().GetLstickX() > 0)
    {  // ������
      axialZ += AXIALROTATION / 20.f;
    }
    else
    {
      if (abs(axialZ) < utility::degree_to_radian(1.f))
      {
        axialZ = 0.f;
      }
      else if (axialZ < 0.f)
      {
        axialZ += AXIALROTATION / 20.f;
      }
      else
      {
        axialZ -= AXIALROTATION / 20.f;
      }
    }
    // ��]����
    if (abs(axialX) < AXIALROTATION)
    {
      _fAxialX = axialX;
    }
    if (abs(axialZ) < AXIALROTATION)
    {
      _fAxialZ = axialZ;
    }

    // �J�����̌����Ă���p�x���擾
    float sx = _cam._vPos.x - _cam._vTarget.x;
    float sy = _cam._vPos.y - _cam._vTarget.y;
    float sz = _cam._vPos.z - _cam._vTarget.z;
    float length3D = sqrt(sx * sx + sy * sy + sz * sz);
    float camerad = atan2(sz, sx);
    float theta = acos(sy / length3D);
    float rad = 0;

    //�L�����̏㏸���~
    int diry = 0;
    if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_A))
    {
      diry += 1;
      _fRotateAirscrew += 3.f * utility::PI / 10.f;
    }
    if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_B))
    {
      diry += -1;
      _fRotateAirscrew -= utility::PI / 18.f;
    }

    //�L�����̈ړ�
    Vector4 dir = { -(_game.Getinput().GetLstickY()),0,_game.Getinput().GetLstickX() };   // int�l������

    float length = 0.f;
    dir.Normalized();
    if (dir.Lenght() > 0.f)
    {
      length = _fSpeed;
    }
    rad = atan2(dir.z, dir.x);
    dir.y += diry * _fSpeed;
    dir.x = cos(rad + camerad) * length;
    dir.z = sin(rad + camerad) * length;
    if (!_isHitObject)
    {
      _vMoveDir = dir * -1.f;
    }
    else
    {
      dir = _vMoveDir;
    }

    MV1_COLL_RESULT_POLY hitPoly;
    Vector4 posStart = _vPos + dir;
    Vector4 posEnd = { posStart.x, posStart.y - 3000.f, posStart.z };
    hitPoly = MV1CollCheck_Line(_handleStage, -1, ToDX(posStart), ToDX(posEnd));
    if (hitPoly.HitFlag)
    {
      dir += ToMath(hitPoly.HitPosition) - posEnd;
    }

    _vPos += dir;
    // �J�������Ǐ]������
    _cam._vPos += dir;
    _cam._vTarget += dir;

    // �e�ۂ̌����x�N�g���ݒ�
    Vector4 v = { -1.f, 0.f, 0.f };
    rad = atan2(v.z, v.x);
    // �e�Ƀo��������������
    float randomDeg = static_cast<float>(utility::get_random(-1, 1));
    float randomRad = utility::degree_to_radian(randomDeg);
    v.x = cos(rad + camerad + randomRad);
    v.z = sin(rad + camerad + randomRad);
    // �e�Ƀo��������������
    randomDeg = static_cast<float>(utility::get_random(-1, 1));
    randomRad = utility::degree_to_radian(randomDeg);
    v.y = sin(_fRotatX + randomRad);
    // �e�̌����x�N�g��
    _vDir = v;

    // �w��ʒu�ݒ�
    float distance = _collision._fRadius * 2.f * 15.f;
    v.x = cos(rad + camerad) * distance;
    v.z = sin(rad + camerad) * distance;
    v.y = sin(_fRotatX) * distance;
    _vTarget = _vPos + v * v.Lenght() * 4.f;

    if (_game.Getinput().XinputEveryOtherRightTrigger(10))
    {  // RT
      if (_iPieces > 0)
      {
        // SE�Đ�
        SeGunShotPlay();
      }
      // �e����
      _fire = true;
    }

    // �����������J��
    if (_pull && _CT == 0)
    {
      _cam._vMemory = _cam._vPos - _cam._vTarget;
      _cam._vTarget = _vPos;
      _cam._vPosEvent.y = _cam._vTarget.y + cos(theta) * length3D;
      length3D *= 0.5f;
      length3D *= static_cast<float>(_iPieces + 1);
      _cam._vPosEvent.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
      _cam._vPosEvent.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);
      _isLerp = true;
      _fTime = 0.0f;
      _statePlayer = State::EVENT;
    }
  }
  else if (_statePlayer == State::EVENT && !_isLerp)
  {
    Vector4 move = { 0.f, 2.f, 0.f };
    if (_pull && _CT > 0)
    {
      // �����_�̈ړ�
      _cam._vTarget -= move;
      if (_finish)
      {
        // �㏸������
        _vPos.y += _fSpeed / 2.f;
        _cam._vTarget.y += _fSpeed / 3.f;
        if (_CT == 1)
        {
          // PLAY��ԂɑJ��
          _pull = false;
          ++_iPieces;
          _cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
          _cam._vPos = _cam._vTarget + _cam._vMemory;
          _statePlayer = State::PLAY;
        }
      }
    }

    if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_X))
    {
      if (_pull && _CT == 0)
      {
        _CT = 10;
        ++_push;
        if (_push >= 12)
        {
          // ��������������
          ChangeVolumeSoundMem(255 * 90 / 100, gGlobal._se["pull"]);
          PlaySoundMem(gGlobal._se["pull"], DX_PLAYTYPE_BACK);
          _CT = 50;
          _finish = true;

        }
      }
    }

  }

  _collision._fRadius = 500.f * _fScale;
  UpdateCollision();   // �R���W�����X�V

  // �v���y���̉�]
  _fRotateAirscrew += utility::PI / 6.f;
  _fRotateBackAirscrew += utility::PI / 6.f;

  // �R������
  if (_cnt % 60 == 0)
  {
    --_iFuel;
    if (_iFuel < 0)
    {
      _iFuel = 0;
    }
  }
  if (_iLife < LIFEMAX / 3)
  {
    if (_cnt % 10 == 0)
    {
      _mode.AddEffectHitBlackSmoke(_vPos);
    }
  }
  if (_ST == 0)
  {
    _isHit = false;
    _isHitObject = false;
    _takeIn = false;
  }

  Vector4 v = { 0.f, 0.f, 0.f };
  if (_isHit)
  {
    ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["se_gunlanding"]);
    PlaySoundMem(gGlobal._se["se_gunlanding"], DX_PLAYTYPE_BACK);
    float rand = static_cast<float>(utility::get_random(-200, 200));
    v = { rand,rand,rand };
    v *= static_cast<float>(_ST) / 20.f;
  }
  if (_takeIn)
  {
    float rand = static_cast<float>(utility::get_random(-100, 100));
    v = { rand,rand,rand };
    v *= static_cast<float>(_ST) / 20.f;
  }
  // �J�����ݒ�X�V
  Vector4 camPos = _cam._vPos + v;
  Vector4 camPosEvent = _cam._vPosEvent + v;
  Vector4 camTarget = _cam._vTarget + v;
  if (_isLerp)
  {
    Vector4 posStart = _cam._vTarget + _cam._vMemory;
    Vector4 posEnd = _cam._vPosEvent;
    _fTime += 0.02f;
    Vector4 camPosNow = posStart * (1.0f - _fTime) + posEnd * _fTime;
    camPosEvent = camPosNow + v;
    if (_fTime > 1.0f)
    {
      _isLerp = false;
    }
  }
  if (_statePlayer == State::EVENT)
  {
    SetCameraPositionAndTarget_UpVecY(ToDX(camPosEvent), ToDX(camTarget));
  }
  else
  {
    SetCameraPositionAndTarget_UpVecY(ToDX(camPos), ToDX(camTarget));
  }
  SetCameraNearFar(_cam._clipNear, _cam._clipFar);

  return true;
}

bool Player::Draw()
{
  ActorMainGame::Draw();
  // �t�H�O�ݒ�
  SetFogEnable(TRUE);
  SetFogColor(255, 255, 205);
  SetFogStartEnd(5000.f, 800000.f);

  matrix44 rotaMatrix = matrix44();
  matrix44 rotaAirscrewMatrix = matrix44();
  matrix44 rotaBackAirscrewMatrix = matrix44();
  matrix44 posMatrix = matrix44();
  matrix44 posAirscrewMatrix = matrix44();
  matrix44 posBackAirscrewMatrix = matrix44();
  matrix44 matrix = matrix44();
  matrix44 airscrewMatrix = matrix44();
  matrix44 backAirscrewMatrix = matrix44();
  // ���f���̉�]�l
  float rX = utility::degree_to_radian(5.f);   // �����������
  if (_statePlayer == State::PLAY)
  {
    rX += _fRotatX + _fAxialX;   // �J�����𓮂��������v���X
  }
  rotaAirscrewMatrix.rotate_y(_fRotateAirscrew, false);
  rotaBackAirscrewMatrix.rotate_x(_fRotateBackAirscrew, false);
  rotaMatrix.rotate_z(_fAxialZ, false);
  rotaMatrix.rotate_x(rX, false);
  rotaMatrix.rotate_y(_fRotatY, false);
  // �ʒu
  Vector4 posAirscrew = { 0.f, 0.f, -200.f };
  Vector4 posBackAirscrew = { 40.f, 450.f, 860.f };
  posMatrix.transfer(_vPos.x, _vPos.y, _vPos.z, false);
  posAirscrewMatrix.transfer(posAirscrew.x, posAirscrew.y, posAirscrew.z, false);
  posBackAirscrewMatrix.transfer(posBackAirscrew.x, posBackAirscrew.y, posBackAirscrew.z, false);
  // �s��ݒ蔽�f
  matrix = rotaMatrix * posMatrix;
  airscrewMatrix = rotaAirscrewMatrix * posAirscrewMatrix * matrix;
  backAirscrewMatrix = rotaBackAirscrewMatrix * posBackAirscrewMatrix * matrix;
  MV1SetMatrix(_handleBody, ToDX(matrix));
  MV1SetMatrix(_handleAirscrew, ToDX(airscrewMatrix));
  MV1SetMatrix(_handleMagnet, ToDX(matrix));
  MV1SetMatrix(_handleBackAirscrew, ToDX(backAirscrewMatrix));

  // ���f���`��
  SetUseLighting(FALSE);
  MV1DrawModel(_handleBody);
  MV1DrawModel(_handleAirscrew);
  MV1DrawModel(_handleMagnet);
  MV1DrawModel(_handleBackAirscrew);
  SetUseLighting(TRUE);

  // �R���W�����`��
  if (!((ModeMainGame&)_mode)._dbgCollisionDraw)
  {
    Vector4 color = { 255, 255, 255 };
    if (_isHit)
    {
      color = { 255, 0, 0 };
    }
    DrawCollision(color);
  }

  return true;
}

void Player::CameraUpdate()
{

  if (_statePlayer == State::EVENT)
  {
    // ������������Ԃ̃J����
    EventCamera();
    return;
  }

  // �O�����ɍ��W(r(length3D),��(theta),��(camerad))
  float sx = _cam._vPos.x - _cam._vTarget.x;
  float sy = _cam._vPos.y - _cam._vTarget.y;
  float sz = _cam._vPos.z - _cam._vTarget.z;
  float length3D = sqrt(sx * sx + sy * sy + sz * sz);
  float camerad = atan2(sz, sx);
  float theta = acos(sy / length3D);


  // �p�x�ύX  ���f��������������
  // Y����]
  if (_game.Getinput().GetRstickX() < -1000)
  {
    camerad += 0.02f;
    _fRotatY += -0.02f;
  }
  else if (_game.Getinput().GetRstickX() > 1000)
  {
    camerad += -0.02f;
    _fRotatY += 0.02f;
  }

  float limitrad = utility::radian_to_degree(theta);  // �x���@�ɕϊ�
  // X����]
  if (_game.Getinput().GetRstickY() < -1000)
  {
    if (limitrad > 40.f)
    {
      theta += -0.02f;
      _fRotatX += -0.02f;
    }
  }
  else if (_game.Getinput().GetRstickY() > 1000)
  {
    if (limitrad < 100.f)
    {
      theta += 0.02f;
      _fRotatX += 0.02f;
    }
  }

  // �J�����ʒu
  _cam._vPos.y = _cam._vTarget.y + cos(theta) * length3D;
  _cam._vPos.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
  _cam._vPos.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);

}

void Player::EventCamera()
{
  // �O�����ɍ��W(r(length3D),��(theta),��(camerad))
  float sx = _cam._vPos.x - _cam._vTarget.x;
  float sy = _cam._vPos.y - _cam._vTarget.y;
  float sz = _cam._vPos.z - _cam._vTarget.z;
  float length3D = sqrt(sx * sx + sy * sy + sz * sz);
  float camerad = atan2(sz, sx);
  float theta = acos(sy / length3D);

  // �p�x�ύX
  // Y����]
  camerad = atan2(sz, sx) + utility::PI;

  // X����]
  float degree = 80.f;
  theta = utility::degree_to_radian(degree);

  float length = 400.f;
  length3D += length * static_cast<float>(_iPieces);

  // �J�����ʒu
  _cam._vPosEvent.y = _vPos.y + cos(theta) * length3D;
  _cam._vPosEvent.x = _vPos.x + length3D * sin(theta) * cos(camerad);
  _cam._vPosEvent.z = _vPos.z + length3D * sin(theta) * sin(camerad);
  float transformY = 200.f;
  _cam._vPosEvent.y += 4000.f + transformY * static_cast<float>(_iPieces);
}

void Player::AddBullet(Vector4 pos)
{
  auto bullet = std::make_shared<Bullet>(_game, static_cast<int>(ActorMainGame::Type::kBullet), _mode);
  bullet->SetPosition(pos);
  _mode.AddEffectFirePlayer(pos);
  bullet->SetDir(_vDir);
  bullet->SetSpeed(bullet->_fSpeed * 2.f);
  bullet->_iDamage = 1;
  bullet->_iType = 2;
  _mode.GetObjectServer3D().Add(bullet);
}