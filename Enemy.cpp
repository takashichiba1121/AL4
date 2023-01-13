#include"Enemy.h"
#include"PLayer.h"
#include<assert.h>
#include"affine.h"
#include"GameScene.h"
#include<cmath>
void Enemy::Initialize(Model* model, Model* BulletModel, Vector3 translation)
{
	assert(model);

	this->model_ = model;
	this->BulletModel_ = BulletModel;
	textureHandle_ = TextureManager::Load("enemytexture.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = translation;

	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

	//Fire();

	//�ڋ߃t�F�[�Y������
	ApproachInutialize();
}

void Enemy::Fire()
{
	assert(player_);
	//�e�̑��x
	const float kBulletSpeed = 0.5f;
	Vector3 playerPos = player_->GetworldPosition();
	Vector3 enemyPos = worldTransform_.translation_;
	Vector3 vector = { playerPos.x - enemyPos.x,playerPos.y - enemyPos.y,playerPos.z+30 - enemyPos.z };
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len != 0)
	{
		vector /= len;
	}
	vector *= kBulletSpeed;

	vector = affine::MatVector(worldTransform_.matWorld_, vector);

	//�e�̐������A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(BulletModel_, worldTransform_.translation_, vector,player_);
	gameScene_->AddEnemyBullet(std::move(newBullet));
}

void Enemy::Update()
{
	if (worldTransform_.translation_.z - player_->GetworldPosition().z <=300 && worldTransform_.translation_.z - player_->GetworldPosition().z >= 0)
	{
		//���˃^�C�}�[�J�E���g�_�E��
		fireTimer--;
		//�w�莞�Ԃ�r�B����
		if (fireTimer <= 0) {
			//�e�𔭎�
			Fire();
			//���˃^�C�}�[��������
			fireTimer = kFireInterval;
		}
		//�K��̈ʒu�ɓ��B�����痣�E
		if (worldTransform_.translation_.z < player_->GetworldPosition().z - 50)
		{
			isDead_ = true;
		}
	}
}
void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
void Enemy::ApproachInutialize()
{
	//���˃^�C�}�[��������
	fireTimer = kFireInterval;
}
void Enemy::OnCollision()
{
	isDead_ = true;
}
Vector3 Enemy::GetworldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldpos;
	//���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldpos.x = worldTransform_.translation_.x;
	worldpos.y = worldTransform_.translation_.y;
	worldpos.z = worldTransform_.translation_.z;

	return worldpos;
}