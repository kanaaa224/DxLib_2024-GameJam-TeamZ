#pragma once

#include"SceneBase.h"
#include"../Object/Player.h"
#include"../Object/CommentManager.h"
#include"../Object/EnemyManager.h"

class GameMainScene :public SceneBase
{
private:
	int back_ground_image;  //背景画像
	
	int mileage;//走行距離
	Player* player;  //プレイヤー
	CommentManager comment_manager;//コメント管理
	EnemyManager enemy_manager;//敵管理

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};