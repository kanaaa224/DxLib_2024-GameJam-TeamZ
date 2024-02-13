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

//初期化処理
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

	//画像の読み込み
	image = LoadGraph("Resource/images/jet.png");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません\n");
	}
}

//更新処理
void Player::Update()
{
	//弾生成処理処理
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

	//弾が生成されていたら、更新を行う
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

	//移動処理
	Movement();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawGraph(location.x, location.y, image, TRUE);
	DrawBox(location.x, location.y, location.x + box_size.x, location.y + box_size.y, 0xffffff, FALSE);

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i] != nullptr)bullet[i]->Draw();
	}
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//バリア枚数取得処理
int Player::GetBarrierCount() const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//移動処理
void Player::Movement()
{
	Vector2D old_location = location;
	
	//十字移動処理
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

	//画面外に行かないように制限する
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

	//矩形が重なっていれば当たり
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