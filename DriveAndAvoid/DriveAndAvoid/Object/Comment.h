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
	Comment(const char* comment, float font_size);
	~Comment() {};
	bool Update();  //�X�V����(�R�����g�������ł��邩)
	void Draw()const;  //�`�揈��
	int HitBullet();//�e���󂯂����̏���
};