#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), bullet_count(0),bullet_flg(true)
{

}

Player::~Player()
{

}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(115.0f, 35.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 50;
	fuel = 20000;
	bullet_count = 0;
	bullet_flg = true;
	bullet = new Bullet * [20];

	for (int i = 0; i < 20; i++)
	{
		bullet[i] = nullptr;
		bullet_pos[i] = 0;
	}

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/jet.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���\n");
	}
}

//�X�V����
void Player::Update()
{

	if (bullet_count >= 20)
	{
		bullet_count = 0;
	}

	//�e������������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && bullet_count < 20)
	{
		if (bullet[bullet_count] == nullptr)
		{
			bullet_pos[bullet_count] = location;
			bullet[bullet_count] = new Bullet(location + 20);
			bullet_count++;

		}
	}

	//�e����������Ă�����A�X�V���s��
	for (int i = 0; i < 20; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Update();
			if (bullet[i]->IsFinished() || bullet_flg == false)
			{
				delete bullet[i];
				bullet[i] = nullptr;
				bullet_pos[i] = 0;
			}
		}
	}

	if (!is_active)
	{
		count++;
		if (count > 100)
		{
			count = 0;
			is_active = true;
		}
	}

	//�ړ�����
	Movement();

	//����������5
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

}

//�`�揈��
void Player::Draw()
{
	if (!is_active)
	{
		if (count % 5 == 0)DrawGraphF(location.x, location.y, image, TRUE);
	}
	if(is_active)
	{
		//�v���C���[�摜�̕`��
		DrawGraphF(location.x, location.y, image, TRUE);
	}

	for (int i=0; i < 20; i++)
	{
		//�e����������Ă�����A�`����s��
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}
}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(image);


	for (int i = 0; i < 20; i++)
	{
		delete bullet[i];
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�e�̏�Ԑݒ�Ǘ�
void Player::SetBulletActive(bool flg)
{
	this->bullet_flg = flg;
}

//�̗͌�������
void Player::DecreaseHP(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�e�̈ʒu���W�擾
Vector2D Player::GetBulletLocation() 
{
	return  this->bullet_pos[bullet_count] += bullet[bullet_count]->GetLocation();	
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpped() const
{
	return this->speed;
}


//�̗͎擾����
float Player::GetHP() const
{
	return this->hp;
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-3.0f, 0.0f);
		
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(3.0f, 0.0f);
		
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -3.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 3.0f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 510.0f - box_size.y))
	{
		location -= move;
	}
}

//��������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RB�{�^���������ꂽ��A��������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}

//�e�̓����蔻��`�F�b�N
bool Player::HitBullet(Vector2D location, Vector2D size)
{
	bool is_hit = false;
	for (int i = 0; i < 20; i++)
	{
		if (bullet[i] != nullptr)
		{
			if (bullet[i]->Hit(location, size))
			{
				delete bullet[i];
				bullet[i] = nullptr;
				is_hit = true;
			}
		}
	}
	return is_hit;
}

bool Player::HitPlayer(Vector2D location, Vector2D size)
{
	if (!is_active)
	{
		return false;
	}

	float sx1 = this->location.x;
	float sx2 = this->location.x + this->box_size.x;
	float sy1 = this->location.y ;
	float sy2 = this->location.y + this->box_size.y;
	float dx1 = location.x;
	float dx2 = location.x + size.x;
	float dy1 = location.y;
	float dy2 = location.y + size.y;
	//��`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;
	return FALSE;
}


bool Player::GetActive()
{
	return is_active;
}