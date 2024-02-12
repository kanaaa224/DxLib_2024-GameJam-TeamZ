#pragma once

#include"../Utility/Vector2D.h"

class Bullet 
{
private:
	Vector2D location;  //位置座標
	float size;  //当たり判定の大きさ

public:
	Bullet(Vector2D location);
	~Bullet();

	void Update();  //更新処理
	void Draw() const;  //描画処理
	Vector2D GetLocation();
	bool Hit(Vector2D location, Vector2D size);
};