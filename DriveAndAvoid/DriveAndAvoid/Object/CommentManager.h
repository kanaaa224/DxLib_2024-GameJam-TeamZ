#pragma once

#include "../Utility/Vector2D.h"
#include"Player.h"

#define MAX_COMMENT_NUM 50//コメントの最大表示数
#define COMMENT_TYPE 20//コメントの種類

struct Comment
{
	bool can_draw;//コメントを表示するか
	int hp;
	int color;
	int type;            // コメントの種類
	float speed;         // 移動速度
	Vector2D location;   // 位置情報
	Vector2D box_size;   // 当たり判定の大きさ
};

class CommentManager
{
private:
	Comment comment[MAX_COMMENT_NUM];

	char comments[COMMENT_TYPE][50] =
	{
		"こんにちは",
		"こんばんは",
		"おはよう",
		"なんのゲーム？",
		"同接やば",
		"は？",
		"へたくそ",
		"うまくね？",
		"うわ",
		"あ",
		"wwwwwwwwwwwwww",
		"つまんな",
		"（⌒,_ゝ⌒）",
		"ｷﾀ――(ﾟ∀ﾟ)――!!",
		"オワコン配信者",
		"wktk",
		"w",
		"誰ですか？",
		"!",
		"!?",
	};

public:
	CommentManager();
	~CommentManager();

	void Initialize();        // 初期化処理
	void Update(Player* player); // 更新処理
	void Draw() const;        // 描画処理
	void Fialize();           // 終了時処理

	void CommentGenerate();
};