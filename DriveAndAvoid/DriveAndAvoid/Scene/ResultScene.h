#pragma once

#include"SceneBase.h"

class ResultScene :public SceneBase
{
private:
	int back_ground;  //�w�i�摜
	int main_image;	//�w�i�摜
	int titleback_SE;	//�^�C�g���ɖ߂�SE
	int image[5];  //�X�p�`���摜
	int superchats[5];  //���������X�p�`����ۑ�����
	int score; // �X�R�A�i�X�p�`���ŉ҂������v�z�j

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