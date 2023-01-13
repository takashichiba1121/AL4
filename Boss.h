#pragma once

#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"DebugText.h"
#include"BossBullet.h"
class Player;
///<summary>
///敵
///</summary>
class Boss {
public:
	void Initialize(Model* model,Model* bulletModel, Vector3 translation);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// 2D描画
	/// </summary>
	void DrawUI();
	///<summary>
	///弾発射
	///</summary>
	void Fire1(float razian);
	///<summary>
	///弾発射
	///</summary>
	void Fire2(float razian);
	///<summary>
	///弾発射
	///</summary>
	void wave1();
	///<summary>
	///弾発射
	///</summary>
	void wave2();

	void SetPlayer(Player* player) { player_ = player; }

	//衝突を検出したら呼び出されたるコールバック関数
	void OnCollision();

	//ワールド座標を取得
	Vector3 GetworldPosition();

	const std::list<std::unique_ptr<BossBullet>>& GetBullets() { return bullets_; }

	bool IsDead()const { return isDead_; }

	/// <summary>
	/// リセット
	/// </summary>
	void reset();

	int GetHp() { return Hp; };

	//発射間隔
	static const int kFireInterval = 10;
	//発射間隔
	static const int kFireInterval2 = 60;
	//発射間隔
	static const int kFireInterval3 = 60;
private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

	Model* bulletModel_=nullptr;

	////弾
	std::list<std::unique_ptr<BossBullet>>bullets_;

	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
	};

	//フェーズ
	Phase phase_ = Phase::Approach;
	//発射タイマー
	int32_t fireTimer = 0;
	//発射タイマー
	int32_t fireTimer2 = 0;
	//発射タイマー
	int32_t fireTimer3 = 30;
	//自キャラ
	Player* player_ = nullptr;

	DebugText* debugText_ = nullptr;
	//デスフラグ
	bool isDead_ = false;

	const int MaxHp = 300;
	int Hp = MaxHp;

	uint32_t hpBar = 0;
	uint32_t damageBar = 0;

	std::unique_ptr<Sprite> HpUI = nullptr;
	std::unique_ptr<Sprite> damageUI = nullptr;

	float HpUIx = 150;
	float HpUISizex = 300;

};
