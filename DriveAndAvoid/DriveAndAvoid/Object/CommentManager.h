#pragma once

#include "../Utility/Vector2D.h"
#include"Player.h"

#define MAX_COMMENT_NUM 50//�R�����g�̍ő�\����
#define COMMENT_TYPE 20//�R�����g�̎��

struct Comment
{
	bool can_draw;//�R�����g��\�����邩
	int hp;
	int color;
	int type;            // �R�����g�̎��
	float speed;         // �ړ����x
	Vector2D location;   // �ʒu���
	Vector2D box_size;   // �����蔻��̑傫��
};

class CommentManager
{
private:
	Comment comment[MAX_COMMENT_NUM];

	char comments[COMMENT_TYPE][50] =
	{
		"����ɂ���",
		"����΂��",
		"���͂悤",
		"�Ȃ�̃Q�[���H",
		"���ڂ��",
		"�́H",
		"�ւ�����",
		"���܂��ˁH",
		"����",
		"��",
		"wwwwwwwwwwwwww",
		"�܂��",
		"�i��,_�T�܁j",
		"���\�\(߁��)�\�\!!",
		"�I���R���z�M��",
		"wktk",
		"w",
		"�N�ł����H",
		"!",
		"!?",
	};

public:
	CommentManager();
	~CommentManager();

	void Initialize();        // ����������
	void Update(Player* player); // �X�V����
	void Draw() const;        // �`�揈��
	void Fialize();           // �I��������

	void CommentGenerate();
};