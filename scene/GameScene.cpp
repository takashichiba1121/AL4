#include "GameScene.h"
#include "TextureManager.h"
#include"AxisIndicator.h"
#include <cassert>
#include<cmath>
#include<random>
#include"player.h"
#include"enemy.h"
#include<fstream>
#include"Collision.h"
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	//自キャラの解放
	delete player_;
	delete playerModel_;
	delete model_;
	delete skydomeModel_;
	delete bossmodel_;
	delete playerBulletModel_;
	delete bossBulettModel_;
}

void GameScene::Initialize(GameScene* gameScene) {
	gameScene_ = gameScene;
	debugCamera_ = new DebugCamera(1280, 720);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//自キャラの生成
	skydome = std::make_unique<Skydome>();
	railCamera_ = std::make_unique <RailCamera>();
	boss_ = std::make_unique<Boss>();
	title_ = std::make_unique<Title>();
	result_ = std::make_unique<Result>();
	gameOver_ = std::make_unique<GameOver>();
	spritesousa1 = std::make_unique<Sprite>();
	spritesousa2 = std::make_unique<Sprite>();
	player_ = new Player();
	model_ = Model::Create();
	//TextureManager::Load("2D.png");
	playerModel_ = Model::CreateFromOBJ("player", true);
	playerBulletModel_ = Model::CreateFromOBJ("playerbullet", true);
	//自キャラの初期化
	player_->Initialize(playerModel_, playerBulletModel_);

	railCamera_->Initialize(Vector3{ 0.0f,10.0f,-1000.0f }, Vector3{ 0.0f,0.0f,0.0f });

	player_->SetParent(railCamera_->GetWorldTransform());

	skydomeModel_ = Model::CreateFromOBJ("skydome", true);

	skydome->Initialize(skydomeModel_);

	bossmodel_ = Model::CreateFromOBJ("boss", true);

	boss_->SetPlayer(player_);

	bossBulettModel_ = Model::CreateFromOBJ("bossbullet", true);

	boss_->Initialize(bossmodel_, bossBulettModel_, Vector3(0, 0, 100));

	title_->Initialize();

	result_->Initialize();

	gameOver_->Initialize();

	sousa1 = TextureManager::Load("sousa1.png");
	sousa2 = TextureManager::Load("sousa2.png");

	//スプライト生成
	spritesousa1.reset(Sprite::Create(sousa1, Vector2{ 74,592 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
	spritesousa2.reset(Sprite::Create(sousa2, Vector2{ 74,656 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));

	//サウンドデータの読み込み
	soundEnter_ = audio_->LoadWave("enter.wav");
	soundBGM_ = audio_->LoadWave("BGM.wav");
	soundKill_ = audio_->LoadWave("kill.wav");
	soundBossKill_ = audio_->LoadWave("BossKill.wav");
	A=audio_->PlayWave(soundBGM_,1,0.1f);
	LoadEnemyPopData();
}

void GameScene::Update() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_W))
	{
		if (isDebugCameraActive_) { isDebugCameraActive_ = false; }
		else { isDebugCameraActive_ = true; }
	}
#endif
	//デスフラグの立った弾を削除
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
	//デスフラグの立った敵を削除
	enemy_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});

	//衝突判定
	CheckAllCollisions();
	switch (phase_)
	{
	case Phase::title:

		title_->Update();

		if (input_->IsPressMouse(0) && title_->getStateFrg() == true) {
			phase_ = Phase::enemy;
			audio_->PlayWave(soundEnter_, 0, 0.5f);
		}
		else
		{
			break;
		}
	case Phase::enemy:
		//弾更新
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			//敵キャラの更新
			enemy->Update();
		}
		//弾更新
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}

		railCamera_->Update();

		//自キャラの更新
		player_->Update(railCamera_->GetViewProjection());

		UpdateEnemyPopCommands();
		if (player_->GetworldPosition().z > 0) {
			phase_ = Phase::boss;
		}
		if (player_->IsDead() == true)
		{
			phase_ = Phase::GameOver;
		}
		break;
	case Phase::boss:
		if (boss_->IsDead() == true) {
			phase_ = Phase::result;
			audio_->PlayWave(soundBossKill_);
		}
		if (player_->IsDead() == true)
		{
			phase_ = Phase::GameOver;
		}
		if (boss_->GetHp() <= 150 && bossAttck150 == false)
		{
			bossAttck150 = true;
			//敵を発生させる
			Fire(Vector3( 25, 25, 50));
			Fire(Vector3(-25, 25, 50));
			Fire(Vector3(-25,-25, 50));
			Fire(Vector3( 25,-25, 50));
		}
		if (boss_->GetHp() <= 150 && bossAttck150 == false)
		{
			bossAttck50 = true;

		}
		//弾更新
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			//敵キャラの更新
			enemy->Update();
		}
		//弾更新
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}

		//自キャラの更新
		player_->Update(railCamera_->GetViewProjection());

		boss_->Update();
		break;
	case Phase::result:

		result_->Update();

		if (input_->IsPressMouse(0) && result_->getStateFrg() == true) {

			phase_ = Phase::title;
			audio_->PlayWave(soundEnter_, 0, 0.5f);
			reset();
		}
		else
		{
			break;
		}
	case Phase::GameOver:
		gameOver_->Update();

		if (input_->IsPressMouse(0) && gameOver_->getStateFrg() == true) {

			phase_ = Phase::title;
			audio_->PlayWave(soundEnter_, 0, 0.5f);
			reset();
		}
		else
		{
			break;
		}

	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//3Dモデル描画
	skydome->Draw(railCamera_->GetViewProjection());
	switch (phase_)
	{
	case Phase::title:

		break;
	case Phase::enemy:
		//弾描画
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			enemy->Draw(railCamera_->GetViewProjection());
		}
		//弾描画
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(railCamera_->GetViewProjection());
		}

		//自キャラの描画
		player_->Draw(railCamera_->GetViewProjection());

		break;
	case Phase::boss:
		//弾描画
		for (std::unique_ptr<Enemy>& enemy : enemy_) {
			enemy->Draw(railCamera_->GetViewProjection());
		}
		//弾描画
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(railCamera_->GetViewProjection());
		}

		//自キャラの描画
		player_->Draw(railCamera_->GetViewProjection());

		if (!boss_->IsDead())
		{
			boss_->Draw(railCamera_->GetViewProjection());
		}

		break;
	case Phase::result:

		break;
	case Phase::GameOver:

		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	switch (phase_)
	{
	case Phase::title:
		title_->Draw();
		break;
	case Phase::enemy:
		player_->DrawUI();
		break;
	case Phase::boss:
		player_->DrawUI();
		boss_->DrawUI();
		break;
	case Phase::result:
		result_->Draw();
		break;
	case Phase::GameOver:
		gameOver_->Draw();
		break;
	}
	spritesousa1->Draw();
	spritesousa2->Draw();

	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::CheckAllCollisions()
{
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<BossBullet>>& bossBullets = boss_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetworldPosition();

	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		//敵弾の座標
		posB = bullet->GetworldPosition();

		const float AR = 1;
		const float BR = 1;

		float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
		float B = pow((AR + BR), 2);

		if (A <= B)
		{
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	//自弾と敵キャラ全ての当たり判定
	for (const std::unique_ptr<Enemy>& enemy : enemy_) {
		posA = enemy->GetworldPosition();
		//自弾と敵キャラ全ての当たり判定
		for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
			//自弾の座標
			posB = bullet->GetworldPosition();

			const float AR = 1;
			const float BR = 1;

			float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
			float B = pow((AR + BR), 2);

			if (A <= B)
			{
				//自キャラの衝突時コールバックを呼び出す
				enemy->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				bullet->OnCollision();
				audio_->PlayWave(soundKill_,0,0.5f);
			}
		}
	}
#pragma endregion

#pragma region 自弾とボスの当たり判定
	//ボスの座標
	posA = boss_->GetworldPosition();

	//ボスと自弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		//自弾の座標
		posB = bullet->GetworldPosition();

		const float AR = 50;
		const float BR = 1;

		float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
		float B = pow((AR + BR), 2);

		if (A <= B)
		{
			//ボスの衝突時コールバックを呼び出す
			boss_->OnCollision();
			//自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region ボス弾と自機の当たり判定
	//自機の座標
	posA = player_->GetworldPosition();

	//ボス弾と自機全ての当たり判定
	for (const std::unique_ptr<BossBullet>& bullet : bossBullets) {
		//自弾の座標
		posB = bullet->GetworldPosition();

		const float AR = 1;
		const float BR = 1;

		float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
		float B = pow((AR + BR), 2);

		if (A <= B)
		{
			//ボスの衝突時コールバックを呼び出す
			player_->OnCollision();
			//自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion
}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets_.push_back(std::move(enemyBullet));
}
void GameScene::Fire(Vector3 trans)
{
	assert(player_);

	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->Initialize(playerModel_, bossBulettModel_, trans);
	enemy->SetPlayer(player_);
	enemy->SetGameScene(gameScene_);
	enemy_.push_back(std::move(enemy));
}
void GameScene::LoadEnemyPopData() {
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}
void GameScene::UpdateEnemyPopCommands() {

	//待機処理
	if (enemyPop) {
		enemyPopTime--;
		if (enemyPopTime <= 0) {
			//待機完了
			enemyPop = false;
		}
		return;
	}

	//1行分の文字列を入れる
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}
		//POPコマンド
		if (word.find("POP") == 0) {
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させる
			Fire(Vector3(x, y, z));
		}
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			enemyPop = true;

			enemyPopTime = waitTime;
			//コマンドループを抜ける
			break;
		}
	}
}
void GameScene::reset() {
	enemyBullets_.clear();
	enemy_.clear();
	player_->reset();
	boss_->reset();
	railCamera_->reset();
	enemyPopCommands.str("");
	enemyPopCommands.clear(std::stringstream::goodbit);
	LoadEnemyPopData();
	enemyPop = false;
	enemyPopTime = 0;
	bossAttck150 = false;
}
