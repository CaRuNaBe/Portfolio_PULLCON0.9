Portfolio_PULLCON0.9  
├─ Dxlib(DXライブラリ格納ディレクトリ)  
│      
├─ picojson(C++のJSONパーサpicojson.hが入っているファイル)  
│   
├─ AppFrame  
│　│  
│　└─ source    
│　　　│　appframe.h(フレームのインクルード済みヘッダー)  
│　　　│  
│　　　├─ Application (エントリーポイントとゲームの入力計算描画が入ったファイル)  
│　　　│　　ApplicationBase.cpp  
│　　　│　　ApplicationBase.h(アプリケーションの実体となる基底クラス)  
│　　　│　　InputManager.cpp  
│　　　│　　InputManager.h(入力系をまとめたクラス)  
│　　　│　　WinMain.cpp(エントリーポイント)  
│　　　│      
│　　　├─ Base(オブジェクトの基底クラスとそれを管理するクラスが入ったファイル)  
│　　　│　　GameBase.cpp  
│　　　│　　GameBase.h(基底クラス,オブジェクト作る時ここから派生する)  
│　　　│　　GameServerShared.cpp  
│　　　│　　GameServerShared.h(オブジェクトをシェアードポインタで作りサーバーで管理したいときに使うクラス)  
│　　　│　　GameServerUnique.cpp  
│　　　│　　GameServerUnique.h(オブジェクトをユニークポインタで作りサーバーで管理したいときに使うクラス)  
│　　　│      
│　　　├─ Math(計算系をまとめたファイル)  
│　　　│　　2dCollision.cpp  
│　　　│　　2dCollision.h(2次元的当たり判定をまとめたクラス)  
│　　　│　　3dCollision.cpp  
│　　　│　　3dCollision.h(3次元的当たり判定をまとめたクラス)  
│　　　│　　dx_utility.cpp  
│　　　│　　dx_utility.h(dxライブラリで使われる構造体と自分の構造体を変換する関数をまとめたファイル)  
│　　　│　　Easing.cpp  
│　　　│　　Easing.h(イージング関数群をまとめたクラス)  
│　　　│　　math.cpp  
│　　　│　　math.h(計算系のインクルードファイルをまとめたもの)  
│　　　│　　matrix33.cpp  
│　　　│　　matrix33.h(3*3行列クラス)  
│　　　│　　matrix44.cpp  
│　　　│　　matrix44.h(4*4行列クラス)  
│　　　│　　Polar2.cpp  
│　　　│　　Polar2.h(2次元極座標の計算クラス)  
│　　　│　　Polar3D.cpp  
│　　　│　　Polar3D.h(3次元極座標の計算クラス)  
│　　　│　　rect.cpp  
│　　　│　　rect.h(矩形を定義したクラス)  
│　　　│　　utility.cpp  
│　　　│　　utility.h(その他まとめられない計算関数や円周率など定数を入れた静的クラス)  
│　　　│　　vector2.cpp  
│　　　│　　vector2.h(2dベクトルの計算クラス)  
│　　　│　　vector4.cpp  
│　　　│　　vector4.h(3dベクトルの計算クラス)  
│　　　│  
│　　　├─ ResourceServer(画像を管理するクラスが入ったファイル)  
│　　　│　　ResourceServer.cpp  
│　　　│　　ResourceServer.h  
│　　　│      
│　　　└─ Script(スクリプトのコマンドを処理するクラスとスクリプトの文字を操作すクラスをまとめたファイル)  
│　　　　　CommandBase.h(コマンド操作するときの基底クラス)  
│　　　　　CommandCrFeedIn.cpp  
│　　　　　CommandCrFeedIn.h(カラーでフェードインするときに処理するクラス)  
│　　　　　CommandCrFeedOut.cpp    
│　　　　　CommandCrFeedOut.h(カラーでフェードアウトするときに処理するクラス)  
│　　　　　CommandDrawIn.cpp  
│　　　　　CommandDrawIn.h(画像をフェードインするときに処理するクラス)  
│　　　　　CommandDrawOut.cpp  
│　　　　　CommandDrawOut.h(画像をフェードアウトするときに処理するクラス)  
│　　　　　CommandDrawRect.cpp  
│　　　　　CommandDrawRect.h(四角形を描画するときに処理するクラス)  
│　　　　　CommandDrawString.cpp  
│　　　　　CommandDrawString.h(文字を描画する時に処理するクラス)  
│　　　　　CommandDrawTime.cpp  
│　　　　　CommandDrawTime.h(時間を描画する時に処理するクラス)  
│　　　　　CommandImageLoad.cpp  
│　　　　　CommandImageLoad.h(画像をロードするときに処理するクラス)  
│　　　　　CommandLabel.cpp  
│　　　　　CommandLabel.h(ラベルを保存するときに処理するクラス)  
│　　　　　CommandMessage.cpp  
│　　　　　CommandMessage.h(絵を動かしながら音を流すときに処理するクラス)  
│　　　　　CommandMoviePlay.cpp  
│　　　　　CommandMoviePlay.h(動画を再生させたいときに処理するクラス)  
│　　　　　CommandMusicBack.cpp  
│　　　　　CommandMusicBack.h(音楽を一回だけ流すコマンドを処理するクラス)  
│　　　　　CommandMusicLoop.cpp  
│　　　　　CommandMusicLoop.h(音楽をループ再生するときに処理するクラス)  
│　　　　　CommandMusicStop.cpp  
│　　　　　CommandMusicStop.h(音を止めたいときに処理するクラス)  
│　　　　　CommandSeLoad.cpp  
│　　　　　CommandSeLoad.h(音をメモリに読み込むときに処理するクラス)  
│　　　　　ScriptsData.cpp  
│　　　　　ScriptsData.h(jsonファイルの呼び込みクラス)  
│　　　　　ScriptsString.cpp  
│　　　　　ScriptsString.h(スクリプトに使われる文字列に対するユーティリティ処理)  
│                  
└─ PULLCON0.9  
　　│  
　　└─ PULLCON0.9  
　　　　│  
　　　　└─ source  
　　　　　　│　ApplicationGlobal.cpp  
　　　　　　│　ApplicationGlobal.h(グローバル変数を置く静的クラス)  
　　　　　　│　ApplicationMain.cpp  
　　　　　　│　ApplicationMain.h(ゲームの実体となる派生クラス)  
　　　　　　│  
　　　　　　├─ maingame(ゲーム内(ModeMainGame)に登場するオブジェクトをまとめたファイル)  
　　　　　　│　　ActorMainGame.cpp  
　　　　　　│　　ActorMainGame.h(ModeMainGameで使われるオブジェクトの基底クラス)  
　　　　　　│　　AreaCommunication.cpp  
　　　　　　│　　AreaCommunication.h(コミュニケーションエリア)  
　　　　　　│　　AreaEnemySpawn.cpp  
　　　　　　│　　AreaEnemySpawn.h(エネミースポーンエリア)  
　　　　　　│　　AreaNoEntry.cpp  
　　　　　　│　　AreaNoEntry.h(侵入不能エリア)  
　　　　　　│　　AreaSupply.cpp  
　　　　　　│　　AreaSupply.h(燃料回復エリア)  
　　　　　　│　　Bullet.cpp  
　　　　　　│　　Bullet.h(弾丸)  
　　　　　　│　　EffectBase.cpp  
　　　　　　│　　EffectBase.h(エフェクトの基底クラス)  
　　　　　　│　　EffectDeathObject.cpp  
　　　　　　│　　EffectDeathObject.h(しんだときのエフェクト)  
　　　　　　│　　EffectDestroyAmmo.cpp  
　　　　　　│　　EffectDestroyAmmo.h(球が死んだときのエフェクト)  
　　　　　　│　　EffectFireGunship.cpp  
　　　　　　│　　EffectFireGunship.h(ガンシップが球を発射したときのエフェクト)  
　　　　　　│　　EffectFirePlayer.cpp  
　　　　　　│　　EffectFirePlayer.h(プレイヤーが球を発射したときのエフェクト)  
　　　　　　│　　EffectHitBlackSmoke.cpp  
　　　　　　│　　EffectHitBlackSmoke.h(黒煙エフェクト)  
　　　　　　│　　EffectHitPlayerFrame.cpp  
　　　　　　│　　EffectHitPlayerFrame.h(炎エフェクト)  
　　　　　　│　　EffectSpawnAmmo.cpp  
　　　　　　│　　EffectSpawnAmmo.h(弾丸が生まれるときのエフェクト)  
　　　　　　│　　EnemyAAA.cpp  
　　　　　　│　　EnemyAAA.h(敵対空砲)  
　　　　　　│　　EnemyColumn.cpp  
　　　　　　│　　EnemyColumn.h(敵の隊列クラス)  
　　　　　　│　　EnemyGunShip.cpp  
　　　　　　│　　EnemyGunShip.h(敵ガンシップ)  
　　　　　　│　　EnemyKobae.cpp  
　　　　　　│　　EnemyKobae.h(敵コバエー)  
　　　　　　│　　EnemySkyhunter.cpp  
　　　　　　│　　EnemySkyhunter.h(敵スカイハンター)  
　　　　　　│　　GameStage.cpp  
　　　　　　│　　GameStage.h(ゲーム上の土台)  
　　　　　　│　　Player.cpp  
　　　　　　│　　Player.h(プレイヤー)  
　　　　　　│　　SkySphere.cpp  
　　　　　　│　　SkySphere.h(スカイスフェア)  
　　　　　　│　　StageObject.cpp  
　　　　　　│　　StageObject.h(ステージ上のビルなどのオブジェクト)  
　　　　　　│  
　　　　　　├─ mode(画面モードをまとめたファイル)  
　　　　　　│　　ModeMainGame.cpp  
　　　　　　│　　ModeMainGame.h(ゲームのスクリプトが実装されているクラス)  
　　　　　　│　　ModeSpeakScript.cpp  
　　　　　　│　　ModeSpeakScript.h(キャラが喋る時に使われるクラス)  
　　　　　　│　　ModeTitle.cpp  
　　　　　　│　　ModeTitle.h(タイトル画面)  
　　　　　　│      
　　　　　　├─ speakscript(ModeSpeakScript内で使われるオブジェクトをまとめたファイル)  
　　　　　　│　　ActorBaseSpeak.cpp  
　　　　　　│　　ActorBaseSpeak.h(ModeSpeakScript内で使われるオブジェクトの基底クラス)  
　　　　　　│　　SpeakScriptObject.cpp  
　　　　　　│　　SpeakScriptObject.h(ゲーム中に動きながら喋るオブジェクト)  
　　　　　　│  
　　　　　　├─ title(タイトル(ModeTitle)内で使われるオブジェクトをまとめたファイル)  
　　　　　　│　　ActorTitle.cpp  
　　　　　　│　　ActorTitle.h(タイトル画面でのオブジェクトの基底クラス)  
　　　　　　│　　CreditGuid.cpp  
　　　　　　│　　CreditGuid.h(クレジットの文字を表示するクラス)  
　　　　　　│　　CreditLogo.cpp  
　　　　　　│　　CreditLogo.h(プレイヤーがクレジットを見る時に引っ張るもののクラス)  
　　　　　　│　　EndGuid.cpp  
　　　　　　│　　EndGuid.h(エンドの文字を表示するクラス)  
　　　　　　│　　EndLogo.cpp  
　　　　　　│　　EndLogo.h(プレイヤーがエンドする時に引っ張るもののクラス)  
　　　　　　│　　StartGuid.cpp  
　　　　　　│　　StartGuid.h(スタート文字を表示するクラス)  
　　　　　　│　　StartLogo.cpp  
　　　　　　│　　StartLogo.h(ゲームを始めたい時引っ張るもののクラス)  
　　　　　　│　　TitleLogo.cpp  
　　　　　　│　　TitleLogo.h(タイトルロゴ)  
　　　　　　│　　TitlePlayer.cpp  
　　　　　　│　　TitlePlayer.h(タイトル画面でのプレイヤー)  
　　　　　　│      
　　　　　　└─ ui(ゲーム上のuiオブジェクトをまとめたファイル)  
　　　　　　　　　UIBase.cpp  
　　　　　　　　　UIBase.h(ゲーム画面で使われるuiの基底クラス)  
　　　　　　　　　UICursor.cpp  
　　　　　　　　　UICursor.h(カーソルuiクラス)  
　　　　　　　　　UIFuelGage.cpp  
　　　　　　　　　UIFuelGage.h(燃料ゲージのクラス)  
　　　　　　　　　UIHpGage.cpp  
　　　　　　　　　UIHpGage.h(hpゲージのクラス)  
　　　　　　　　　UIPullGage.cpp  
　　　　　　　　　UIPullGage.h(引張ゲージのクラス)  
　　　　　　　　　UITutorial.cpp  
　　　　　　　　　UITutorial.h(画面上に表示されるボタンの案内のクラス)  