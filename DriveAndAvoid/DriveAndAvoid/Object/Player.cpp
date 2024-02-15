#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#define BULLET_MAX_NUM 20
#define NORMAL_SPEED 5.0f

Player::Player() : Collider(Vector2D(100.0f, 100.0f), Vector2D(115.0f, 35.0f)), is_active(true), image(NULL), speed(NORMAL_SPEED), hp(10)
{
	bullet = new Bullet * [BULLET_MAX_NUM];

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		bullet[i] = nullptr;
	}

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/jet.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/jet.png������܂���\n");
	}
}

Player::~Player()
{
	DeleteGraph(image);
	
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			delete bullet[i];
		}
	}
}

//�X�V����
void Player::Update()
{
	//�e������������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			if (bullet[i] == nullptr)
			{
				bullet[i] = new Bullet(Vector2D(location.x + size.x + 5, location.y + size.y / 2));
				break;
			}
		}
	}

	//�e����������Ă�����A�X�V���s��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Update();
			if (bullet[i]->GetLocation().x > 1000)
			{
				delete bullet[i];
				bullet[i] = nullptr;
			}
		}
	}

	//�ړ�����
	Movement();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawGraph(location.x, location.y, image, TRUE);
	DrawBox(location.x, location.y, location.x + size.x, location.y + size.y, 0xffffff, FALSE);

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)bullet[i]->Draw();
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�ړ�����
void Player::Movement()
{
	Vector2D old_location = location;
	
	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))location.x -= speed;
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))location.x += speed;
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))location.y -= speed;
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))location.y += speed;
}

bool Player::HitBullet(Collider* collider)
{
	bool is_hit = false;
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			if (bullet[i]->Hit(collider))
			{
				delete bullet[i];
				bullet[i] = nullptr;
				is_hit = true;
			}
		}
	}
	return is_hit;
}

float Player::GetSpped()const
{
	return speed;
}

int Player::GetHp()const
{
	return hp;
}