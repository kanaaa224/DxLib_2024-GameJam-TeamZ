#pragma once

#include"../Utility/Vector2D.h"
#include"Barrier.h"
#include"Bullet.h"

class Player
{
private:
	bool is_active;  //有効状態か？
	int image;  //画像データ
	Vector2D location;  //位置座標
	Vector2D box_size;  //当たり判定の大きさ
	float speed;  //速さ
	int barrier_count;  //バリアの枚数
	Barrier* barrier;  //バリア
	Bullet** bullet; //弾
	int hp;

public:
	Player();
	~Player();

	void Initialize();  //初期化処理
	void Update();  //更新処理
	void Draw();  //描画処理
	void Finalize() ;  //終了時処理

public:

	void SetActive(bool flg); //有効フラグ設定
	Vector2D GetLocation() const;  //位置座標取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさ取得
	int GetBarrierCount() const;  //バリアの枚数取得
	bool IsBarrier() const;  //バリア有効か？を取得
	float GetSpped()const;
	int GetHp()const;
	bool HitBullet(Vector2D location, Vector2D size);
	bool HitPlayer(Vector2D location, Vector2D size);

private:
	void Movement();  //移動処理

};