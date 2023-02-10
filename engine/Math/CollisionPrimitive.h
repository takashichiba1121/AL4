#pragma once
///<summary>
///当たり判定プリミティブ
///</summary>

#include<DirectXMath.h>
#include"Vector3.h"

/// <summary>
/// 平面
/// </summary>
struct  Sphere
{
	//中心座標
	Vector3 center = { 0,0,0 };
	//半径
	float radius = 1.0f;
};

struct  Plane
{
	//中心座標
	Vector3 normal = { 0,1,0};
	//原点からの距離
	float distance = 0.0f;
};

/// <summary>
/// 法線付き三角形
/// </summary>
class Triangle {
public:
	//頂点座標3つ
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	//法線ベクトル
	Vector3 normal;

	/// <summary>
	/// 法線ベクトル
	/// </summary>
	void ComputeNormal();
};

struct Ray
{
	//視点座標
	Vector3 start = {0,0,0};

	//方向
	Vector3 dir = {1,0,0};
};