#pragma once

#include "SceneBase.h"

class TitleScene :public SceneBase
{
private:
	int img_logo; // ロゴ画像
	int background_image;  //背景画像
	int chara_image;//タイトル画面のキャラクター画像
	int menu_image;  //メニュー画像
	int cursor_image;  //カーソル画像
	int menu_cursor;   //メニューカーソル番号
	int cursor_moveSE;	//カーソル移動時のSE
	int cursor_selectSE;	//決定時のSE
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