#pragma once

#include"Collider.h"
#include"Bullet.h"

class Player : public Collider
{
private:
	bool is_active;  //有効状態か？
	int image;  //画像データ
	float speed;  //速さ
	int hp;
	Bullet** bullet; //弾

public:
	Player();
	~Player();

	void Update();  //更新処理
	void Draw();  //描画処理

	void SetActive(bool flg); //有効フラグ設定
	float GetSpped()const;
	int GetHp()const;
	bool HitBullet(Collider* collider);
	
private:
	void Movement();  //移動処理
};