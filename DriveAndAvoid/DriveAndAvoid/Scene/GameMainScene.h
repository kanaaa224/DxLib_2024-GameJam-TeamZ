#pragma once

#include"SceneBase.h"
#include"../Object/Enemy.h"
#include"../Object/Player.h"
#include"../Object/Comment.h"

class GameMainScene :public SceneBase
{
private:
	int high_score;  //�n�C�X�R�A
	int back_ground;  //�w�i�摜
	int gamemainscene_image; //�Q�[���V�[���摜
	int barrier_image;   //�o���A�摜
	int mileage;   //���s����
	int enemy_image[3];  //�G�摜
	int enemy_count[3];  //�ʂ�߂����G�J�E���g
	int comment_count;	//���������R�����g��
	const char *text[100];	//�R�����g�\��
	int disp_hpbar;	//HP�o�[�̕\��
	Player* player;  //�v���C���[

	Comment** comment;         // �R�����g�i�G�j
	CommentData* commentDatas; // �R�����g�̃f�[�^�icsv�t�@�C�����烍�[�h�j
	Enemy** enemy;//�G�L����
	int commentDatas_num;      // �R�����g�̃f�[�^�̐�

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();
	//�����蔻��
	bool IsHitCheck(Player* p, Comment* e);
};