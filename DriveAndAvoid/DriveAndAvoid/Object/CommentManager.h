#pragma once

#include"Comment.h"
#include"Player.h"

#define COMMENT_TYPE 20//�R�����g�̎��
 
class CommentManager
{
private:
	char comments[COMMENT_TYPE][50];
	Comment** normal_comment;//���ʂ̃T�C�Y�̃R�����g
	Comment** big_comment;//�傫���T�C�Y�̃R�����g
	
public:
	CommentManager();
	~CommentManager();

	void Update(Player* player); // �X�V����
	void Draw() const;        // �`�揈��
	void CommentGenerate();
	bool HitComment(Collider* collider, bool can_delete);
	bool HitNormalComment(Collider* collider, bool can_delete);
	bool HitBigComment(Collider* collider, bool can_delete);

};