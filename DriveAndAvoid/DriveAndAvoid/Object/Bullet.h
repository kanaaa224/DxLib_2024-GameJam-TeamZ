#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //�e�̃T�C�Y
	float bullet_speed;  //�e�̑���
	Vector2D bullet_pos;  //�e�̈ʒu���W
	int bullet_type;  //�e�̎��

public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //�X�V����
	void Draw() const;  //�`�揈��
	bool IsFinished();
	Vector2D GetLocation() const;  //�ʒu���W�擾
	bool Hit(Vector2D location, Vector2D size);
};