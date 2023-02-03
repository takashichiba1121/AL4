#pragma once
///<summary>
///当たり判定プリミティブ
///</summary>

#include<DirectXMath.h>

/// <summary>
/// 平面
/// </summary>
struct  Sphere
{
	//中心座標
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//半径
	float radius = 1.0f;
};

struct  Plane
{
	//中心座標
	DirectX::XMVECTOR nolmal = { 0,1,0,0 };
	//半径
	float distance = 0.0f;
};