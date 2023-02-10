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
public: // メンバ関数
	GameScene();

	~GameScene();

	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// スプライト描画
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

	//当たり判定￥　球
	Sphere sphere;
	//当たり判定　平面
	Plane plane;
	//三角形
	Triangle triangle;
	//当たり判定　レイ
	Ray ray;

	int scene = 0;

	imguiManager imgui;
};

