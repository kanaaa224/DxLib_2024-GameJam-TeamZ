#include"Player.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#define BULLET_MAX_NUM 20

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f), speed(0.0f), bullet(nullptr)
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
	speed = 3.0f;

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
		throw("Resource/images/car1pol.bmp������܂���\n");
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
				bullet[i] = new Bullet(Vector2D(location.x + box_size.x, location.y + box_size.y / 2));
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
	DrawBox(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xffffff, FALSE);

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)bullet[i]->Draw();
	}
}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�o���A�����擾����
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//�ړ�����
void Player::Movement()
{
	Vector2D old_location = location;
	
	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		location.x -= speed;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		location.x += speed;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		location.y -= speed;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		location.y += speed;
	}

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 550.0f - box_size.y))
	{
		location = old_location;
	}
}

bool Player::HitBullet(Vector2D location, Vector2D size)
{
	bool is_hit = false;
	for (int i = 0; i < BULLET_MAX_NUM; i++)
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
	float sx1 = this->location.x;
	float sx2 = this->location.x + this->box_size.x;
	float sy1 = this->location.y;
	float sy2 = this->location.y + this->box_size.y;

	float dx1 = location.x;
	float dx2 = location.x + size.x;
	float dy1 = location.y;
	float dy2 = location.y + size.y;

	//��`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;

	return FALSE;
}

float Player::GetSpped()const
{
	return speed;
}

int Player::GetHp()const
{
	return hp;
}