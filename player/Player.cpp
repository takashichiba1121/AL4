#include"PLayer.h"
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
#include"affine.h"
#include"MathUtility.h"
void Player::Initialize(Model* model,Model* bulletModel) {
	assert(model);
	assert(bulletModel);

	this->model_ = model;
	this->bulletModel_ = bulletModel;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(0.0f, -10.0f, 50.0f);

	//3Dレティクルのワールドトランスフォームの初期化
	worldTransform3DReticle_.Initialize();

	//レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("2D.png");

	//スプライト生成
	sprite2DReticle_.reset(Sprite::Create(textureReticle, Vector2{ 640,360 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
}

void Player::Update(ViewProjection viewProjection) {

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	Vector3 move = { 0,0,0 };
	Vector3 rot = { 0,0,0 };
	////ゲームパッドの状態を得る変数（XINPUT）
	//XINPUT_STATE joyState;
	////ジョイスティック状態取得
	//if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	//	move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.1;
	//	move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 0.1;
	//}
	//プレイヤー移動処理
	if (input_->PushKey(DIK_A))
	{
		move.x = -0.5;
	}
	if (input_->PushKey(DIK_D))
	{
		move.x = 0.5;
	}
	if (input_->PushKey(DIK_W))
	{
		move.y = 0.5;
	}
	if (input_->PushKey(DIK_S))
	{
		move.y = -0.5;
	}
	/*if (input_->PushKey(DIK_A))
	{
		rot.y = 0.001;
	}
	if (input_->PushKey(DIK_D))
	{
		rot.y = -0.001;
	}*/

	worldTransform_.translation_ += move;
	worldTransform_.rotation_.y += rot.y * (180 / PI);

	//移動限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);




	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatRot(worldTransform_.matWorld_, worldTransform_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();

	//キャラクター攻撃処理
	Attack();

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
	{
		POINT mousePosition;
		//マウス座標（スクリーン座標）を取得する
		GetCursorPos(&mousePosition);

		//クライアントエリア座標に変換する
		HWND hwnd = WinApp::GetInstance()->GetHwnd();
		ScreenToClient(hwnd, &mousePosition);

		sprite2DReticle_->SetPosition(Vector2(mousePosition.x, mousePosition.y));
		
		//ビューポート行列
		Matrix4 matViewport = {
			640,    0,0,0,
			  0, -360,0,0,
			  0,    0,1,0,
			640,  360,0,1,
		};

		//ビューポート行列
		Matrix4 matVPV;
		matVPV = viewProjection.matView;
		matVPV *= viewProjection.matProjection;
		matVPV *= matViewport;
		//合成行列の逆行列を計算する
		Matrix4 matInverseVPV = MathUtility::Matrix4Inverse(matVPV);

		//スクリーン座標
		Vector3 posNear = Vector3(mousePosition.x, mousePosition.y, 0);
		Vector3 posFar = Vector3(mousePosition.x, mousePosition.y, 1);

		//スクリーン座標系からワールド座標系へ
		posNear = affine::wdivision(matInverseVPV, posNear);
		posFar = affine::wdivision(matInverseVPV, posFar);

		//マウスレイの方向
		Vector3 mouseDirection = posFar;
		mouseDirection -= posNear;
			float len = sqrt(mouseDirection.x * mouseDirection.x + mouseDirection.y * mouseDirection.y + mouseDirection.z * mouseDirection.z);
		if (len != 0)
		{
			mouseDirection /= len;
		}
		//カメラから照準オブジェクトの距離
		const float kDistanceTestObject = 100.0f;
		Vector3 A = posNear;
		A+= Vector3(mouseDirection.x * kDistanceTestObject, mouseDirection.y * kDistanceTestObject, mouseDirection.z * kDistanceTestObject);
		worldTransform3DReticle_.translation_ = A;
		affine::makeMatIdentity(worldTransform3DReticle_.matWorld_);
		affine::makeMatTrans(worldTransform3DReticle_.matWorld_, worldTransform3DReticle_.translation_);
		worldTransform3DReticle_.TransferMatrix();

		//DebugText::GetInstance()->SetPos(20, 200);
		//DebugText::GetInstance()->Printf(
		//	"Mouse ScreenPos:(%d,%d)", mousePosition.x, mousePosition.y);
		//DebugText::GetInstance()->SetPos(20, 220);
		//DebugText::GetInstance()->Printf("Near:(%f,%f,%f)", posNear.x, posNear.y, posNear.z);
		//DebugText::GetInstance()->SetPos(20, 240);
		//DebugText::GetInstance()->Printf("Far:(%f,%f,%f)", posFar.x, posFar.y, posFar.z);
		//DebugText::GetInstance()->SetPos(20, 260);
		//DebugText::GetInstance()->Printf(
		//	"MouseObject:(%f,%f,%f)", worldTransform3DReticle_.translation_.x, 
		//	worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	}
}

void Player::Attack() {
	
	if (fireTimer== kFireInterval) {
		fireTimer = 0;
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = affine::MatVector(worldTransform_.parent_->matWorld_, velocity);
		velocity = affine::MatVector(worldTransform_.matWorld_, velocity);
		velocity = MathUtility::operator-(affine::GetWorldTrans(worldTransform3DReticle_.matWorld_), affine::GetWorldTrans(worldTransform_.matWorld_));
		float len = sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
		if (len != 0)
		{
			velocity /= len;
		}
		velocity *= kBulletSpeed;

		//弾の生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		Vector3 playerWolrdPos = worldTransform_.parent_->translation_;
		playerWolrdPos += worldTransform_.translation_;
		Vector3 playerWolrdRot = worldTransform_.parent_->rotation_;
		playerWolrdRot += worldTransform_.rotation_;
		newBullet->Initialize(bulletModel_, GetworldPosition(), velocity);

		//弾の登録する
		bullets_.push_back(std::move(newBullet));
	}
	else
	{
		fireTimer++;
	}
}
void missile() {

}

void Player::Draw(ViewProjection& viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_);

	/*model_->Draw(worldTransform3DReticle_, viewProjection_, textureHandle_);*/
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}
void Player::DrawUI() {
	sprite2DReticle_->Draw();
}
Vector3 Player::GetworldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldpos;
	//ワールド行列の平行移動成分を取得（ワールド座標）
	worldpos.x = worldTransform_.matWorld_.m[3][0];
	worldpos.y = worldTransform_.matWorld_.m[3][1];
	worldpos.z = worldTransform_.matWorld_.m[3][2];
	return worldpos;
}
void Player::OnCollision()
{
	isDead_ = true;
}
void Player::reset() {
	worldTransform_.translation_ = Vector3(0.0f, -10.0f, 50.0f);
	bullets_.clear();
	isDead_ = false;
}
