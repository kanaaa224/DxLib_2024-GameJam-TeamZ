#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //�e�̃T�C�Y
	float bullet_speed;  //�e�̑���

public:
	Bullet();
	~Bullet();

	void Draw(const Vector2D& location);  //�`�揈��
};