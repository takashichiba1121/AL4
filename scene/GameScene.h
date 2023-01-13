#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"DebugCamera.h"
#include "PLayer.h"
#include"Enemy.h"
#include"Skydome.h"
#include"RailCamera.h"
#include<sstream>
#include"boss.h"
#include"Title.h"
#include"result.h"
#include"GameOver.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(GameScene* gameScene);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Fire(Vector3 trans);

	///<summary>
	///衝突判定と応答
	///</summary>
	void CheckAllCollisions();

	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	/// <summary>
	/// リセット
	/// </summary>
	void reset();

private: // メンバ変数
	//モデル
	Model* model_ = nullptr;
	Model* skydomeModel_ = nullptr;
	Model* bossmodel_ = nullptr;
	Model* playerBulletModel_ = nullptr;
	Model* bossBulettModel_ = nullptr;
	Model* playerModel_ = nullptr;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//自キャラ
	Player* player_ = nullptr;
	//敵キャラ
	std::list<std::unique_ptr<Enemy>> enemy_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	uint32_t textureHandle = 0;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	std::unique_ptr<Skydome> skydome = nullptr;

	std::unique_ptr <RailCamera> railCamera_ = nullptr;

	//弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;

	GameScene* gameScene_ = nullptr;

	std::stringstream enemyPopCommands;

	bool enemyPop = true;

	float enemyPopTime = true;

	std::unique_ptr<Boss> boss_;

	enum class Phase {
		title, //タイトル画面
		enemy, //雑魚戦フェーズ
		boss,  //ボス戦フェーズ
		result,//リザルトフェーズ
		GameOver//ゲームオーバーフェーズ
	};
	//フェーズ
	Phase phase_ = Phase::title;

	std::unique_ptr <Title> title_ = nullptr;
	std::unique_ptr <Result> result_ = nullptr;
	std::unique_ptr <GameOver> gameOver_ = nullptr;

	uint32_t sousa1 = 0;
	uint32_t sousa2 = 0;
	//2Dレティクル用スプライト
	std::unique_ptr<Sprite> spritesousa1;
	std::unique_ptr<Sprite> spritesousa2;

	bool bossAttck150=false;
	bool bossAttck50 = false;

	uint32_t soundEnter_ = 0;
	uint32_t soundBGM_ = 0;
	uint32_t soundKill_ = 0;
	uint32_t soundBossKill_ = 0;

	uint32_t A=0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
