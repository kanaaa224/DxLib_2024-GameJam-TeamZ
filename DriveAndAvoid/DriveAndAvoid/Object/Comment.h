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
	void Update();  //�X�V����
	void Draw()const;  //�`�揈��
	int HitBullet();//�e���󂯂����̏���
};