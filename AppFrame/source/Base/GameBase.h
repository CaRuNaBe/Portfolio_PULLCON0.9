/*****************************************************************//**
 * \file   GameBase.h
 * \brief  �Q�[���ɓo�ꂷ����̂̊��N���X
 *
 * \author ���������Y
 * \date    December 2022
 *********************************************************************/
#pragma once
class ApplicationBase;
class GameBase
{
public:
  /** �R���X�g���N�^ */
  GameBase(ApplicationBase& _game,int layer)
    : _game(_game)
    ,layer(layer)
    ,is_dead(false)
    ,is_update_skip(false)
    ,is_draw_skip(false)
    ,cnt(0)
  {}
  /** �f�X�g���N�^ */
  virtual ~GameBase()
  {};
  /** �X�V */
  virtual bool Update() = 0;
  /** �`�� */
  virtual bool Draw() = 0;
  /** �f�o�b�O���`�� */
  virtual bool DebugDraw() = 0;
  /** ����ł��邩 */
  virtual bool IsDead()
  {
    return is_dead;
  }
  /** ���� */
  virtual void Dead()
  {
    is_dead = true;
  }
  /** �X�V���Ă����� */
  virtual bool GetUpdateSkip()
  {
    return is_update_skip;
  }
  /** �Z�b�g�֐� */
  virtual void SetUpdateSkip(bool update_skip)
  {
    is_update_skip = update_skip;
  }
  /** is_draw_skip�擾 */
  virtual bool GetDrawSkip()
  {
    return is_draw_skip;
  }
  /** �Z�b�g�֐� */
  virtual void SetDrawSkip(bool draw_skip)
  {
    is_draw_skip = draw_skip;
  }
  /** ���C���[�擾 */
  virtual int GetLayer()
  {
    return layer;
  }

protected:
  /** ApplicationBase�i�[ */
  ApplicationBase& _game;
  /** ���񂾂�true */
  bool is_dead;
  /** �X�V���΂��Ƃ�true */
  bool is_update_skip;
  /** �`�悵�Ȃ��Ƃ�true */
  bool is_draw_skip;
  /** �`�揇 */
  int layer;
  /** �J�E���g */
  int cnt;
};

