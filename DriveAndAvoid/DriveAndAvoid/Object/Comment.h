#pragma once

#include "../Utility/Vector2D.h"

class Comment
{
private:
	int type;            // タイプ
	int font_size;       // コメントのフォントサイズ
	int font_color;      // コメントのフォントカラー
	const char* comment; // コメント
	float speed;         // 移動速度
	Vector2D location;   // 位置情報
	Vector2D box_size;   // 当たり判定の大きさ

public:
	Comment(int type, int font_size, int font_color, const char* string); // typeが0は移動無し
	~Comment();

	void Initialize();        // 初期化処理
	void Update(float spped); // 更新処理
	void Draw() const;        // 描画処理
	void Fialize();           // 終了時処理

	int GetType() const;          // タイプ取得
	Vector2D GetLocation() const; // 位置情報の取得
	Vector2D GetBoxSize() const;  // 当たり判定の大きさを取得
	const char *GetComment();		  //コメント内容取得
};