#pragma once

#include"Collider.h"

class Bullet : public Collider
{
private:
	Vector2D location;  //�ʒu���W
	float size;  //�����蔻��̑傫��

public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //�X�V����
	void Draw() const;  //�`�揈��
};