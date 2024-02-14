#pragma once

#include"Comment.h"
#include"Player.h"

#define COMMENT_TYPE 20//コメントの種類
 
class CommentManager
{
private:
	char comments[COMMENT_TYPE][50];
	Comment** comment;
	
public:
	CommentManager();
	~CommentManager();

	void Update(Player* player); // 更新処理
	void Draw() const;        // 描画処理
	void CommentGenerate();
	bool HitComment(Collider* collider, bool can_delete);
};