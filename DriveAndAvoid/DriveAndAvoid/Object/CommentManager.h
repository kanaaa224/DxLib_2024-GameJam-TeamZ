#pragma once

#include"Comment.h"
#include"Player.h"

#define COMMENT_TYPE 20//�R�����g�̎��
 
class CommentManager
{
private:
	char comments[COMMENT_TYPE][50];
	Comment** comment;
	
public:
	CommentManager();
	~CommentManager();

	void Update(Player* player); // �X�V����
	void Draw() const;        // �`�揈��
	void CommentGenerate();
	bool HitComment(Collider* collider, bool can_delete);
};