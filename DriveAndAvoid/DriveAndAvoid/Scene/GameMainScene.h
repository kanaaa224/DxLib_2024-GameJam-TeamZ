#pragma once

#include"SceneBase.h"
#include"../Object/Enemy.h"
#include"../Object/Player.h"
#include"../Object/Comment.h"
#include"../Object/SuperChat.h"

#define MAX_COMMENT_NUM 2000 // �R�����g�ő吔

class GameMainScene :public SceneBase
{
private:
	int back_ground;  //�w�i�摜
	int gamemainscene_image; //�Q�[���V�[���摜
	int barrier_image;   //�o���A�摜
	int img_gameoverWindow;  // �Q�[���I�[�o�[���̃E�B���h�E�摜
	int img_gameclearWindow; // �Q�[���N���A���̃E�B���h�E�摜
	int comment_breakSE;	//�R�����g�j�󎞂�SE
	int enemy_downSE;	//�G���j����SE
	int player_damageSE;	//�_���[�W����SE
	int changescene_SE;		//�V�[���ړ�����SE
 	int input_delay; //���͒x��
	int high_score;  //�n�C�X�R�A
	int mileage;   //���s����
	int enemy_image[3];  //�G�摜
	int enemy_count[3];  //�ʂ�߂����G�J�E���g
	//int comment_count;	//���������R�����g��
	int break_count;  //���j�����G���J�E���g����
	int superchat_count;  //�X�p�`�����J�E���g����
	int save_superchat[5];  //���������X�p�`����ۑ�����
	int random_num;  //�����_���ɐ�����������������
	//const char *text[BUFFER];	//�R�����g�\��
	//unsigned int color_num[BUFFER];
	int disp_hpbar;	//HP�o�[�̕\��
	Player* player;  //�v���C���[
	int image[5];
	Comment** comment;         // �R�����g�i�G�j
	CommentData* commentDatas; // �R�����g�̃f�[�^�icsv�t�@�C�����烍�[�h�j
	Enemy** enemy;//�G�L����
	int commentDatas_num;      // �o�ꂳ����R�����g��

	bool isGameover;  // �Q�[���I�[�o�[�̏��
	bool isGameclear; // �Q�[���N���A�̏��

	SuperChat** superchat;  //�X�[�p�[�`���b�g

	int bgm; // BGM

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