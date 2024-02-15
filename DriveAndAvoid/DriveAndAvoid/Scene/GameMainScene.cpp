#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), mileage(0), player(nullptr)
{
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	//高得点値を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/background.png");
	gamemainscene_image = LoadGraph("Resource/images/GameMainScene Image.png");
	LoadGraph("Resource/images/barrier.png");

	player = new Player();
}

//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Update();

	//移動距離の更新
	mileage++;

	//コメント管理（神里が追加しました）
	comment_manager.Update(player);

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(-mileage % 1280, 0, back_ground, TRUE);
	DrawGraph(-mileage % 1280 + 1280, 0, back_ground, TRUE);

	//プレイヤーの描画
	player->Draw();

	//コメント描画（神里が追加しました）
	comment_manager.Draw();

}

//終了時処理
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);
	
	//リザルトデータの書き込み
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開けませんでした\n");
	}

	//スコア保存
	fprintf(fp, "%d,\n", score);

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	delete player;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}