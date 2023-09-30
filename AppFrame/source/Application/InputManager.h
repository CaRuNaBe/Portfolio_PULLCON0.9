/*****************************************************************//**
 * \file   input_manager.h
 * \brief  入力管理クラス定義
 *
 * \author 阿部健太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include<DxLib.h>
class InputManager
{
public:
  InputManager();
  ~InputManager();
  /** 更新 */
  bool Update();

  //入力取得関数
  /** コントローラーの隔フレーム入力 */
  const bool& EveryOtherKey(int button,const int FrequencyFrame);
  /** コントローラーの毎フレーム入力 */
  const int GetKey(int button);
  /** コントローラーの押したときの入力 */
  const int GetTrg(int button);
  /** コントローラーの離したときの入力 */
  const int GetRel(int button);

  /** xinput隔フレーム入力 */
  const bool& XinputEveryOtherKey(int button,const int FrequencyFrame);
  /** xinput左トリガーの隔フレーム入力 */
  const bool& XinputEveryOtherLeftTrigger(const int FrequencyFrame);
  /** xinput右トリガーの隔フレーム入力 */
  const bool& XinputEveryOtherRightTrigger(const int FrequencyFrame);
  /** xinput左トリガーの数値取得 */
  const unsigned char& GetLeftTrigger();
  /** xinput右トリガーの数値取得 */
  const unsigned char& GetRightTrigger();
  /** 左スティックx軸取得 */
  short& GetLstickX();
  /** 左スティックy軸取得 */
  short& GetLstickY();
  /** 右スティックx軸取得 */
  const short& GetRstickX();
  /** 右スティックy軸取得 */
  const short& GetRstickY();
  /** xinput毎フレーム入力 */
  const bool GetKeyXinput(const int button);
  /** xinput押したときの入力 */
  const bool GetTrgXinput(const int button);
  /** xinput離したときの入力 */
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
