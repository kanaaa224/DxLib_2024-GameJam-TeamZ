#pragma once

#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:
	int img_logo; // ���S�摜
	int background_image;  //�w�i�摜
	int chara_image;//�^�C�g����ʂ̃L�����N�^�[�摜
	int menu_image;  //���j���[�摜
	int cursor_image;  //�J�[�\���摜
	int menu_cursor;   //���j���[�J�[�\���ԍ�
	int cursor_moveSE;	//�J�[�\���ړ�����SE
	int cursor_selectSE;	//���莞��SE
	int bgm; // BGM

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};