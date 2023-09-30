/*****************************************************************//**
 * \file   input_manager.h
 * \brief  ���͊Ǘ��N���X��`
 *
 * \author ���������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include<DxLib.h>
class InputManager
{
public:
  InputManager();
  ~InputManager();
  /** �X�V */
  bool Update();

  //���͎擾�֐�
  /** �R���g���[���[�̊u�t���[������ */
  const bool& EveryOtherKey(int button,const int FrequencyFrame);
  /** �R���g���[���[�̖��t���[������ */
  const int GetKey(int button);
  /** �R���g���[���[�̉������Ƃ��̓��� */
  const int GetTrg(int button);
  /** �R���g���[���[�̗������Ƃ��̓��� */
  const int GetRel(int button);

  /** xinput�u�t���[������ */
  const bool& XinputEveryOtherKey(int button,const int FrequencyFrame);
  /** xinput���g���K�[�̊u�t���[������ */
  const bool& XinputEveryOtherLeftTrigger(const int FrequencyFrame);
  /** xinput�E�g���K�[�̊u�t���[������ */
  const bool& XinputEveryOtherRightTrigger(const int FrequencyFrame);
  /** xinput���g���K�[�̐��l�擾 */
  const unsigned char& GetLeftTrigger();
  /** xinput�E�g���K�[�̐��l�擾 */
  const unsigned char& GetRightTrigger();
  /** ���X�e�B�b�Nx���擾 */
  short& GetLstickX();
  /** ���X�e�B�b�Ny���擾 */
  short& GetLstickY();
  /** �E�X�e�B�b�Nx���擾 */
  const short& GetRstickX();
  /** �E�X�e�B�b�Ny���擾 */
  const short& GetRstickY();
  /** xinput���t���[������ */
  const bool GetKeyXinput(const int button);
  /** xinput�������Ƃ��̓��� */
  const bool GetTrgXinput(const int button);
  /** xinput�������Ƃ��̓��� */
  const bool GetRelXinput(const int button);
private:
  XINPUT_STATE _gxKey;
  XINPUT_STATE _gxTrg;
  XINPUT_STATE _gxRel;
  int _gKey,_gTrg,_gRel;
  int Key_skip_count;
  int LeftTrigger_skip_count;
  int RightTrigger_skip_count;
  bool is_Click_on_Key;
  bool is_Click_on_R_Trigger;
  bool is_Click_on_L_Trigger;
};
