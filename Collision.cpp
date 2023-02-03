#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, XMVECTOR* inter)
{
    //���W�n�̒��_���狅�̒��S���W�ւ̋���
    XMVECTOR distV = XMVector3Dot(sphere.center,plane.nolmal);
    //���ʂ̋��������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
    float dist = distV.m128_f32[0] - plane.distance;
    //�����̐�Βl�����a���傫����Γ������Ă��Ȃ�
    if (fabsf(dist) > sphere.radius) {return false;}

    //�^����_���v�Z
    if (inter) {
        //���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
        *inter = -dist * plane.nolmal + sphere.center;
    }

    return true;
}
