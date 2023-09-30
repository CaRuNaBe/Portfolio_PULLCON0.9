#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
// �J����
class Camera
{
public:
  Vector4 _vPos;// �ʒu
  Vector4 _vPosEvent;// �����������J�����ʒu
  Vector4 _vTarget; // �����_
  Vector4 _vMemory; // �x�N�g���ۑ��p
  float _clipNear, _clipFar;// �N���b�v
};

class Player : public ActorMainGame
{
public:
  Player(ApplicationBase& game, int layer, ModeMainGame& mode);
  virtual ~Player();
  virtual Type GetType()
  {
    return Type::kPlayer;
  }
  // �v���C���[�̏��
  enum class State
  {
    NUM, //�������
    PLAY,//�v���C�A�u�����
    EVENT//�C�x���g���
  };

  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

  void CameraUpdate();    // �J�����X�V
  void EventCamera();    // �J����
  void AddBullet(Vector4 pos);
  State GetPlayerState()
  {
    return _statePlayer;
  }
  int GetPush()
  {
    return _push;
  }
protected:
  // �J����
  Camera _cam;

  State  _statePlayer;

  Vector4 _vMoveDir;
  int    _push;                 // �{�^���A�ŉ�
  bool   _isLerp;               // ���`��Ԃ��邩
  bool   _isHit;                // ����������
  bool   _isHitObject;          // �I�u�W�N�g�Ɠ���������
  float  _fSpeedIint;           // �v���C���[�̑��x�̏����l
  float  _fTime;                // ���`��Ԃ̌o�ߎ���
  float  _fRotateAirscrew;      // �v���y���̉�]
  float  _fRotateBackAirscrew;  // �o�b�N�v���y���̉�]
  float  _fAxialX;              // �w���R�v�^�[��X����]
  float  _fAxialZ; // �w���R�v�^�[��Z����]

  int    _handleBody;
  int    _handleAirscrew;
  int    _handleMagnet;
  int    _handleBackAirscrew;
  int    _handleStage;


};
