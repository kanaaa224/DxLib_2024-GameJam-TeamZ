#pragma once

#include"Collider.h"
#include"Bullet.h"

class Player : public Collider
{
private:
	bool is_active;  //�L����Ԃ��H
	int image;  //�摜�f�[�^
	float speed;  //����
	int hp;
	Bullet** bullet; //�e

public:
	Player();
	~Player();

	void Update();  //�X�V����
	void Draw();  //�`�揈��

	void SetActive(bool flg); //�L���t���O�ݒ�
	float GetSpped()const;
	int GetHp()const;
	bool HitBullet(Collider* collider);
	
private:
	void Movement();  //�ړ�����
};