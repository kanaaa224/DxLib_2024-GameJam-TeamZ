#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

#define MAX_ENEMY_NUM 20

GameMainScene::GameMainScene() : back_ground_image(NULL), player(nullptr), mileage(0)
{
	
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	//画像の読み込み
	back_ground_image = LoadGraph("Resource/images/background.png");
	player = new Player();
}

//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Update();
	//敵キャラの更新
	enemy_manager.Update(player);
	//コメントの更新
	comment_manager.Update(player);

	mileage++;

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(-mileage % 1280, 0, back_ground_image, TRUE);
	DrawGraph(-mileage % 1280 + 1280, 0, back_ground_image, TRUE);

	//プレイヤーの描画
	player->Draw();
	//敵キャラの更新
	enemy_manager.Draw();
	//コメント描画
	comment_manager.Draw();

}

//終了時処理
void GameMainScene::Finalize()
{
	//動的確保したオブジェクトを削除する
	delete player;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}