#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/CommentManager.h"
#include"../Object/EnemyManager.h"

class GameMainScene :public SceneBase
{
private:
	int back_ground_image;  //�w�i�摜
	
	int mileage;//���s����
	Player* player;  //�v���C���[
	CommentManager comment_manager;//�R�����g�Ǘ�
	EnemyManager enemy_manager;//�G�Ǘ�

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};