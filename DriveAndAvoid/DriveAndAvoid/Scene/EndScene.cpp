#include"EndScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"


EndScene::EndScene() : count(0), back_ground_image(NULL)
{
	SetFontSize(50);
}

EndScene::~EndScene()
{

}

//初期化処理
void EndScene::Initialize()
{
	back_ground_image = LoadGraph("Resource/images/title_background.png");
}

//更新処理
eSceneType EndScene::Update()
{
	count++;

	if (count > 200)
	{
		return eSceneType::END;
	}

	return GetNowScene();
}

//描画処理
void EndScene::Draw() const
{
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, back_ground_image, FALSE);
	
	SetDrawBright(255, 255, 255);
	DrawString(510, 100, "クレジット", 0xffffff);
	DrawString(305, 300, "お借りした音源　　　魔王魂", 0xffffff);
	DrawString(265, 400, "お借りしたイラスト　いらすとや", 0xffffff);
	DrawString(805, 470, "illustAC", 0xffffff);
	DrawString(805, 540, "illalet", 0xffffff);
}

//終了時処理
void EndScene::Finalize()
{
	DeleteGraph(back_ground_image);
}

//現在のシーン情報を取得
eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}