#pragma once

#include"SceneBase.h"
#include"../Object/RankingData.h"

class RankingDispScene :public SceneBase
{
private:
	int background_image;  //背景画像
	int ranking_board_image;
	int titleback_SE;	//タイトルに戻るSE
	RankingData* ranking;  //ランキング情報

public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};