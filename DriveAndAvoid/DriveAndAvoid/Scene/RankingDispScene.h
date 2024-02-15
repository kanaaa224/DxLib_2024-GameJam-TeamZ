#pragma once

#include"SceneBase.h"
#include"../Object/RankingData.h"

class RankingDispScene :public SceneBase
{
private:
	int background_image;  //�w�i�摜
	int ranking_board_image;
	int titleback_SE;	//�^�C�g���ɖ߂�SE
	RankingData* ranking;  //�����L���O���

public:
	RankingDispScene();
	virtual ~RankingDispScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};