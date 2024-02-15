#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

#define MAX_ENEMY_NUM 20

GameMainScene::GameMainScene() : back_ground_image(NULL), player(nullptr), enemy(nullptr), mileage(0)
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
	LoadDivGraph("Resource/images/enemy.png", 3, 3, 1, 300, 350, enemy_image);

	player = new Player();

	enemy = new Enemy * [MAX_ENEMY_NUM];

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		enemy[i] = nullptr;
	}
}

//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Update();

	//エネミーの更新
	bool can_spawn = false;//新しいエネミーが生成可能か
	if (GetRand(100) == 0)can_spawn = true;

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->Update())
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
		else if (can_spawn)
		{
			enemy[i] = new Enemy(enemy_image[GetRand(2)]);
			can_spawn = false;
		}
	}

	//コメント
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

	//エネミーの描画
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//コメント描画（神里が追加しました）
	comment_manager.Draw();

}

//終了時処理
void GameMainScene::Finalize()
{
	//動的確保したオブジェクトを削除する
	delete player;

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}