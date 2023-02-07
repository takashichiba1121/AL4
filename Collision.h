#pragma once
#include"CollisionPrimitive.h"

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
		plane, DirectX::XMVECTOR* inter = nullptr);

	///<summary>
	///�_�ƎO�p�`�̍ŋߐړ_�����߂�
	///</summary>
	///<param name="point">�_</param>
	///<param name="triangle">�O�p�`</param>
	///<param name="closest">�ŋߌ�_(�o�͗p)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point ,
		const Triangle&triangle,DirectX::XMVECTOR* closest);

	///<summary>
	///�_�ƎO�p�`�̓����蔻��`�F�b�N
	///</summary>
	///<param name="point">��</param>
	///<param name="triangle">�O�p�`</param>
	///<param name="closest">��_(�O�p�`��̍ŋߐړ_)</param>
	///<returns>�������Ă邩�ۂ�</retuns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle&
		triangle, DirectX::XMVECTOR* inter = nullptr);
};

