#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //弾のサイズ
	float bullet_speed;  //弾の速さ
	Vector2D bullet_pos;  //弾の位置座標
	int bullet_type;  //弾の種類

public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //更新処理
	void Draw() const;  //描画処理
	bool IsFinished();
	Vector2D GetLocation() const;  //位置座標取得
	bool Hit(Vector2D location, Vector2D size);
};