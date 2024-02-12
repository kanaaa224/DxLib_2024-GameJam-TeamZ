#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	float bullet_size;  //弾のサイズ
	float bullet_speed;  //弾の速さ

public:
	Bullet();
	~Bullet();

	void Update();  //更新処理
	void Draw(const Vector2D& location) const;  //描画処理
	bool IsFinished(Vector2D& pos);
};