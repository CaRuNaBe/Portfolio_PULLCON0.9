#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
#include <string>
#include <sstream>
#include <array>
class EnemyAAA : public ActorMainGame
{
public:
  EnemyAAA(ApplicationBase& game, int layer, ModeMainGame& mode, int min_id, int max_id, int pile_num, float scale, Vector4 _vPosi);
  virtual ~EnemyAAA();
  virtual Type GetType()
  {
    return Type::kEnemyAAA;
  }
  // �΋�C�̏��
  enum class State
  {
    NUM,//�n���̑΋�C
    PLAY,//�v���C�A�u�����
    EVENT,//�C�x���g���
    WEAPON//���퉻
  };

  virtual void Initialize(int pile_num, Vector4 _vPosi, float scale);
  virtual bool Update();
  virtual bool Draw();

  virtual void Damage();
  void AddBullet(const int& theta_split_num, const int& phi_split_num, const int& theta_degree_lower, const int& theta_degree_upper, const int& phi_degree_lower, const int& phi_degree_upper);
  void AddPieces(int min_id, int max_id, int pile_num, float scale);
  void GetSearch();
  void SetDamage();
  void SetStateAAA();

  void SetAxialX(float _x_rad)
  {
    _fAxialX = _x_rad;
  }
  void SetAxialY(float _y_rad)
  {
    _fAxialY = _y_rad;
  }
  void SetType(int _aim_player)
  {
    _iEnemyType = _aim_player;
  }
protected:
  State   _stateAAA;

  int    _iEnemyType;    // �^�C�v 0,�ǔ��� 1,�Œ莮
  int    _iSurvivalTime; // �ˌ�����e�̐�������
  int    _iPossession;   // �΋�C�p�[�c�̏��L��
  float  _fAxialY;       // Y����](�x���@)
  float  _fAxialX;       // X����](�x���@)
  bool   _get;           // �v���C���[��T�m������

  int    _handle_body;
  int    _handle_turret;

  int AAA_ID;
  std::vector<int>bullet_state;

};
