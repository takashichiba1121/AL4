#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"Collision.h"
#include<sstream>
#include<iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete objTriangle;
	delete objGround;
	delete objSphere;
	delete objRay;
	delete modelTriangle;
	delete modelGround;
	delete modelSphere;
	delete modelRay;
	delete camera;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// カメラ生成
	camera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight, input);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	objTriangle = Object3d::Create();
	objGround = Object3d::Create();
	objSphere = Object3d::Create();
	objRay = Object3d::Create();

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	modelTriangle = Model::CreateFromOBJ("triangle_mat");
	modelGround = Model::CreateFromOBJ("ground");
	modelSphere = Model::CreateFromOBJ("playerbullet");
	modelRay = Model::CreateFromOBJ("cube");

	objTriangle->SetModel(modelTriangle);
	objGround->SetModel(modelGround);
	objSphere->SetModel(modelSphere);
	objRay->SetModel(modelRay);

	objRay->SetScale({ 0.5f,0.5f,0.5f });

	//球の初期値を設定
	sphere.center = XMVectorSet(0, 2, 0, 1);//中心座標
	sphere.radius = 1.0f;//半径

	//球の初期値を設定
	plane.normal = XMVectorSet(0, 1, 0, 0);//法線ベクトル
	plane.distance = 0.0f;//原点(0.0.0)からの距離


	//三角形の初期化を設定
	triangle.p0 = XMVectorSet(-1.0f, 1, -1.0f, 1);//左手前
	triangle.p1 = XMVectorSet(-1.0f, 1, +1.0f, 1);//右奥
	triangle.p2 = XMVectorSet(+1.0f, 1, -1.0f, 1);//右手前
	triangle.normal = XMVectorSet(0.0f, 1.0f, 0.0f, 1);//上向き
	triangle.ComputeNormal();

	//レイの初期値を設定
	ray.start = XMVectorSet(0, 1, 0, 1);//原点やや上
	ray.dir = XMVectorSet(0, -1, 0, 0);//下向き
}

void GameScene::Update()
{
	bool hit=false;
	float distance;
	XMVECTOR inter;

	camera->Update();

	if (input->TriggerKey(DIK_SPACE))
	{
		scene++;
		if (scene==5)
		{
			scene = 0;
		}
	}
	switch (scene)
	{
	case 0:
	//球移動a
	{
		XMVECTOR moveY = XMVectorSet(0,0.01f, 0, 0);
		if (input->PushKey(DIK_Q)) { sphere.center += moveY; }
		else if (input->PushKey(DIK_E)) { sphere.center -= moveY; }

		XMVECTOR moveX = XMVectorSet( 0.01f,0, 0, 0);
		if (input->PushKey(DIK_A)) { sphere.center += moveX; }
		else if (input->PushKey(DIK_D)) { sphere.center -= moveX; }

		XMVECTOR moveZ = XMVectorSet(0,0,0.01f, 0);
		if (input->PushKey(DIK_W)) { sphere.center += moveZ; }
		else if (input->PushKey(DIK_S)) { sphere.center -= moveZ; }
	}
	//球と平面の当たり判定
	hit = Collision::CheckSphere2Plane(sphere, plane);
	if (hit) {
		//stringstreamで変数の値を埋め込んで整形する
		std::ostringstream spherestr;
		spherestr << "Sphere:("
			<< std::fixed << std::setprecision(2)
			<< sphere.center.m128_f32[0] << ","
			<< sphere.center.m128_f32[1] << ","
			<< sphere.center.m128_f32[2] << ")";

		debugText.Print("HIT", 50, 200, 1.0f);

		debugText.Print(spherestr.str(), 50, 180, 1.0f);
	}
		break;
	case 1:
	//球移動
	{
		XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
		if (input->PushKey(DIK_Q)) { sphere.center += moveY; }
		else if (input->PushKey(DIK_E)) { sphere.center -= moveY; }

		XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
		if (input->PushKey(DIK_A)) { sphere.center += moveX; }
		else if (input->PushKey(DIK_D)) { sphere.center -= moveX; }

		XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
		if (input->PushKey(DIK_W)) { sphere.center += moveZ; }
		else if (input->PushKey(DIK_S)) { sphere.center -= moveZ; }
	}
	//球と三角形の当たり判定
	XMVECTOR inter;
	hit = Collision::CheckSphere2Triangle(sphere,triangle,&inter);
	if (hit)
	{
		debugText.Print("HIT", 50, 200, 1.0f);
		//stringstreamをリセットし、交点座標を埋め込む
		std::ostringstream spherestr;
		spherestr.str("");
		spherestr.clear();
		spherestr << "("
			<< std::fixed << std::setprecision(2)
			<< inter.m128_f32[0] << ","
			<< inter.m128_f32[1] << ","
			<< inter.m128_f32[2] << ")";

		debugText.Print(spherestr.str(),50,220,1.0f);
	}
		break;
	case 2:
		//レイ移動
	{

		{
			XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
			if (input->PushKey(DIK_Q)) { ray.start += moveY; }
			else if (input->PushKey(DIK_E)) { ray.start -= moveY; }

			XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
			if (input->PushKey(DIK_D)) { ray.start += moveX; }
			else if (input->PushKey(DIK_A)) { ray.start -= moveX; }

			XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
			if (input->PushKey(DIK_W)) { ray.start += moveZ; }
			else if (input->PushKey(DIK_S)) { ray.start -= moveZ; }
		}

		std::ostringstream raystr;
		raystr << "lay.start("
			<< std::fixed << std::setprecision(2)
			<< ray.start.m128_f32[0] << ","
			<< ray.start.m128_f32[1] << ","
			<< ray.start.m128_f32[2] << ")";

		debugText.Print(raystr.str(), 50, 180, 1.0f);
	}
	//レイと平面の当たり判定
	hit = Collision::CheckRay2Plane(ray, plane,&distance, &inter);
	if (hit)
	{
		debugText.Print("HIT", 50, 200, 1.0f);
		//stringstreamをリセットし、交点座標を埋め込む
		std::ostringstream raystr;
		raystr.str("");
		raystr.clear();
		raystr << "("
			<< std::fixed << std::setprecision(2)
			<< inter.m128_f32[0] << ","
			<< inter.m128_f32[1] << ","
			<< inter.m128_f32[2] << ")";

		debugText.Print(raystr.str(), 50, 220, 1.0f);
	}
	break;
	case 3:
		//レイ移動
	{
		{
			XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
			if (input->PushKey(DIK_Q)) { ray.start += moveY; }
			else if (input->PushKey(DIK_E)) { ray.start -= moveY; }

			XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
			if (input->PushKey(DIK_A)) { ray.start += moveX; }
			else if (input->PushKey(DIK_D)) { ray.start -= moveX; }

			XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
			if (input->PushKey(DIK_W)) { ray.start += moveZ; }
			else if (input->PushKey(DIK_S)) { ray.start -= moveZ; }
		}

		std::ostringstream raystr;
		raystr << "lay.start("
			<< std::fixed << std::setprecision(2)
			<< ray.start.m128_f32[0] << ","
			<< ray.start.m128_f32[1] << ","
			<< ray.start.m128_f32[2] << ")";

		debugText.Print(raystr.str(), 50, 180, 1.0f);
	}
	//レイと三角形の当たり判定
	hit = Collision::CheckRay2Triangle(ray, triangle,&distance, &inter);
	if (hit)
	{
		debugText.Print("HIT", 50, 200, 1.0f);
		//stringstreamをリセットし、交点座標を埋め込む
		std::ostringstream raystr;
		raystr.str("");
		raystr.clear();
		raystr << "("
			<< std::fixed << std::setprecision(2)
			<< inter.m128_f32[0] << ","
			<< inter.m128_f32[1] << ","
			<< inter.m128_f32[2] << ")";

		debugText.Print(raystr.str(), 50, 220, 1.0f);

		raystr.str("");
		raystr.clear();
		raystr << "("
			<< std::fixed << std::setprecision(2) << distance << ")";

		debugText.Print(raystr.str(), 50, 240, 1.0f);
	}
	break;
	case 4:
		//レイ移動
	{
		{
			XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
			if (input->PushKey(DIK_Q)) { ray.start += moveY; }
			else if (input->PushKey(DIK_E)) { ray.start -= moveY; }

			XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
			if (input->PushKey(DIK_A)) { ray.start += moveX; }
			else if (input->PushKey(DIK_D)) { ray.start -= moveX; }

			XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
			if (input->PushKey(DIK_W)) { ray.start += moveZ; }
			else if (input->PushKey(DIK_S)) { ray.start -= moveZ; }
		}

		std::ostringstream raystr;
		raystr << "lay.start("
			<< std::fixed << std::setprecision(2)
			<< ray.start.m128_f32[0] << ","
			<< ray.start.m128_f32[1] << ","
			<< ray.start.m128_f32[2] << ")";

		debugText.Print(raystr.str(), 50, 180, 1.0f);
	}
	{
		//レイと球の当たり判定
		hit = Collision::CheckRay2Sphere(ray, sphere, &distance, &inter);
		if (hit) {
			debugText.Print("HIT", 50, 260, 1.0f);
			//stringstreamをリセットし、交点座標を埋め込む
			std::ostringstream raystr;
			raystr.str("");
			raystr.clear();
			raystr << "inter:("
				<< std::fixed << std::setprecision(2)
				<< inter.m128_f32[0] << ","
				<< inter.m128_f32[1] << ","
				<< inter.m128_f32[2] << ")";

			debugText.Print(raystr.str(), 50, 220, 1.0f);

			raystr.str("");
			raystr.clear();
			raystr << "("
				<< std::fixed << std::setprecision(2) << distance << ")";

			debugText.Print(raystr.str(), 50, 240, 1.0f);
		}

	}
	break;
	}
	objSphere->SetPosition({ sphere.center.m128_f32[0], sphere.center.m128_f32[1] ,sphere.center.m128_f32[2] });
	objTriangle->SetPosition({ 0,1,0 });
	objRay->SetPosition({ ray.start.m128_f32[0], ray.start.m128_f32[1] ,ray.start.m128_f32[2] });


	objTriangle->Update();
	objGround->Update();
	objSphere->Update();
	objRay->Update();

		debugText.Print("AD: move camera LeftRight", 50, 50, 1.0f);
		debugText.Print("WS: move camera UpDown", 50, 70, 1.0f);
		debugText.Print("ARROW: move camera FrontBack", 50, 90, 1.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	switch (scene)
	{
	case 0:
		objSphere->Draw();
		objGround->Draw();
		break;
	case 1:
		objSphere->Draw();
		objTriangle->Draw();
		break;
	case 2:
		objRay->Draw();
		objGround->Draw();
		break;
	case 3:
		objRay->Draw();
		objTriangle->Draw();
		break;
	case 4:
		objRay->Draw();
		objSphere->Draw();
		break;
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
