#pragma once

#include"SceneBase.h"

class ResultScene :public SceneBase
{
private:
	int back_ground;  //背景画像
	int main_image;	//背景画像
	int titleback_SE;	//タイトルに戻るSE
	int score;  //スコア
	int image[5];  //スパチャ画像
	int save_superchat[5];  //生成したスパチャを保存する

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();
};