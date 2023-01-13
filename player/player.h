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
#include<cassert>
#include"PlayerBullet.h"
#include<memory>
#include<list>

/// <summary>
/// 自キャラ
/// </summary>
class Player {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model,Model* bulletModel);
	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection viewProjection);

	///<summary>
	///攻撃
	///</summary>
	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection_);

	//ワールド座標を取得
	Vector3 GetworldPosition();

	//衝突を検出したら呼び出されたるコールバック関数
	void OnCollision();

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; };

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	bool IsDead()const { return isDead_; }

	/// <summary>
	/// リセット
	/// </summary>
	void reset();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* bulletModel_=nullptr;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;

	//弾
	std::list<std::unique_ptr<PlayerBullet>>bullets_;

	float PI = 3.1415927f;

	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	//2Dレティクル用スプライト
	std::unique_ptr<Sprite> sprite2DReticle_;

	static const int kFireInterval = 10;

	//発射タイマー
	int32_t fireTimer = 0;

	//デスフラグ
	bool isDead_ = false;
};