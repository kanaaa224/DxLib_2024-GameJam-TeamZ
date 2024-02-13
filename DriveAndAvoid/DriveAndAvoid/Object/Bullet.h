#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //�e�̃T�C�Y
	float bullet_speed;  //�e�̑���
	float bullet_pos;  //�e�̈ʒu���W
	int bullet_type;  //�e�̎��

public:
	Bullet(int type);
	~Bullet();

	void Update();  //�X�V����
	void Draw(const Vector2D& location) const;  //�`�揈��
	bool IsFinished(Vector2D& pos);
};