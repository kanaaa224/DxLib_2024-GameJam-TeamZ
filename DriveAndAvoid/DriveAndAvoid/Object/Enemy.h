#pragma once

#include "Collider.h"

class Enemy : public Collider
{
private:
	float speed;         // 移動速度
	int image_handle;
	float angle;

public:
	Enemy(int image_handle); // typeが0は移動無し
	~Enemy();

	bool Update(); // 更新処理
	void Draw() const;        // 描画処理
};