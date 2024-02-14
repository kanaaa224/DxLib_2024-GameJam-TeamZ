#pragma once

#include"../Utility/Vector2D.h"

class Enemy
{
private:
	int image_handle;  //画像
	int type;//エネミータイプ
	Vector2D location;  //位置座標
	Vector2D box_size;  //当たり判定の大きさ
	float speed;  //速さ
	int hp;  //体力

public:
	Enemy(int image_handle, int type);
	~Enemy();

	void Update();  //更新処理
	void Draw();  //描画処理
	
public:
	Vector2D GetLocation() const;  //位置座標取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさ取得
	int GetHp() const;  //体力取得
	void SetHp(int hp);
};