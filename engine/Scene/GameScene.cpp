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

	// 3D�I�u�W�F�N�g����
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

	//���̏����l��ݒ�
	sphere.center = { 0, 2, 0 };//���S���W
	sphere.radius = 1.0f;//���a

	//���̏����l��ݒ�
	plane.normal = { 0, 1, 0 };//�@���x�N�g��
	plane.distance = 0.0f;//���_(0.0.0)����̋���


	//�O�p�`�̏�������ݒ�
	triangle.p0 = { -1.0f, 1, -1.0f};//����O
	triangle.p1 = { -1.0f, 1, +1.0f};//�E��
	triangle.p2 = { +1.0f, 1, -1.0f};//�E��O
	triangle.normal = { 0.0f, 1.0f, 0.0f};//�����
	triangle.ComputeNormal();

	//���C�̏����l��ݒ�
	ray.start = { 0, 1, 0 };//���_����
	ray.dir = { 0, -1, 0 };//������
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
		//���ړ�a
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
	//���ƕ��ʂ̓����蔻��
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
		//���ړ�
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
	//���ƎO�p�`�̓����蔻��
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
		//���C�ړ�

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
	//���C�ƕ��ʂ̓����蔻��
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
		//���C�ړ�
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
	//���C�ƎO�p�`�̓����蔻��
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
		//���C�ړ�
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
		//���C�Ƌ��̓����蔻��
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
	// 3D�I�u�N�W�F�N�g�̕`��
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
