/*****************************************************************//**
 * @file   ModeMainGame.h
 * @brief  �Q�[���X�N���v�g��`
 *
 * @author ���������Y
 * @date   November 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "../maingame/ActorMainGame.h"
#include "../ui/UIBase.h"
#include <vector>
#include <memory>
#include <string>
#include <array>

class CommandLabel;
class CommandChoice;
class UIBase;

class ModeMainGame :public GameBase
{
public:
  /** �R���X�g���N�^ */
  ModeMainGame(ApplicationBase& game, int layer);
  /** �f�X�g���N�^ */
  virtual ~ModeMainGame();
  /** ������ �R���X�g���N�^����� */
  virtual void Initialize(std::string jsonpath, std::string scriptsname, std::string jsonname);
  /** �v�Z ���t���[���Ă΂�� */
  virtual bool Update();
  /** �`�� ���t���[���Ă΂�� */
  virtual bool Draw();
  /** �㏈�� �f�X�g���N�^���Ă� */
  void Destroy();
  /** �f�o�b�O���[�h���`�� */
  virtual bool DebugDraw();

  /** �R���W�����`�� */
  bool _dbgCollisionDraw;


  GameServerShared<ActorMainGame>& GetObjectServer3D()
  {
    return object_main_game;
  }
  /** �G�t�F�N�g�Đ� */
  void AddEffectHitPlayerFrame(const math::Vector4& pos);
  void AddEffectSpawnAmmo(const math::Vector4& pos);
  void AddEffectDestroyAmmo(const math::Vector4& pos);
  void AddEffectHitBlackSmoke(const math::Vector4& pos);
  void AddEffectDeathObject(const math::Vector4& pos);
  void AddEffectFirePlayer(const math::Vector4& pos);
  void AddEffectFireGunship(const math::Vector4& pos);
  void AddEffectHitEnemy(const math::Vector4& pos);
private:
  enum class ScriptState
  {
    PREPARSING,//�v���p�[�X
    PARSING,//�p�[�X
    GAME,//�Q�[����
    STORY,//�X�g�[���[�Đ�
    CRFEEDIN,//�t�F�[�h�C����
    CRFEEDOUT,//�t�F�[�h�A�E�g��
    TIME_WAIT,//���ԑ҂�
    CLICK_WAIT,//�{�^���������܂ő҂�
    END,//�Q�[���̏I���
  };

  /** ��s�ǂݍ��� */
  void PreParsing();
  /** �ǂݍ��� */
  void Parsing();

  /** �R�}���h */
  /** �X�e�[�W���x���ǉ��R�}���h */
  bool OnCommandStageLabel(unsigned int line, std::vector<std::string>& scripts);
  /** �w��̃X�e�[�W���x���ɃW�����v����R�}���h */
  bool OnCommandJumpLabel(unsigned int line, std::vector<std::string>& scripts);
  /** �o�^���ꂽ�N���A���Ԃ�艺����Ă����ꍇ�w��̃X�e�[�W���x���ɂƂԃR�}���h */
  bool OnCommandTurning(unsigned int line, std::vector<std::string>& scripts);
  /** �Q�[���X�^�[�g�R�}���h */
  bool OnCommandStart(unsigned int line, std::vector<std::string>& scripts);
  /** �Q�[���I���R�}���h */
  bool OnCommandEnd(unsigned int line, std::vector<std::string>& scripts);
  /** �t�F�[�h�C���J�n�R�}���h */
  bool OnCommandCrFeedIn(unsigned int line, std::vector<std::string>& scripts);
  /** �t�F�[�h�A�E�g�J�n�R�}���h */
  bool OnCommandCrFeedOut(unsigned int line, std::vector<std::string>& scripts);
  /** �t���[�����҂R�}���h */
  bool OnCommandTimeWait(unsigned int line, std::vector<std::string>& scripts);
  /** �X�g�[�����[�h�J�n�R�}���h */
  bool OnCommandStory(unsigned int line, std::vector<std::string>& scripts);

  /** �X�e�[�W�ǂݍ��݃R�}���h */
  bool OnCommandStage(unsigned int line, std::vector<std::string>& scripts);
  /** �X�J�C�X�t�B�A�ǉ��R�}���h */
  bool OnCommandSkySphere(unsigned int line, std::vector<std::string>& scripts);
  /** �v���C���[�ǉ��R�}���h */
  bool OnCommandPLayer(unsigned int line, std::vector<std::string>& scripts);
  /** �K���V�b�v�ǉ��R�}���h */
  bool OnCommandGunShip(unsigned int line, std::vector<std::string>& scripts);
  /** �P�i�̑΋�C�ǉ��R�}���h */
  bool OnCommandEnemyAAA(unsigned int line, std::vector<std::string>& scripts);
  /** �G���A��Ƀ����_���z�u�R�}���h */
  bool OnCommandAreaAAA(unsigned int line, std::vector<std::string>& scripts);
  /** �X�e�[�W���1�������̂�u���R�}���h */
  bool OnCommandObject(unsigned int line, std::vector<std::string>& scripts);
  /** �G���A��ɂ��̂������_���Ŕz�u�R�}���h */
  bool OnCommandAreaObj(unsigned int line, std::vector<std::string>& scripts);
  /** �G�X�|�[���ꏊ�z�u�R�}���h */
  bool OnCommandAreaSpawn(unsigned int line, std::vector<std::string>& scripts);
  /** �R���񕜏ꏊ�z�u�R�}���h */
  bool OnCommandSupply(unsigned int line, std::vector<std::string>& scripts);
  /** ���ɓ���ƃL����������ׂ���̂�u���R�}���h */
  bool OnCommandCommunication(unsigned int line, std::vector<std::string>& scripts);
  /** ������������ɉ����錩���Ȃ������蔻���u���R�}���h */
  bool OnCommandNoEntry(unsigned int line, std::vector<std::string>& scripts);
  /** td::vector<std::string>��1����3��math::Vector4�ɕϊ�����֐� */
  bool IsSetVrctor4(math::Vector4& set, std::vector<std::string>& scripts);





  /** �t���[�����҂��Ɏg����Update */
  void TimeWait();
  /** ������ɑΉ������s�����擾 */
  bool GetLineNumber(const std::string& str, unsigned int& line) const;
  /** �t�F�[�h�C�����Ɏg����Update */
  void CrfiUpdate();
  /** �t�F�[�h�A�E�g���Ɏg����Update */
  void CrfoUpdate();
  /** �t�F�[�h�C���`�� */
  void DrawFeedIn()const;
  /** �t�F�[�h�A�E�g�`�� */
  void DrawFeedOut()const;

  /** ScriptsData�ɃA�N�Z�X����|�C���^ */
  std::unique_ptr<ScriptsData> scripts_data;
  /** �X�e�[�W�����i�[����vector */
  std::vector < std::unique_ptr <CommandLabel>> label_list;
  std::vector < std::unique_ptr < CommandCrFeedIn>> crfi_list;
  std::vector < std::unique_ptr < CommandCrFeedOut>> crfo_list;


  /** �Q�[���̃X�e�[�^�X */
  ScriptState state;
  /** �Q�[���R�}���h�Ɏg���镶������L�[�Ƃ����֐��|�C���^ */
  using FunctionGameCommand = std::map<std::string, bool(ModeMainGame::*)(unsigned int, std::vector<std::string>&)>;
  /** �X�N���v�g�̍ő�s�� */
  unsigned int max_line;
  /** ���̍s�� */
  unsigned int now_line;
  /** �҂��� */
  unsigned int wait_count;
  /** �t�F�[�h�A�E�g�C������Ƃ��Ɏg�����l */
  float alpha;
  /** �t�F�[�h�A�E�g�C������Ƃ��Ɏg���t���[���� */
  float feedcount;
  /** �X�e�[�W�� */
  std::string stage_name;
  /** �Q�[���I�[�o�[�� */
  std::string game_over_name;
  /** �Q�[���N���A�� */
  std::string game_clear_name;
  /** �Q�[���X�^�[�g���� */
  int start_time;
  /** �v���C���[���O�ɏo���Ƃ�true�ɂ�ui�\�� */
  bool is_player_danger;
  /** �v���C���[��������ɓ�������true�ɂ�ui�\�� */
  bool is_player_in_supply;
  /** ���E�͈̔� */
  float world_range_x;
  float world_range_y;
  float world_range_z;
  /** �v���C���[���O�ɏo���Ƃ��ɕ\������ui�̃n���h�� */
  int cg_outobarea[74];
  /** �v���C���[���������ɓ��������\������ui */
  int cg_in_supply;
  /** �v���C���[���O�ɏo����}�C�i�X1����0�ɂȂ�����Q�[���I�[�o�[ */
  int game_over_timer;

protected:
  /** �v���C���[����̂�ǉ����Ă����T�[�o�[ */
  GameServerShared<ActorMainGame> object_main_game;
  /** ui�֌W��o�^����T�[�o�[ */
  GameServerUnique<UIBase> ui_player;
};
