#pragma once

#include"Comment.h"

#define COMMENT_TYPE 20//�R�����g�̎��
 
class CommentManager
{
private:
	char comments[COMMENT_TYPE][50];
	Comment** comment;
	
public:
	CommentManager();
	~CommentManager();

	void Update(); // �X�V����
	void Draw() const;        // �`�揈��

	void CommentGenerate();
	bool HitComment(Collider* collider, bool can_delete);
};