#include"result.h"
#include"Collision.h"
#include"WinApp.h"
void Result::Initialize() {
	input_ = Input::GetInstance();

	//レティクル用テクスチャ取得
	textureReticle1 = TextureManager::Load("result1.png");
	//レティクル用テクスチャ取得
	textureReticle2 = TextureManager::Load("result2.png");

	uint32_t textureReticle = TextureManager::Load("CLEAR.png");

	//スプライト生成
	state2D.reset(Sprite::Create(textureReticle1, Vector2{ 640,500 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
	Title2D.reset(Sprite::Create(textureReticle, Vector2{ 640,200 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
}
void Result::Update() {
	POINT mousePosition;
	//マウス座標（スクリーン座標）を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	if (Collision::GetBoxCollision(Vector2(mousePosition.x, mousePosition.y), Vector2(0, 0), state2D->GetPosition(), Vector2(256, 128))) {
		stateFrg = true;
		state2D->SetTextureHandle(textureReticle2);
	}
	else {
		stateFrg = false;
		state2D->SetTextureHandle(textureReticle1);
	}
}
void Result::Draw() {
	state2D->Draw();
	Title2D->Draw();
}