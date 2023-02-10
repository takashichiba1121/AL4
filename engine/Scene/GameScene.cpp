#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete modelSphere;
	delete modelGround;
	delete modelRay;
	delete modelTriangle;
	delete objTriangle;
	delete objGround;
	delete objSphere;
	delete objRay;
}

void GameScene::Initialize()
{
	objTriangle=new Object3d;
	objGround = new Object3d;
	objSphere = new Object3d;
	objRay = new Object3d;
	modelSphere = new Model;
	modelGround = new Model;
	modelRay = new Model;
	modelTriangle = new Model;

	Object3d::SetEye({ 0,5,-10 });

	// 3Dオブジェクト生成
	objTriangle->Initialize();
	objGround->Initialize();
	objSphere->Initialize();
	objRay->Initialize();


	modelTriangle = Model::LoadFormOBJ("triangle_mat");
	modelGround = Model::LoadFormOBJ("ground");
	modelSphere = Model::LoadFormOBJ("playerbullet");
	modelRay = Model::LoadFormOBJ("cube");

	objTriangle->SetModel(modelTriangle);
	objGround->SetModel(modelGround);
	objSphere->SetModel(modelSphere);
	objRay->SetModel(modelRay);

	objRay->SetScale({ 0.5f,0.5f,0.5f });

	//球の初期値を設定
	sphere.center = { 0, 2, 0 };//中心座標
	sphere.radius = 1.0f;//半径

	//球の初期値を設定
	plane.normal = { 0, 1, 0 };//法線ベクトル
	plane.distance = 0.0f;//原点(0.0.0)からの距離


	//三角形の初期化を設定
	triangle.p0 = { -1.0f, 1, -1.0f};//左手前
	triangle.p1 = { -1.0f, 1, +1.0f};//右奥
	triangle.p2 = { +1.0f, 1, -1.0f};//右手前
	triangle.normal = { 0.0f, 1.0f, 0.0f};//上向き
	triangle.ComputeNormal();

	//レイの初期値を設定
	ray.start = { 0, 1, 0 };//原点やや上
	ray.dir = { 0, -1, 0 };//下向き
}

void GameScene::Update()
{
	Vector3 eye=Object3d::GetEye();

	if (Input::PushKey(DIK_LEFT))
	{
		eye.x++;
	}

	if (Input::PushKey(DIK_RIGHT))
	{
		eye.x--;
	}

	if (Input::PushKey(DIK_UP))
	{
		eye.y++;
	}

	if (Input::PushKey(DIK_DOWN))
	{
		eye.y--;
	}

	if (Input::PushKey(DIK_Z))
	{
		eye.z++;
	}

	if (Input::PushKey(DIK_X))
	{
		eye.z--;
	}

	Object3d::SetEye(eye);

	bool hit = false;
	float distance=0;
	Vector3 inter = {0,0,0};

	if (Input::TriggerKey(DIK_SPACE))
	{
		scene++;
		if (scene == 5)
		{
			scene = 0;
		}
	}
	switch (scene)
	{
	case 0:
		//球移動a
	{
		Vector3 moveY = { 0, 0.01f, 0};
		if (Input::PushKey(DIK_Q)) { sphere.center += moveY; }
		else if (Input::PushKey(DIK_E)) { sphere.center -= moveY; }

		Vector3 moveX = { 0.01f, 0, 0 };
		if (Input::PushKey(DIK_D)) { sphere.center += moveX; }
		else if (Input::PushKey(DIK_A)) { sphere.center -= moveX; }

		Vector3 moveZ = {0, 0, 0.01f };
		if (Input::PushKey(DIK_W)) { sphere.center += moveZ; }
		else if (Input::PushKey(DIK_S)) { sphere.center -= moveZ; }
	}
	//球と平面の当たり判定
	hit = Collision::CheckSphere2Plane(sphere, plane);
	imgui.Begin();
	if (hit)
	{
		ImGui::Text("hit");
	}
	else
	{
		ImGui::Text("notHit");
	}
	imgui.End();
	break;
	case 1:
		//球移動
	{
		Vector3 moveY = { 0, 0.01f, 0 };
		if (Input::PushKey(DIK_Q)) { sphere.center += moveY; }
		else if (Input::PushKey(DIK_E)) { sphere.center -= moveY; }

		Vector3 moveX = { 0.01f, 0, 0 };
		if (Input::PushKey(DIK_D)) { sphere.center += moveX; }
		else if (Input::PushKey(DIK_A)) { sphere.center -= moveX; }

		Vector3 moveZ = { 0,0,0.01f};
		if (Input::PushKey(DIK_W)) { sphere.center += moveZ; }
		else if (Input::PushKey(DIK_S)) { sphere.center -= moveZ; }
	}
	//球と三角形の当たり判定
	hit = Collision::CheckSphere2Triangle(sphere, triangle, &inter);
	imgui.Begin();
	if (hit)
	{
		ImGui::Text("hit");
	}
	else
	{
		ImGui::Text("notHit");
	}
	imgui.End();
	break;
	case 2:
		//レイ移動

		{
			Vector3 moveY = { 0,0.01f, 0 };
			if (Input::PushKey(DIK_Q)) { ray.start += moveY; }
			else if (Input::PushKey(DIK_E)) { ray.start -= moveY; }

			Vector3 moveX = { 0.01f, 0, 0 };
			if (Input::PushKey(DIK_A)) { ray.start += moveX; }
			else if (Input::PushKey(DIK_D)) { ray.start -= moveX; }

			Vector3 moveZ = { 0,0,0.01f };
			if (Input::PushKey(DIK_W)) { ray.start += moveZ; }
			else if (Input::PushKey(DIK_S)) { ray.start -= moveZ; }
		}
	//レイと平面の当たり判定
	hit = Collision::CheckRay2Plane(ray, plane, &distance, &inter);
	imgui.Begin();
	if (hit)
	{
		ImGui::Text("hit");
	}
	else
	{
		ImGui::Text("notHit");
	}
	imgui.End();
	break;
	case 3:
		//レイ移動
		{
			Vector3 moveY = { 0,0.01f, 0 };
			if (Input::PushKey(DIK_Q)) { ray.start += moveY; }
			else if (Input::PushKey(DIK_E)) { ray.start -= moveY; }

			Vector3 moveX = { 0.01f, 0, 0 };
			if (Input::PushKey(DIK_A)) { ray.start += moveX; }
			else if (Input::PushKey(DIK_D)) { ray.start -= moveX; }

			Vector3 moveZ = { 0,0,0.01f};
			if (Input::PushKey(DIK_W)) { ray.start += moveZ; }
			else if (Input::PushKey(DIK_S)) { ray.start -= moveZ; }
		}
	//レイと三角形の当たり判定
	hit = Collision::CheckRay2Triangle(ray, triangle, &distance, &inter);
	imgui.Begin();
	if (hit)
	{
		ImGui::Text("hit");
	}
	else
	{
		ImGui::Text("notHit");
	}
	imgui.End();
	break;
	case 4:
		//レイ移動
		{
			Vector3 moveY = { 0,0.01f, 0 };
			if (Input::PushKey(DIK_Q)) { ray.start += moveY; }
			else if (Input::PushKey(DIK_E)) { ray.start -= moveY; }

			Vector3 moveX = { 0.01f, 0, 0 };
			if (Input::PushKey(DIK_A)) { ray.start += moveX; }
			else if (Input::PushKey(DIK_D)) { ray.start -= moveX; }

			Vector3 moveZ = { 0,0,0.01f};
			if (Input::PushKey(DIK_W)) { ray.start += moveZ; }
			else if (Input::PushKey(DIK_S)) { ray.start -= moveZ; }
		}

	{
		//レイと球の当たり判定
		hit = Collision::CheckRay2Sphere(ray, sphere, &distance, &inter);
		imgui.Begin();
		if (hit)
		{
			ImGui::Text("hit");
		}
		else
		{
			ImGui::Text("notHit");
		}
		imgui.End();
	}
	break;
	}
	objSphere->SetPosition({ sphere.center });
	objTriangle->SetPosition({ 0,1,0 });
	objRay->SetPosition({ ray.start });


	objTriangle->Update();
	objGround->Update();
	objSphere->Update();
	objRay->Update();
}

void GameScene::Draw()
{
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
}

void GameScene::SpriteDraw()
{
}
