#include"EnemyBullet.h"
#include<cassert>
#include"affine.h"
#include"player.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity, Player* player)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	assert(player);
	model_ = model;
	player_ = player;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;
}
void EnemyBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	if (worldTransform_.translation_.z < player_->GetworldPosition().z-50){
		isDead_ = true;
	}
	worldTransform_.translation_ += velocity_;

	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatRot(worldTransform_.matWorld_, worldTransform_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}
void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
void EnemyBullet::OnCollision()
{
	isDead_ = true;
}
Vector3 EnemyBullet::GetworldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldpos;
	//���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldpos.x = worldTransform_.translation_.x;
	worldpos.y = worldTransform_.translation_.y;
	worldpos.z = worldTransform_.translation_.z;

	return worldpos;
}