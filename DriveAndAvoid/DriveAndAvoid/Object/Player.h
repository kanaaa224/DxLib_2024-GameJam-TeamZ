#pragma once

#include"../Utility/Vector2D.h"
#include"Bullet.h"

enum AnimPlayer
{
	FIRE01,
	FIRE02,
	FIRE03
};

class Player
{
private:
	bool is_active;  //�L����Ԃ��H
	int image;  //�摜�f�[�^
	int fire_image01; //���̉摜�f�[�^
	int fire_image02;  
	Vector2D location;  //�ʒu���W
	Vector2D box_size;  //�����蔻��̑傫��
	float angle;  //�p�x
	float speed;  //����
	float hp;  //�̗�
	float fuel;  //�R��
	int bullet_count; //�e�c��
	Vector2D bullet_pos[60];  //�e�̔��ˏꏊ
	Bullet** bullet; //�e
	bool bullet_flg; //�o���b�g����������Ă��邩�H
	int count;   //�_�ŗp�J�E���g
	AnimPlayer now_anim; //���݂̃A�j���[�V����
	int delay;  //�x��
	
public:
	Player();
	~Player();

	void Initialize();  //����������
	void Update();  //�X�V����
	void Draw();  //�`�揈��
	void Finalize() ;  //�I��������

public:
	void SetActive(bool flg); //�L���t���O�ݒ�
	bool GetActive(); //�v���C���[���̃t���O���擾����
	void SetBulletActive(bool flg); //�e�̗L���t���O�ݒ�
	void DecreaseHP(float value);  //�̗͌�������
	void IncreaseSpeed(float value); //	�X�s�[�h��������
	Vector2D GetLocation() const;  //�ʒu���W�擾
	Vector2D GetBulletLocation();  //�ʒu���W�擾
	Vector2D GetBoxSize() const;  //�����蔻��̑傫���擾
	float GetSpped() const;  //�����擾����
	float GetHP() const;  //�̗͎擾
	bool HitBullet(Vector2D location, Vector2D size); //�e�̓����蔻��
	bool HitPlayer(Vector2D location, Vector2D size); //�v���C���[�̓����蔻��
	void ChangeAnim(AnimPlayer anim);  //�A�j���[�V�����̐؂�ւ�����

private:
	void Movement();  //�ړ�����
	void Acceleration();  //��������
};