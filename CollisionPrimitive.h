#pragma once
///<summary>
///�����蔻��v���~�e�B�u
///</summary>

#include<DirectXMath.h>

/// <summary>
/// ����
/// </summary>
struct  Sphere
{
	//���S���W
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//���a
	float radius = 1.0f;
};

struct  Plane
{
	//���S���W
	DirectX::XMVECTOR nolmal = { 0,1,0,0 };
	//���a
	float distance = 0.0f;
};