/*****************************************************************//**
 * \file   GameServerShared.h
 * \brief  �Q�[���ɓo�ꂷ����̂��ׂĂ��Ǘ�����N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
template<class T> class GameServerShared
{
  using GameBasePtr = std::shared_ptr<T>;
  using TypeModes = std::vector<GameBasePtr>;
public:
  /** �R���X�g���N�^ */
  GameServerShared() :_updating(false)
  {}
  /** �f�X�g���N�^ */
  ~GameServerShared()
  {
    Clear();
  }
  /** _vObjects�擾 */
  TypeModes& GetObjects()
  {
    return _vObjects;
  }
  /** _vObjects������ */
  void Clear()
  {
    _vObjects.clear();
  }
  /** _updating��true�̎��͒ǉ��\�񂷂� */
  void Add(GameBasePtr object)
  {
    if( _updating )
    {
      _vPendingObjects.push_back(object);
    } else
    {
      _vObjects.push_back(object);
    }
  }
  /** �폜�\�񂷂� */
  void Del(T& object)
  {
    object.Dead();
  }
  /** �X�V���� ���t���[���Ă΂�� */
  bool Update()
  {
    _updating = true;//�����J�n
    for( auto&& object : _vObjects )
    {
      if( object->GetUpdateSkip() )
      {
        continue;//�X�L�b�v����
      }
      object->Update();
    }

    // ���C���[�ɂ��\�[�g
    std::sort(_vObjects.begin(),_vObjects.end(),[](const GameBasePtr& ch1,const GameBasePtr& ch2)
              {
                return ch1->GetLayer() < ch2->GetLayer();
              });

    _updating = false;//�����I��
    AddPendingObjects();//_vObjects�ɒǉ������̃t���[�����瓮����
    DeleteObjects(); // �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����
    return true;
  }
  /** �`�揈�� ���t���[���Ă΂�� */
  bool Draw()
  {
    for( auto&& object : _vObjects )
    {
      if( object->GetDrawSkip() )
      {
        continue;//�`��X�L�b�v
      }
      object->Draw();
    }
#if _DEBUG
    for( auto&& object : _vObjects )
    {
      object->DebugDraw();
    }
#endif
    return true;
  }
protected:
  /** ���������̂�����R���e�i */
  TypeModes _vObjects;
  /** ��Œǉ����邽�߂̃R���e�i */
  TypeModes _vPendingObjects;
  /** _vObjects���񂵂Ă���Ƃ���true�ɂ��� */
  bool _updating;
  /** Del�֐��ŃI�u�W�F�N�g������ł����ꍇ_vObjects����erase */
  void DeleteObjects()
  {
    // �R���e�i���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
    for( auto ite = _vObjects.begin(); ite != _vObjects.end(); )
    {
      if( (*ite)->IsDead() )
      {
        ite = _vObjects.erase(ite); // �����object���̂��̂��폜�����
      } else
      {
        ++ite;//���ɐi�߂�
      }
    }
  }
  /** _vPendingObjects �̒��ɂ�����̂� _vObjects �ɒǉ� */
  void AddPendingObjects()
  {
    // _vPendingObjects -> _vObjects �ɒǉ�
    _vObjects.insert(_vObjects.end(),make_move_iterator(_vPendingObjects.begin()),make_move_iterator(_vPendingObjects.end()));
    // _vPendingObjects ���N���A
    _vPendingObjects.clear();
  }
};
