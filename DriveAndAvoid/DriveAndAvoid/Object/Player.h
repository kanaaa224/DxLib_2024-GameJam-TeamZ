#pragma once

#include"../Utility/Vector2D.h"
#include"Bullet.h"

enum AnimPlayer
{
	FIRE01,
	FIRE02,
	FIRE03
};

class Player
{
private:
	bool is_active;  //有効状態か？
	int image;  //画像データ
	int fire_image01; //炎の画像データ
	int fire_image02;  
	Vector2D location;  //位置座標
	Vector2D box_size;  //当たり判定の大きさ
	float angle;  //角度
	float speed;  //速さ
	float hp;  //体力
	float fuel;  //燃料
	int bullet_count; //弾残数
	Vector2D bullet_pos[60];  //弾の発射場所
	Bullet** bullet; //弾
	bool bullet_flg; //バレットが生成されているか？
	int count;   //点滅用カウント
	AnimPlayer now_anim; //現在のアニメーション
	int delay;  //遅延
	
public:
	Player();
	~Player();

	void Initialize();  //初期化処理
	void Update();  //更新処理
	void Draw();  //描画処理
	void Finalize() ;  //終了時処理

public:
	void SetActive(bool flg); //有効フラグ設定
	bool GetActive(); //プレイヤー側のフラグを取得する
	void SetBulletActive(bool flg); //弾の有効フラグ設定
	void DecreaseHP(float value);  //体力減少処理
	void IncreaseSpeed(float value); //	スピード増加処理
	Vector2D GetLocation() const;  //位置座標取得
	Vector2D GetBulletLocation();  //位置座標取得
	Vector2D GetBoxSize() const;  //当たり判定の大きさ取得
	float GetSpped() const;  //速さ取得処理
	float GetHP() const;  //体力取得
	bool HitBullet(Vector2D location, Vector2D size); //弾の当たり判定
	bool HitPlayer(Vector2D location, Vector2D size); //プレイヤーの当たり判定
	void ChangeAnim(AnimPlayer anim);  //アニメーションの切り替え処理

private:
	void Movement();  //移動処理
	void Acceleration();  //加速処理
};