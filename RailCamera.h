#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"DebugText.h"
#include "Input.h"
/// <summary>
/// ���L����
/// </summary>
class RailCamera {

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 translation, Vector3 rot);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void reset();

	ViewProjection& GetViewProjection() { return viewProjection_; };

	WorldTransform* GetWorldTransform() { return &worldTransform_; };
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;

	Input* input_ = nullptr;

	float PI = 3.1415927f;
};