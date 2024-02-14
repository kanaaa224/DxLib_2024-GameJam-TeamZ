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
	Comment(const char* comment, int font_size);
	~Comment() {};
	bool Update(Player* player);  //更新処理(戻り値で、現在コメントが消せるかを返す)
	void Draw();  //描画処理
};