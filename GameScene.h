#pragma once
#include"Model.h"
#include"object3d.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"input.h"
#include"Texture.h"
class GameScene
{
public:
public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(GameScene* gameScene);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void BulletUpdate();

	void CheckAllCollisions();

	/// <summary>
	/// �`��
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// �`��
	/// </summary>
	void SpriteDraw();

private:
	Model* EnemyModel;

	Object3d* Enemy[5];

	Sprite* TitreUI = nullptr;

	Sprite* Space = nullptr;

	Sprite* sprite2DReticle_=nullptr;

	Sprite* Clear = nullptr;

	Sprite* Sousa = nullptr;

	enum class Phase {
		title, //�^�C�g�����
		enemy, //�G����t�F�[�Y
		result,//���U���g�t�F�[�Y
	};

	Phase phase_=Phase::title;

	Model* playerBullet;

	Object3d* bullet;

	bool isBullet=false;

	bool EnemyDeath[5];
};

