#pragma once
#include"Model.h"
#include "Sprite.h"
#include"Input.h"
class Title
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	bool getStateFrg() { return stateFrg; };
private:
	//2D���e�B�N���p�X�v���C�g
	std::unique_ptr<Sprite> state2D;
	std::unique_ptr<Sprite> Title2D;

	bool stateFrg = false;

	Input* input_ = nullptr;

	uint32_t textureReticle1 = 0;

	uint32_t textureReticle2 = 0;
};