#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	Vector2D location;  //�ʒu���W
	float size;  //�����蔻��̑傫��

public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //�X�V����
	void Draw() const;  //�`�揈��
	Vector2D GetLocation();
	bool Hit(Vector2D location, Vector2D size);
};