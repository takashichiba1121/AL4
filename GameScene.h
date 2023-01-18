#pragma once
#include"Model.h"
#include"object3d.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"input.h"
#include"Texture.h"
class GameScene
{
public:
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
	/// 毎フレーム処理
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void BulletUpdate();

	void CheckAllCollisions();

	/// <summary>
	/// 描画
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// 描画
	/// </summary>
	void SpriteDraw();

private:
	Model* EnemyModel;

	Object3d* Enemy[5];

	Sprite* TitreUI = nullptr;

	Sprite* Space = nullptr;

	Sprite* sprite2DReticle_=nullptr;

	Sprite* Clear = nullptr;

	Sprite* Sousa = nullptr;

	enum class Phase {
		title, //タイトル画面
		enemy, //雑魚戦フェーズ
		result,//リザルトフェーズ
	};

	Phase phase_=Phase::title;

	Model* playerBullet;

	Object3d* bullet;

	bool isBullet=false;

	bool EnemyDeath[5];
};

