#include"RailCamera.h"
#include"affine.h"
#include<assert.h>
void RailCamera::Initialize(Vector3 trans, Vector3 rot) {

	worldTransform_.Initialize();
	//���[���h�g�����X�t�H�[���̏����ݒ�
	this->worldTransform_.translation_ = trans;
	this->worldTransform_.rotation_ = rot;
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	viewProjection_.farZ = 5000.0f;
	//�r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();

	debugText_ = DebugText::GetInstance();

	input_ = Input::GetInstance();
}
void RailCamera::Update() {
	//�v���C���[���񏈗�
	Vector3 rot = { 0,0,0 };
	Vector3 move = { 0,0,0 };
	move.z = 0.5;

	worldTransform_.translation_ += move;
	worldTransform_.rotation_.y += rot.y * (180 / PI);

	affine::makeMatIdentity(worldTransform_.matWorld_);
	affine::makeMatRot(worldTransform_.matWorld_, worldTransform_.rotation_);
	affine::makeMatTrans(worldTransform_.matWorld_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	viewProjection_.eye = worldTransform_.translation_;
	//���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = affine::MatVector(worldTransform_.matWorld_, forward);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	forward += viewProjection_.eye;
	viewProjection_.target = forward;
	//���[���h����x�N�g��
	Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_.up = affine::MatVector(worldTransform_.matWorld_, up);
	//�r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();
}
void RailCamera::reset() {
	//���[���h�g�����X�t�H�[���̏����ݒ�
	this->worldTransform_.translation_ =  Vector3{ 0.0f,10.0f,-1000.0f };
}