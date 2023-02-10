#pragma once
#include"object3d.h"
#include"input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"Texture.h"
#include"Audio.h"
#include"imguiManager.h"
#include<imgui.h>
#include"Collision.h"
class GameScene
{
public: // �����o�֐�
	GameScene();

	~GameScene();

	void Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�v���C�g�`��
	/// </summary>
	void SpriteDraw();
private:
	Model* modelTriangle = nullptr;
	Model* modelGround = nullptr;
	Model* modelSphere = nullptr;
	Model* modelRay = nullptr;

	Object3d* objTriangle = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objSphere = nullptr;
	Object3d* objRay = nullptr;

	//�����蔻�聏�@��
	Sphere sphere;
	//�����蔻��@����
	Plane plane;
	//�O�p�`
	Triangle triangle;
	//�����蔻��@���C
	Ray ray;

	int scene = 0;

	imguiManager imgui;
};

