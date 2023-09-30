/*****************************************************************//**
 * @file   ModeMainGame.h
 * @brief  ゲームスクリプト定義
 *
 * @author 阿部健太郎
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
  /** コンストラクタ */
  ModeMainGame(ApplicationBase& game, int layer);
  /** デストラクタ */
  virtual ~ModeMainGame();
  /** 初期化 コンストラクタ時よぶ */
  virtual void Initialize(std::string jsonpath, std::string scriptsname, std::string jsonname);
  /** 計算 毎フレーム呼ばれる */
  virtual bool Update();
  /** 描画 毎フレーム呼ばれる */
  virtual bool Draw();
  /** 後処理 デストラクタ時呼ぶ */
  void Destroy();
  /** デバッグモード時描画 */
  virtual bool DebugDraw();

  /** コリジョン描画 */
  bool _dbgCollisionDraw;


  GameServerShared<ActorMainGame>& GetObjectServer3D()
  {
    return object_main_game;
  }
  /** エフェクト再生 */
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
    PREPARSING,//プレパース
    PARSING,//パース
    GAME,//ゲーム中
    STORY,//ストーリー再生
    CRFEEDIN,//フェードイン中
    CRFEEDOUT,//フェードアウト中
    TIME_WAIT,//時間待ち
    CLICK_WAIT,//ボタンを押すまで待つ
    END,//ゲームの終わり
  };

  /** 先行読み込み */
  void PreParsing();
  /** 読み込み */
  void Parsing();

  /** コマンド */
  /** ステージラベル追加コマンド */
  bool OnCommandStageLabel(unsigned int line, std::vector<std::string>& scripts);
  /** 指定のステージラベルにジャンプするコマンド */
  bool OnCommandJumpLabel(unsigned int line, std::vector<std::string>& scripts);
  /** 登録されたクリア時間より下回っていた場合指定のステージラベルにとぶコマンド */
  bool OnCommandTurning(unsigned int line, std::vector<std::string>& scripts);
  /** ゲームスタートコマンド */
  bool OnCommandStart(unsigned int line, std::vector<std::string>& scripts);
  /** ゲーム終了コマンド */
  bool OnCommandEnd(unsigned int line, std::vector<std::string>& scripts);
  /** フェードイン開始コマンド */
  bool OnCommandCrFeedIn(unsigned int line, std::vector<std::string>& scripts);
  /** フェードアウト開始コマンド */
  bool OnCommandCrFeedOut(unsigned int line, std::vector<std::string>& scripts);
  /** フレーム数待つコマンド */
  bool OnCommandTimeWait(unsigned int line, std::vector<std::string>& scripts);
  /** ストーリモード開始コマンド */
  bool OnCommandStory(unsigned int line, std::vector<std::string>& scripts);

  /** ステージ読み込みコマンド */
  bool OnCommandStage(unsigned int line, std::vector<std::string>& scripts);
  /** スカイスフィア追加コマンド */
  bool OnCommandSkySphere(unsigned int line, std::vector<std::string>& scripts);
  /** プレイヤー追加コマンド */
  bool OnCommandPLayer(unsigned int line, std::vector<std::string>& scripts);
  /** ガンシップ追加コマンド */
  bool OnCommandGunShip(unsigned int line, std::vector<std::string>& scripts);
  /** 単品の対空砲追加コマンド */
  bool OnCommandEnemyAAA(unsigned int line, std::vector<std::string>& scripts);
  /** エリア上にランダム配置コマンド */
  bool OnCommandAreaAAA(unsigned int line, std::vector<std::string>& scripts);
  /** ステージ上に1個だけものを置くコマンド */
  bool OnCommandObject(unsigned int line, std::vector<std::string>& scripts);
  /** エリア上にものをランダムで配置コマンド */
  bool OnCommandAreaObj(unsigned int line, std::vector<std::string>& scripts);
  /** 敵スポーン場所配置コマンド */
  bool OnCommandAreaSpawn(unsigned int line, std::vector<std::string>& scripts);
  /** 燃料回復場所配置コマンド */
  bool OnCommandSupply(unsigned int line, std::vector<std::string>& scripts);
  /** 中に入るとキャラがしゃべるものを置くコマンド */
  bool OnCommandCommunication(unsigned int line, std::vector<std::string>& scripts);
  /** 当たったら後ろに下がる見えない当たり判定を置くコマンド */
  bool OnCommandNoEntry(unsigned int line, std::vector<std::string>& scripts);
  /** td::vector<std::string>の1から3をmath::Vector4に変換する関数 */
  bool IsSetVrctor4(math::Vector4& set, std::vector<std::string>& scripts);





  /** フレーム数待つ時に使われるUpdate */
  void TimeWait();
  /** 文字列に対応した行数を取得 */
  bool GetLineNumber(const std::string& str, unsigned int& line) const;
  /** フェードイン時に使われるUpdate */
  void CrfiUpdate();
  /** フェードアウト時に使われるUpdate */
  void CrfoUpdate();
  /** フェードイン描画 */
  void DrawFeedIn()const;
  /** フェードアウト描画 */
  void DrawFeedOut()const;

  /** ScriptsDataにアクセスするポインタ */
  std::unique_ptr<ScriptsData> scripts_data;
  /** ステージ名を格納するvector */
  std::vector < std::unique_ptr <CommandLabel>> label_list;
  std::vector < std::unique_ptr < CommandCrFeedIn>> crfi_list;
  std::vector < std::unique_ptr < CommandCrFeedOut>> crfo_list;


  /** ゲームのステータス */
  ScriptState state;
  /** ゲームコマンドに使われる文字列をキーとした関数ポインタ */
  using FunctionGameCommand = std::map<std::string, bool(ModeMainGame::*)(unsigned int, std::vector<std::string>&)>;
  /** スクリプトの最大行数 */
  unsigned int max_line;
  /** 今の行数 */
  unsigned int now_line;
  /** 待つ時間 */
  unsigned int wait_count;
  /** フェードアウトインするときに使うα値 */
  float alpha;
  /** フェードアウトインするときに使うフレーム数 */
  float feedcount;
  /** ステージ名 */
  std::string stage_name;
  /** ゲームオーバー名 */
  std::string game_over_name;
  /** ゲームクリア名 */
  std::string game_clear_name;
  /** ゲームスタート時間 */
  int start_time;
  /** プレイヤーが外に出たときtrueにしui表示 */
  bool is_player_danger;
  /** プレイヤーが給油場に入ったらtrueにしui表示 */
  bool is_player_in_supply;
  /** 世界の範囲 */
  float world_range_x;
  float world_range_y;
  float world_range_z;
  /** プレイヤーが外に出たときに表示するuiのハンドル */
  int cg_outobarea[74];
  /** プレイヤーが給油所に入った時表示するui */
  int cg_in_supply;
  /** プレイヤーが外に出たらマイナス1ずつし0になったらゲームオーバー */
  int game_over_timer;

protected:
  /** プレイヤーやものを追加しておくサーバー */
  GameServerShared<ActorMainGame> object_main_game;
  /** ui関係を登録するサーバー */
  GameServerUnique<UIBase> ui_player;
};
