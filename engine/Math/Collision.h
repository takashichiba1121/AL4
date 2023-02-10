#pragma once
#include"CollisionPrimitive.h"
#include"Vector3.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
	///<summary>
	///���ƕ��ʂ̓����蔻��
	///</summary>
	///<param name="sphere">��</param>
	///<param name="plane">����</param>
	///<param name="inter">��_(���ʏ�̍ŋߐړ_)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane&
		plane, Vector3* inter = nullptr);

	///<summary>
	///�_�ƎO�p�`�̍ŋߐړ_�����߂�
	///</summary>
	///<param name="point">�_</param>
	///<param name="triangle">�O�p�`</param>
	///<param name="closest">�ŋߌ�_(�o�͗p)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static void ClosestPtPoint2Triangle(const Vector3& point ,
		const Triangle&triangle,Vector3* closest);

	///<summary>
	///�_�ƎO�p�`�̓����蔻��`�F�b�N
	///</summary>
	///<param name="point">��</param>
	///<param name="triangle">�O�p�`</param>
	///<param name="inter">��_(�O�p�`��̍ŋߐړ_)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle&
		triangle, Vector3* inter = nullptr);

	///<summary>
	///���C�Ƃ̕��ʓ����蔻��
	///</summary>
	///<param name="ray">���C</param>
	///<param name="plane">����</param>
	///<param name="distance">����(�o�͗p)</param>
	///<param name="inter">��_(�o�͗p)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static bool CheckRay2Plane(const Ray& Ray, const Plane&plane,
		float* distnce=nullptr , Vector3* inter = nullptr);

	/// <summary>
	/// ���C�Ɩ@���t���O�p�`�̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Triangle(const Ray& ray,const Triangle& triangle,
		float* distance=nullptr,Vector3* inter=nullptr);

	/// <summary>
	/// ���C�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="sphere">��</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere,
		float* distance = nullptr, Vector3* inter = nullptr);
};

