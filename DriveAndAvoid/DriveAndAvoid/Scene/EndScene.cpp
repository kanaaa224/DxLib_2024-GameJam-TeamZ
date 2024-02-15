#include"EndScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"


EndScene::EndScene() : count(0), back_ground_image(NULL)
{
	
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
	DrawGraph(0, 0, back_ground_image, FALSE);
	DrawFormatString(0, 0, 0xffffff, "%d", count);
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