#include"RankingDispScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

RankingDispScene::RankingDispScene() :background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

//初期化処理
void RankingDispScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/ranking_background.png");
	ranking_board_image = LoadGraph("Resource/images/ranking_board.png");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Ranking.bmpがありません\n");
	}

	//ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();
	SetFontSize(30);
}

//更新処理
eSceneType RankingDispScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void RankingDispScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, TRUE);
	DrawRotaGraph(640, 360, 1, 0, ranking_board_image, TRUE);
	

	
	//取得したランキングデータを描画する
	for (int i = 0; i < 10; i++)
	{
		DrawFormatString(500, 184 + i * 49, 0x000000, "%2d %-7s %6d", ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
}

//終了時処理
void RankingDispScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(ranking_board_image);

	//動的メモリの解放
	ranking->Finalize();
	delete ranking;
}

//現在のシーン情報を取得
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}