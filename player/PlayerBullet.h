#pragma once
#include "Model.h"
#include "WorldTransform.h"
class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead()const { return isDead_; }

	//�Փ˂����o������Ăяo���ꂽ��R�[���o�b�N�֐�
	void OnCollision();

	//���[���h���W���擾
	Vector3 GetworldPosition();
private:
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
	//����<frm>
	static const int32_t kLifeTime = 60*2;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};