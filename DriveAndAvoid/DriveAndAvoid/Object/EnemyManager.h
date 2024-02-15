#pragma once

#include"Enemy.h"
#include"Player.h"

class EnemyManager
{
private:
	char comments[COMMENT_TYPE][50];
	Comment** normal_comment;//普通のサイズのコメント
	Comment** big_comment;//大きいサイズのコメント

public:
	CommentManager();
	~CommentManager();

	void Update(Player* player); // 更新処理
	void Draw() const;        // 描画処理
	void CommentGenerate();
	bool HitComment(Collider* collider, bool can_delete);
	bool HitNormalComment(Collider* collider, bool can_delete);
	bool HitBigComment(Collider* collider, bool can_delete);
};