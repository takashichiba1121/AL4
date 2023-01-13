#pragma once

#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"DebugText.h"
#include"BossBullet.h"
class Player;
///<summary>
///�G
///</summary>
class Boss {
public:
	void Initialize(Model* model,Model* bulletModel, Vector3 translation);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// 2D�`��
	/// </summary>
	void DrawUI();
	///<summary>
	///�e����
	///</summary>
	void Fire1(float razian);
	///<summary>
	///�e����
	///</summary>
	void Fire2(float razian);
	///<summary>
	///�e����
	///</summary>
	void wave1();
	///<summary>
	///�e����
	///</summary>
	void wave2();

	void SetPlayer(Player* player) { player_ = player; }

	//�Փ˂����o������Ăяo���ꂽ��R�[���o�b�N�֐�
	void OnCollision();

	//���[���h���W���擾
	Vector3 GetworldPosition();

	const std::list<std::unique_ptr<BossBullet>>& GetBullets() { return bullets_; }

	bool IsDead()const { return isDead_; }

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void reset();

	int GetHp() { return Hp; };

	//���ˊԊu
	static const int kFireInterval = 10;
	//���ˊԊu
	static const int kFireInterval2 = 60;
	//���ˊԊu
	static const int kFireInterval3 = 60;
private:
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;

	Model* bulletModel_=nullptr;

	////�e
	std::list<std::unique_ptr<BossBullet>>bullets_;

	enum class Phase {
		Approach, //�ڋ߂���
		Leave,    //���E����
	};

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
	//���˃^�C�}�[
	int32_t fireTimer = 0;
	//���˃^�C�}�[
	int32_t fireTimer2 = 0;
	//���˃^�C�}�[
	int32_t fireTimer3 = 30;
	//���L����
	Player* player_ = nullptr;

	DebugText* debugText_ = nullptr;
	//�f�X�t���O
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
