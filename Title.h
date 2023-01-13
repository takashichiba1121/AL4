#pragma once
#include"Model.h"
#include "Sprite.h"
#include"Input.h"
class Title
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool getStateFrg() { return stateFrg; };
private:
	//2Dレティクル用スプライト
	std::unique_ptr<Sprite> state2D;
	std::unique_ptr<Sprite> Title2D;

	bool stateFrg = false;

	Input* input_ = nullptr;

	uint32_t textureReticle1 = 0;

	uint32_t textureReticle2 = 0;
};