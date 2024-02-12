#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"Bullet.h"

class Player
{
private:
	bool is_active;  //�L����Ԃ��H
	int image;  //�摜�f�[�^
	Vector2D location;  //�ʒu���W
	Vector2D box_size;  //�����蔻��̑傫��
	float speed;  //����
	int barrier_count;  //�o���A�̖���
	Barrier* barrier;  //�o���A
	Bullet** bullet; //�e
	int hp;

public:
	Player();
	~Player();

	void Initialize();  //����������
	void Update();  //�X�V����
	void Draw();  //�`�揈��
	void Finalize() ;  //�I��������

public:

	void SetActive(bool flg); //�L���t���O�ݒ�
	Vector2D GetLocation() const;  //�ʒu���W�擾
	Vector2D GetBoxSize() const;  //�����蔻��̑傫���擾
	int GetBarrierCount() const;  //�o���A�̖����擾
	bool IsBarrier() const;  //�o���A�L�����H���擾
	float GetSpped()const;
	int GetHp()const;
	bool HitBullet(Vector2D location, Vector2D size);
	bool HitPlayer(Vector2D location, Vector2D size);

private:
	void Movement();  //�ړ�����

};