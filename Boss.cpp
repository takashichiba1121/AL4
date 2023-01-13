#include"boss.h"
#include"PLayer.h"
#include<assert.h>
#include"affine.h"
#include"GameScene.h"
#include<cmath>
void Boss::Initialize(Model* model,Model* bulletModel, Vector3 translation)
{
	assert(model);
	assert(bulletModel);

	this->model_ = model;
	this->bulletModel_ = bulletModel;

	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

	worldTransform_.translation_ = translation;

	worldTransform_.scale_ = Vector3(50.0f,50.0f,50.0f);

	worldTransform_.rotation_.y = 1.57;//90度

	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatScale(worldTransform_.matWorld_, worldTransform_.scale_);
	affine::makeMatRot(worldTransform_.matWorld_, worldTransform_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	hpBar = TextureManager::Load("HP.png");
	damageBar = TextureManager::Load("Dameg.png");

	HpUI.reset(Sprite::Create(hpBar, Vector2{ 149,16 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
	damageUI.reset(Sprite::Create(damageBar, Vector2{ 150,16 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
}
void Boss::Update() {

	if (isDead_ == false)
	{
		//デスフラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr<BossBullet>& bullet) {
			return bullet->IsDead();
			});
		//発射タイマーカウントダウン
		fireTimer--;
		fireTimer2--;
		fireTimer3--;
		//指定時間にr達した
		if (fireTimer <= 0) {
			//弾を発射
			Fire1(0);
			//発射タイマーを初期化
			fireTimer = kFireInterval;
		}
		//指定時間にr達した
		if (fireTimer2 <= 0) {
			//弾を発射
			wave1();
			//発射タイマーを初期化
			fireTimer2 = kFireInterval2;
		}
		//指定時間にr達した
		if (fireTimer3 <= 0) {
			//弾を発射
			wave2();
			//発射タイマーを初期化
			fireTimer3 = kFireInterval3;
		}
		//弾更新
		for (std::unique_ptr<BossBullet>& bullet : bullets_) {
			bullet->Update();
		}
		debugText_->SetPos(10, 10);
		debugText_->Printf("HP:%f,%f", HpUISizex, HpUIx);
		debugText_->SetPos(10, 30);
		debugText_->Printf("HP:%d", Hp);
	}
}
void Boss::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
void Boss::DrawUI() {
	damageUI->Draw();
	HpUI->Draw();
}
Vector3 Boss::GetworldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldpos;
	//ワールド行列の平行移動成分を取得（ワールド座標）
	worldpos.x = worldTransform_.translation_.x;
	worldpos.y = worldTransform_.translation_.y;
	worldpos.z = worldTransform_.translation_.z;

	return worldpos;
}
void Boss::OnCollision() {
	Hp--;
	if (Hp <= 0){
		isDead_ = true;
	}
	HpUISizex--;
	if (int(HpUISizex) % 2 == 0){
		HpUIx--;
		HpUI->SetSize(Vector2(HpUISizex,32));
		HpUI->SetPosition(Vector2(HpUIx, 16));
	}
}
void Boss::Fire1(float ShiftPos){
	assert(player_);
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 playerPos = player_->GetworldPosition();
	Vector3 enemyPos = worldTransform_.translation_;
	Vector3 vector = { playerPos.x+ShiftPos - enemyPos.x,playerPos.y - enemyPos.y,playerPos.z - enemyPos.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}
	vector *= kBulletSpeed;
	Matrix4 mat;
	affine::makeMatIdentity(mat);
	affine::makeMatTrans(mat, worldTransform_.translation_);
	vector = affine::MatVector(mat, vector);

	//弾の生成し、初期化
	std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();
	newBullet->Initialize(bulletModel_, worldTransform_.translation_, vector);
	bullets_.push_back(std::move(newBullet));
}
void Boss::Fire2(float ShiftPos) {
	assert(player_);
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 playerPos = player_->GetworldPosition();
	Vector3 enemyPos = worldTransform_.translation_;
	Vector3 vector = { playerPos.x - enemyPos.x,playerPos.y + ShiftPos - enemyPos.y,playerPos.z - enemyPos.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}
	vector *= kBulletSpeed;
	Matrix4 mat;
	affine::makeMatIdentity(mat);
	affine::makeMatTrans(mat, worldTransform_.translation_);
	vector = affine::MatVector(mat, vector);

	//弾の生成し、初期化
	std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();
	newBullet->Initialize(bulletModel_, worldTransform_.translation_, vector);
	bullets_.push_back(std::move(newBullet));
}
void Boss::wave1() {
	Fire1(-50);
	Fire1(-40);
	Fire1(-30);
	Fire1(-20);
	Fire1(-10);
	Fire1(0);
	Fire1(10);
	Fire1(20);
	Fire1(30);
	Fire1(40);
	Fire1(50);
}
void Boss::wave2() {
	Fire2(-30);
	Fire2(-20);
	Fire2(-10);
	Fire2(0);
	Fire2(10);
	Fire2(20);
	Fire2(30);
}
void Boss::reset() {
	Hp = MaxHp;
	isDead_ = false;
	bullets_.clear();
	HpUISizex = 300;
	HpUIx = 150;
	HpUI->SetSize(Vector2(HpUISizex, 32));
	HpUI->SetPosition(Vector2(HpUIx, 16));
}