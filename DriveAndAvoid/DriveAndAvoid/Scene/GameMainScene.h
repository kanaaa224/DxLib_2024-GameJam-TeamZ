#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/CommentManager.h"

class GameMainScene :public SceneBase
{
private:
	int high_score;  //�n�C�X�R�A
	int back_ground;  //�w�i�摜
	int gamemainscene_image; //�Q�[���V�[���摜
	int mileage;   //���s����
	Player* player;  //�v���C���[
	CommentManager comment_manager;//�R�����g�Ǘ�(�_�����ǉ����܂���)

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
};