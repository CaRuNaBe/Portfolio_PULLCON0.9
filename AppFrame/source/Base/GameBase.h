/*****************************************************************//**
 * \file   GameBase.h
 * \brief  ゲームに登場するものの基底クラス
 *
 * \author 阿部健太郎
 * \date    December 2022
 *********************************************************************/
#pragma once
class ApplicationBase;
class GameBase
{
public:
  /** コンストラクタ */
  GameBase(ApplicationBase& _game,int layer)
    : _game(_game)
    ,layer(layer)
    ,is_dead(false)
    ,is_update_skip(false)
    ,is_draw_skip(false)
    ,cnt(0)
  {}
  /** デストラクタ */
  virtual ~GameBase()
  {};
  /** 更新 */
  virtual bool Update() = 0;
  /** 描画 */
  virtual bool Draw() = 0;
  /** デバッグ時描画 */
  virtual bool DebugDraw() = 0;
  /** 死んでいるか */
  virtual bool IsDead()
  {
    return is_dead;
  }
  /** 死んだ */
  virtual void Dead()
  {
    is_dead = true;
  }
  /** 更新していいか */
  virtual bool GetUpdateSkip()
  {
    return is_update_skip;
  }
  /** セット関数 */
  virtual void SetUpdateSkip(bool update_skip)
  {
    is_update_skip = update_skip;
  }
  /** is_draw_skip取得 */
  virtual bool GetDrawSkip()
  {
    return is_draw_skip;
  }
  /** セット関数 */
  virtual void SetDrawSkip(bool draw_skip)
  {
    is_draw_skip = draw_skip;
  }
  /** レイヤー取得 */
  virtual int GetLayer()
  {
    return layer;
  }

protected:
  /** ApplicationBase格納 */
  ApplicationBase& _game;
  /** 死んだらtrue */
  bool is_dead;
  /** 更新を飛ばすときtrue */
  bool is_update_skip;
  /** 描画しないときtrue */
  bool is_draw_skip;
  /** 描画順 */
  int layer;
  /** カウント */
  int cnt;
};

