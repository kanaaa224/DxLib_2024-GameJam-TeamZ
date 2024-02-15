#pragma once

#include"Collider.h"
#include"Player.h"

class Comment : public Collider
{
private:
	const char* comment;//コメント
	float speed;  //速さ
	int hp;
	int color;

public:
	Comment(const char* comment, float font_size);
	~Comment() {};
	bool Update();  //更新処理(コメントを消去できるか)
	void Draw()const;  //描画処理
	int HitBullet();//弾を受けた時の処理
};