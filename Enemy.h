#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"EnemyBullet.h"
class Player;
class GameScene;
///<summary>
///�G
///</summary>
class Enemy {
public:
	void Initialize(Model* model, Model* BulletModel, Vector3 translation);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
	///<summary>
	///�e����
	///</summary>
	void Fire();
	void ApproachInutialize();

	void SetPlayer(Player* player) { player_ = player; }

	//�Փ˂����o������Ăяo���ꂽ��R�[���o�b�N�֐�
	void OnCollision();

	//���[���h���W���擾
	Vector3 GetworldPosition();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	bool IsDead()const { return isDead_; }

	//���ˊԊu
	static const int kFireInterval = 90;
private:
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Model* BulletModel_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�e
	std::list<std::unique_ptr<EnemyBullet>>bullets_;

	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
	};

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
	//���˃^�C�}�[
	int32_t fireTimer = 0;
	//���L����
	Player* player_ = nullptr;

	//�Q�[���V�[��
	GameScene* gameScene_ = nullptr;
	//�f�X�t���O
	bool isDead_ = false;
};