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
	DrawGraph(-mileage % 900, 0, back_ground, TRUE);
	DrawGraph(-mileage % 900 + 900, 0, back_ground, TRUE);

	//コメント描画（神里が追加しました）
	comment_manager.Draw();

	//プレイヤーの描画
	player->Draw();

	//UIの描画
	DrawGraph(0, 0, gamemainscene_image, TRUE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(15);
	//DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	//DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	//DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");
	//for (int i = 0; i < 3; i++)
	//{
	//	DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
	//	DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);

	//}
	//DrawFormatString(510, 200, GetColor(0, 0, 0), "走行距離");
	//DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	//DrawFormatString(510, 240, GetColor(0, 0, 0), "スピード");
	//DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpped());

	////バリア枚数の描画
	//for (int i = 0; i < player->GetBarrierCount(); i++)
	//{
	//	DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	//}

	////燃料ゲージの描画
	//float fx = 510.0f;
	//float fy = 390.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	////体力ゲージの描画
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(195, 642, GetColor(0, 0, 0), "%.0f万人", player->GetHp());
	//DrawFormatStringF(280, 577, GetColor(0, 0, 0), "%.0f万人", player->GetSpped());
	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
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