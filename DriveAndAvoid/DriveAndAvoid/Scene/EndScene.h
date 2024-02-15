#pragma once

#include"SceneBase.h"

class EndScene :public SceneBase
{
private:
	int back_ground_image;
	int count;

public:
	EndScene();
	~EndScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowScene() const override;
};