#pragma once
///<summary>
///�����蔻��v���~�e�B�u
///</summary>

#include<DirectXMath.h>
#include"Vector3.h"

/// <summary>
/// ����
/// </summary>
struct  Sphere
{
	//���S���W
	Vector3 center = { 0,0,0 };
	//���a
	float radius = 1.0f;
};

struct  Plane
{
	//���S���W
	Vector3 normal = { 0,1,0};
	//���_����̋���
	float distance = 0.0f;
};

/// <summary>
/// �@���t���O�p�`
/// </summary>
class Triangle {
public:
	//���_���W3��
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	//�@���x�N�g��
	Vector3 normal;

	/// <summary>
	/// �@���x�N�g��
	/// </summary>
	void ComputeNormal();
};

struct Ray
{
	//���_���W
	Vector3 start = {0,0,0};

	//����
	Vector3 dir = {1,0,0};
};