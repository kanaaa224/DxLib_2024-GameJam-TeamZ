#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), barrier_image(NULL), mileage(0), player(nullptr), comment(nullptr),comment_count(0),disp_hpbar(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
	for (int i = 0; i < 100; i++)
	{
		text[i] = 0;
	}
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
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}

	//オブジェクトの生成
	player = new Player;

	//オブジェクトの初期化
	player->Initialize();











	commentDatas_num = 100;

	/*for (int i = 0; i < 100; i++)
	{
		commentDatas = new CommentData;
	}

	FILE* file;
	errno_t file_result = fopen_s(&file, "Resource/dat/comment.csv", "r");

	if (file_result != 0) throw("Resource/dat/comment.csv が開けませんでした。\n");
	if (file == NULL)     throw("Resource/dat/comment.csv が開けませんでした。\n");

	char str[100];
	unsigned int font_color;
	int font_size;
	int type;

	commentDatas_num = -1;

	while (fscanf_s(file, "%[^,],%x,%d,%d\n", str, sizeof(str), &font_color, &font_size, &type) == 4) {
		CommentData commentData;
		commentData.comment    = str;
		commentData.font_color = font_color;
		commentData.font_size  = font_size;
		commentData.type       = type;

		commentDatas_num++;
		commentDatas[commentDatas_num] = commentData;
	}

	fclose(file);*/

	comment = new Comment * [commentDatas_num];

	for (int i = 0; i < commentDatas_num; i++)
	{
		comment[i] = nullptr;
	}
}

//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Update();

	//移動距離の更新
	mileage++;

	//敵生成処理
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] == nullptr)
			{
				int type = (GetRand(4) % 4) - 1; // -1 ~ 2
				if (type == -1) comment[i] = new Comment(type, 22, 0xff0000, "こんばんは");
				else            comment[i] = new Comment(type, 16, 0xffffff, "こんにちは");
				//comment[i] = new Comment(commentDatas[i].type, commentDatas[i].font_size, commentDatas[i].font_color, commentDatas[i].comment);
				text[i] = comment[i]->GetComment();
				comment_color[i] = comment[i]->GetFontColor();
				comment[i]->Initialize();
				comment_count++;
				break;
			}
		}
	}

	//敵の更新と当たり判定チェック
	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr)
		{
			comment[i]->Update(player->GetSpped());

			//画面外に行ったら、敵を削除してスコア加算
			if (comment[i]->GetLocation().x <= 0.0f)
			{
				enemy_count[comment[i]->GetType()]++;
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
				comment_count--;
			}
		}

		//当たり判定の確認
		if (comment[i] != nullptr)
		{
			if (player->HitPlayer(comment[i]->GetLocation(),comment[i]->GetBoxSize()))
			{
				player->SetActive(false);
				player->DecreaseHP(-5.0f);
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
				disp_hpbar = 60;
				comment_count--;
			}
		}

		if (comment[i] != nullptr)
		{
			if (player->HitBullet(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
			{
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
				comment_count--;
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		int k = i;
		if (comment[i] != nullptr)
		{
			text[i] = comment[i]->GetComment();
			comment_color[i] = comment[i]->GetFontColor();
		}
		else
		{
			while (comment[k] == nullptr)
			{
				k++;
			}
			if(k<100) text[i] = comment[k]->GetComment() , comment_color[i]=comment[k]->GetFontColor();
		}
	}

	//プレイヤーの燃料が体力が0未満なら、リザルトに遷移する
	if (player->GetHP() <= 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	if (disp_hpbar > 0) disp_hpbar--;

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(-mileage % 900, 0, back_ground, TRUE);
	DrawGraph(-mileage % 900 + 900, 0, back_ground, TRUE);

	//敵の描画
	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr) comment[i]->Draw();
	}

	//プレイヤーの描画
	player->Draw();

	
	//UIの描画
	if (disp_hpbar > 0)
	{
		Vector2D HPbar = player->GetLocation();
		DrawBoxAA(HPbar.x, HPbar.y - 30, HPbar.x + 110, HPbar.y - 20, 0xffffff, 0.2f, FALSE);
		for (int i = 0; i < player->GetHP(); i++)
		{
			DrawBoxAA(HPbar.x + (2 + i * 2), HPbar.y - 28, HPbar.x + (4 + i * 2), HPbar.y - 22, 0x00ff00, 1.0f, TRUE);
		}
	}
	DrawGraph(0, 0, gamemainscene_image, TRUE);
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
	DrawFormatString(195, 642, GetColor(0, 0, 0), "%.0f万人", player->GetHP());
	DrawFormatString(280, 577, GetColor(0, 0, 0), "%.0f万人", player->GetSpped());
	DrawFormatString(1100, 43, GetColor(0, 0, 0), "%08d", mileage / 10);
	DrawFormatString(10, 5, 0x00ffff, "%d", comment_count);
	for (int i = 0; i < comment_count ; i++)
	{
		if (140 + (i * 65) <= 600)
		{
			DrawBox(890, 90 + (i * 65), 1235, 140 + (i * 65), 0x000000, FALSE);
			DrawBox(891, 91 + (i * 65), 1234, 139 + (i * 65), comment_color[i], TRUE);
			DrawFormatString(890, 110 + (i * 65), 0x000000, "%s", text[i]);
		}
	}
	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

//終了時処理
void GameMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

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

	//避けた数と得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr)
		{
			comment[i]->Fialize();
			delete comment[i];
			comment[i] = nullptr;
		}
	}

	delete[] comment;
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

////当たり判定処理(プレイヤーと敵)
//bool GameMainScene::IsHitCheck(Player* p, Comment* e)
//{
//	//プレイヤーがバリアを貼っていたら、当たり判定を無視する
//	if (p->IsBarrier())
//	{
//		return false;
//	}
//
//	//敵情報が無ければ、当たり判定を無視する
//	if (e == nullptr)
//	{
//		return false;
//	}
//
//	//位置情報の差分を取得
//	Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//当たり判定サイズの大きさ取得
//	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定とする
//	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}

// 当たり判定処理(プレイヤーと敵)
bool GameMainScene::IsHitCheck(Player * p, Comment * e)
{
	//プレイヤーがバリアを貼っていたら、当たり判定を無視する
	if (p->IsBarrier())
	{
		return false;
	}
	//敵情報が無ければ、当たり判定を無視する
	if (e == nullptr)
	{
		return false;
	}
	float sx1 = p->GetLocation().x;
	float sx2 = p->GetLocation().x + p->GetBoxSize().x;
	float sy1 = p->GetLocation().y;
	float sy2 = p->GetLocation().y + p->GetBoxSize().y;
	float dx1 = e->GetLocation().x;
	float dx2 = e->GetLocation().x + e->GetBoxSize().x;
	float dy1 = e->GetLocation().y;
	float dy2 = e->GetLocation().y + e->GetBoxSize().y;
	//矩形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;
	return FALSE;
}