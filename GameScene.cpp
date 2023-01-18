#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	for (int i = 0; i < 5; i++)
	{
		delete Enemy[i];
	}
	delete EnemyModel;
	delete TitreUI;
	delete Space;
	delete sprite2DReticle_;
	delete bullet;
}

void GameScene::Initialize(GameScene* gameScene)
{
	uint32_t tex = Texture::LoadTexture(L"Resources/TitleUI.png");

	uint32_t tex2 = Texture::LoadTexture(L"Resources/PushSpace.png");

	uint32_t tex3 = Texture::LoadTexture(L"Resources/2D.png");

	uint32_t tex4 = Texture::LoadTexture(L"Resources/CLEAR.png");

	uint32_t tex5 = Texture::LoadTexture(L"Resources/sousa1.png");

	TitreUI = new Sprite;

	TitreUI->Initialize(tex);

	TitreUI->SetPosition({ 640,200 });

	TitreUI->SetAnchorPoint({ 0.5f,0.5f });

	Space = new Sprite;

	Space->Initialize(tex2);

	Space->SetPosition({ 640,600 });

	Space->SetScale({ 250,100 });

	Space->SetAnchorPoint({ 0.5f,0.5f });

	sprite2DReticle_ = new Sprite;

	sprite2DReticle_->Initialize(tex3);

	sprite2DReticle_->SetPosition({ 640,370 });

	sprite2DReticle_->SetAnchorPoint({ 0.5f,0.5f });

	Clear = new Sprite;

	Clear->Initialize(tex4);

	Clear->SetPosition({ 640,200 });

	Clear->SetAnchorPoint({ 0.5f,0.5f });

	Sousa = new Sprite;

	Sousa->Initialize(tex5);

	Sousa->SetPosition({ 10,596 });

	Sousa->SetAnchorPoint({ 0.0f,0.0f });

	EnemyModel = Model::LoadFormOBJ("Enemy");

	for (int i = 0; i < 5; i++)
	{

		Enemy[i] = new Object3d;

		Enemy[i]->SetModel(EnemyModel);

		Enemy[i]->Initialize();

		EnemyDeath[i] = false;

		Enemy[i]->SetScale({ 5,5,5 });
	}

	playerBullet = Model::LoadFormOBJ("playerbullet");

	bullet = new Object3d;

	bullet->SetModel(playerBullet);

	bullet->Initialize();


	Enemy[0]->SetPosition({ 0.0f,0.0f,50.0f });
	Enemy[1]->SetPosition({ 30.0f,0.0f,50.0f });
	Enemy[2]->SetPosition({ -30.0f,00.0f,50.0f });
	Enemy[3]->SetPosition({ 0.0f,-30.0f,50.0f });
	Enemy[4]->SetPosition({ 0.0f,30.0f,50.0f });
}

void GameScene::Update()
{
	switch (phase_)
	{
	case Phase::title:
		TitreUI->Update();

		Space->Update();

		if (Input::TriggerKey(DIK_SPACE))
		{
			phase_ = Phase::enemy;

			Space->SetScale({ 128.0f,64.0f });

			Space->SetPosition({ 10,660 });

			Space->SetAnchorPoint({ 0.0f,0.0f });
		}
		break;
	case Phase::enemy:

		sprite2DReticle_->Update();

		Sousa->Update();

		Space->Update();

		for (int i = 0; i < 5; i++)
		{

			Enemy[i]->Update();
		}

		BulletUpdate();

		CameraUpdate();

		CheckAllCollisions();

		if (EnemyDeath[0] == true && EnemyDeath[1] == true && EnemyDeath[2] == true && EnemyDeath[3] == true && EnemyDeath[4] == true)
		{
			phase_ = Phase::result;

			Space->SetScale({ 250,100 });

			Space->SetPosition({ 640,600 });

			Space->SetAnchorPoint({ 0.5f,0.5f });
		}
		break;
	case Phase::result:

		Clear->Update();

		Space->Update();

		if (Input::TriggerKey(DIK_SPACE))
		{
			phase_ = Phase::title;

			EnemyDeath[0] = false;
			EnemyDeath[1] = false;
			EnemyDeath[2] = false;
			EnemyDeath[3] = false;
			EnemyDeath[4] = false;

			bullet->SetPosition({ 0.0f,0.0f,0.0f });

			Object3d::SetEye({ 0.0f,0.0f,-50.0f });

			Object3d::SetTarget({ 0.0f,0.0f,0.0f });

			for (int i = 0; i < 5; i++)
			{

				Enemy[i]->Update();
			}
		}
		break;
	}

}

void GameScene::CameraUpdate()
{
	XMFLOAT3 eye = Object3d::GetEye();
	XMFLOAT3 target = Object3d::GetTarget();
	if (Input::PushKey(DIK_A))
	{
		eye.x -= 2;
		target.x -= 2;
	}
	if (Input::PushKey(DIK_W))
	{
		eye.y += 2;
		target.y += 2;
	}
	if (Input::PushKey(DIK_S))
	{
		eye.y -= 2;
		target.y -= 2;
	}
	if (Input::PushKey(DIK_D))
	{
		eye.x += 2;
		target.x += 2;
	}
	Object3d::SetEye(eye);
	Object3d::SetTarget(target);

}

void GameScene::BulletUpdate()
{
	if (isBullet == false)
	{
		if (Input::TriggerKey(DIK_SPACE))
		{
			isBullet = true;

			bullet->SetPosition(Object3d::GetEye());
		}
	}
	if (isBullet == true)
	{
		XMFLOAT3 move = bullet->GetPosition();
		if (move.z >= 60)
		{
			isBullet = false;
		}
		move.z += 2;
		bullet->SetPosition(move);
	}

	bullet->Update();
}

void GameScene::CheckAllCollisions()
{
	XMFLOAT3 BulletPos = bullet->GetPosition();
	for (int i = 0; i < 5; i++)
	{
		XMFLOAT3 EnemyPos = Enemy[i]->GetPosition();

		float BulletR = bullet->GetScale().x;
		float EnemyR = Enemy[i]->GetScale().x;

		float A = pow((EnemyPos.x - BulletPos.x), 2) + pow((EnemyPos.y - BulletPos.y), 2) + pow((EnemyPos.z - BulletPos.z), 2);
		float B = pow((BulletR + EnemyR), 2);

		if (A <= B)
		{
			//自キャラの衝突時コールバックを呼び出す
			isBullet = false;
			//敵弾の衝突時コールバックを呼び出す
			EnemyDeath[i] = true;
		}
	}
}

void GameScene::ObjectDraw()
{
	switch (phase_)
	{
	case Phase::title:
		break;
	case Phase::enemy:
		for (int i = 0; i < 5; i++)
		{
			if (EnemyDeath[i] == false)
			{
				Enemy[i]->Draw();
			}
		}
		if (isBullet == true)
		{
			bullet->Draw();
		}
		break;
	case Phase::result:

		break;
	}
}

void GameScene::SpriteDraw()
{
	switch (phase_)
	{
	case Phase::title:
		TitreUI->Draw();

		Space->Draw();
		break;
	case Phase::enemy:
		sprite2DReticle_->Draw();

		Space->Draw();

		Sousa->Draw();
		break;
	case Phase::result:
		Clear->Draw();

		Space->Draw();
		break;
	}
}
