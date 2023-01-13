#include"result.h"
#include"Collision.h"
#include"WinApp.h"
void Result::Initialize() {
	input_ = Input::GetInstance();

	//���e�B�N���p�e�N�X�`���擾
	textureReticle1 = TextureManager::Load("result1.png");
	//���e�B�N���p�e�N�X�`���擾
	textureReticle2 = TextureManager::Load("result2.png");

	uint32_t textureReticle = TextureManager::Load("CLEAR.png");

	//�X�v���C�g����
	state2D.reset(Sprite::Create(textureReticle1, Vector2{ 640,500 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
	Title2D.reset(Sprite::Create(textureReticle, Vector2{ 640,200 }, Vector4{ 1,1,1,1 }, Vector2(0.5, 0.5)));
}
void Result::Update() {
	POINT mousePosition;
	//�}�E�X���W�i�X�N���[�����W�j���擾����
	GetCursorPos(&mousePosition);

	//�N���C�A���g�G���A���W�ɕϊ�����
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