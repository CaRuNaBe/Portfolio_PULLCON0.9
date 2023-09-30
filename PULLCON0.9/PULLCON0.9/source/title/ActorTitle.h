#pragma once
#include "appframe.h"
#include "../mode/ModeTitle.h"
#include "../mode/ModeTitle.h"
class ActorTitle:public GameBase
{
public:
  enum class Type
  {
    // ��ʂ̗񋓌^
    /** �^�C�g����� */
    KBASE,     // 0 �A�N�^�[
    KPLAYER,     // 1 �v���C���[
    KTITLELOGO,     // 2 �^�C�g�����S
    KGAMESTARTLOGO, // 3 �Q�[���X�^�[�g���S
    KGAMESTARTGUID,  // 4 �Q�[���X�^�[�g�K�C�h
    KCREDITLOGO,   // 5 �N���W�b�g���S
    KCREDITGUID,     // 6 �N���W�b�g�K�C�h
    KENDLOGO,     // 7 �Q�[���I�����S
    KENDGUID,        // 8 �Q�[���I���K�C�h
  };
  virtual Type GetType() = 0;

  ActorTitle( ApplicationBase& game,int layer,ModeTitle& mode );
  virtual ~ActorTitle();

  virtual void Initialize();/*������*/
  virtual bool Update();//
  virtual void UpdateCollision();
  virtual bool Draw();
  virtual void DrawCollision();
  virtual bool DebugDraw();
  virtual  math::AABB& GetCollision()
  {
    return _collision;
  }

  virtual  math::Vector2& GetPosition()
  {
    return _pos;
  }
  virtual void SetPosition( const math::Vector2& pos )
  {
    _pos = pos;
  }
  virtual  math::Vector2& GetSize()
  {
    return _size;
  }
  virtual void SetSize( math::Vector2& size )
  {
    _size = size;
  }
  virtual  bool  IsHitObject( ActorTitle& object );// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩�H
protected:
  ModeTitle& _mode;
  math::Vector2 _pos;// ���W
  math::Vector2 _size; // �傫��
  float _spd; // �ړ����x
  math::AABB _collision; // �����蔻��p��`
  math::Vector2 _colPos,_colSize;// �����蔻��ʒu�T�C�Y(_pos����̍���)
  int _cnt;// ����J�E���^
  const int LOW_MOVEMENT_PULL;
  const int UP_MOVEMENT_PULL;
};
