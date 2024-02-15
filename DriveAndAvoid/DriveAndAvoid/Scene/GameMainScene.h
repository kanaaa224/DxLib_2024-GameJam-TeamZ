#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/CommentManager.h"
#include"../Object/Enemy.h"

class GameMainScene :public SceneBase
{
private:
	int back_ground_image;  //背景画像
	int enemy_image[3];//敵画像
	
	int mileage;//走行距離
	Player* player;  //プレイヤー
	Enemy** enemy;  //敵
	CommentManager comment_manager;//コメント管理(神里が追加しました)

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};