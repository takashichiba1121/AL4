#pragma once
#include"CollisionPrimitive.h"

/// <summary>
/// 当たり判定ヘルパークラス
/// </summary>
class Collision
{
public:
	///<summary>
	///球と平面の当たり判定
	///</summary>
	///<param name="sphere">球</param>
	///<param name="plane">平面</param>
	///<param name="inter">交点(平面上の最近接点)</param>
	///<returns>交差してるか否か</retuns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane&
		plane, DirectX::XMVECTOR* inter = nullptr);

	///<summary>
	///点と三角形の最近接点を求める
	///</summary>
	///<param name="point">点</param>
	///<param name="triangle">三角形</param>
	///<param name="closest">最近交点(出力用)</param>
	///<returns>交差してるか否か</retuns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point ,
		const Triangle&triangle,DirectX::XMVECTOR* closest);

	///<summary>
	///点と三角形の当たり判定チェック
	///</summary>
	///<param name="point">球</param>
	///<param name="triangle">三角形</param>
	///<param name="inter">交点(三角形上の最近接点)</param>
	///<returns>交差してるか否か</retuns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle&
		triangle, DirectX::XMVECTOR* inter = nullptr);

	///<summary>
	///レイとの平面当たり判定
	///</summary>
	///<param name="ray">レイ</param>
	///<param name="plane">平面</param>
	///<param name="distance">距離(出力用)</param>
	///<param name="inter">交点(出力用)</param>
	///<returns>交差してるか否か</retuns>
	static bool CheckRay2Plane(const Ray& Ray, const Plane&plane,
		float* distnce=nullptr , DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// レイト法線付き三角形の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="triangle">三角形</param>
	/// <param name="distance">距離(出力用)</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Triangle(const Ray& ray,const Triangle& triangle,
		float* distance=nullptr,DirectX::XMVECTOR* inter=nullptr);
};

