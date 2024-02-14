#pragma once

#include"Collider.h"
#include"Player.h"

class Comment : public Collider
{
private:
	const char* comment;//�R�����g
	float speed;  //����
	int hp;
	int color;

public:
	Comment(const char* comment, int font_size);
	~Comment() {};
	bool Update(Player* player);  //�X�V����(�߂�l�ŁA���݃R�����g�������邩��Ԃ�)
	void Draw();  //�`�揈��
};