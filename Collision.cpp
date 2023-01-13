#include"Collision.h"


// �Z�`�̓����蔻��obj1, 2�ɂ�����Ɣ��肷��
bool Collision::GetBoxCollision(Vector2 obj1, Vector2 obj1SIZE, Vector2 obj2, Vector2 obj2SIZE)
{
	if (obj1.x- obj1SIZE.x / 2 < obj2.x + obj2SIZE.x/2 && obj1.x + obj1SIZE.x/2>obj2.x- obj2SIZE.x / 2 &&
		obj1.y- obj1SIZE.y / 2 < obj2.y + obj2SIZE.y/2 && obj1.y + obj1SIZE.y/2>obj2.y- obj2SIZE.y / 2)
	{
		return true;
	}
	return false;
}