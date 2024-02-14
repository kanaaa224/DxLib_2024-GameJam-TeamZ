#pragma once

#include"../Utility/Vector2D.h"

class Enemy
{
private:
	int image_handle;  //�摜
	int type;//�G�l�~�[�^�C�v
	Vector2D location;  //�ʒu���W
	Vector2D box_size;  //�����蔻��̑傫��
	float speed;  //����
	int  angle;//�v���C���[����]����p�x


public:
	Enemy(int image_handle, int type);
	~Enemy();

	void Update();  //�X�V����
	void Draw();  //�`�揈��
	
public:
	Vector2D GetLocation() const;  //�ʒu���W�擾
	Vector2D GetBoxSize() const;  //�����蔻��̑傫���擾
};