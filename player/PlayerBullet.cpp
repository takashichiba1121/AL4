#include"PlayerBullet.h"
#include<cassert>
#include"affine.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	//textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;
}
void PlayerBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_ += velocity_;

	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatRot(worldTransform_.matWorld_, worldTransform_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}
void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
void PlayerBullet::OnCollision()
{
	isDead_ = true;
}
Vector3 PlayerBullet::GetworldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldpos;
	//���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldpos.x = worldTransform_.translation_.x;
	worldpos.y = worldTransform_.translation_.y;
	worldpos.z = worldTransform_.translation_.z;

	return worldpos;
}