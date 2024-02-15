#include"GameMainScene.h"
#include"../Utility/InputControl.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>



GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), barrier_image(NULL), mileage(0), player(nullptr), comment(nullptr), commentDatas(nullptr), commentDatas_num(0),isGameover(false), isGameclear(false), disp_hpbar(0),enemy(nullptr), break_count(0),input_delay(0),superchat(nullptr),superchat_count(0),random_num(0),comment_breakSE(NULL), enemy_downSE(NULL), player_damageSE(NULL), changescene_SE(NULL)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		save_superchat[i] = NULL;
	}
	/*for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		text[i] = 0;
		color_num[i] = 0xffffff;
	}*/
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	break_count = 0;
	superchat_count = 0;
	input_delay = 0;
	//高得点値を読み込む
	ReadHighScore();

	//画像の読み込み
	back_ground = LoadGraph("Resource/images/background.png");
	gamemainscene_image = LoadGraph("Resource/images/stream.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	img_gameoverWindow  = LoadGraph("Resource/images/gameover_window.png");
	img_gameclearWindow = LoadGraph("Resource/images/gameclear_window.png");
	int result = LoadDivGraph("Resource/images/enemy.png", 3, 3, 1, 300, 350, enemy_image);
	LoadDivGraph("resource/images/SuperChat.png", 5, 5, 1, 330, 105, image);

	//SEの読み込み
	comment_breakSE = LoadSoundMem("Resource/sounds/commentbreakSE.mp3");
	enemy_downSE = LoadSoundMem("Resource/sounds/enemydownSE.mp3");
	player_damageSE = LoadSoundMem("Resource/sounds/Player_damageSE.mp3");
	changescene_SE = LoadSoundMem("Resource/sounds/backSE.mp3");
	ChangeVolumeSoundMem(150, comment_breakSE);
	ChangeVolumeSoundMem(170, enemy_downSE);
	ChangeVolumeSoundMem(170, player_damageSE);

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


	// コメントデータの初期化、読み込み
	commentDatas = new CommentData[MAX_COMMENT_NUM];
	
	FILE* file;
	errno_t file_result = fopen_s(&file, "Resource/dat/comment.csv", "r");
	
	if (file_result != 0) throw("Resource/dat/comment.csv が開けませんでした。\n");
	if (file == NULL)     throw("Resource/dat/comment.csv が開けませんでした。\n");
	
	char str[100];
	unsigned int font_color;
	int font_size;
	int type;
	
	commentDatas_num = -1;

	while (fscanf_s(file, "%[^,],%x,%d,%d\n", str, 100, &font_color, &font_size, &type) == 4) {
		CommentData commentData;
		commentData.comment = str;
		commentData.font_color = font_color;
		commentData.font_size = font_size;
		commentData.type = type;

		commentDatas_num++;
		commentDatas[commentDatas_num] = commentData;
	}
	
	int buffer = commentDatas_num;

	for (int i = commentDatas_num + 1; i < MAX_COMMENT_NUM; i++) {
		commentDatas[i] = commentDatas[GetRand(commentDatas_num)];
		commentDatas_num++;
	}
	
	fclose(file);

	
	// コメントの初期化
	comment = new Comment * [commentDatas_num];

	for (int i = 0; i < commentDatas_num; i++)
	{
		comment[i] = nullptr;
	}


	//エネミーの初期化
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	
	//スパチャの初期化
	superchat = new SuperChat * [5];
	for (int i = 0; i < 5; i++)
	{
		superchat[i] = nullptr;
	}
	

	isGameover  = false;
	isGameclear = false;
}

//更新処理
eSceneType GameMainScene::Update()
{
	if (player->GetHP() <= 0.0f) isGameover = true; // プレイヤーの体力が0未満ならゲームオーバー

	if (isGameover || isGameclear && input_delay > 120)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			PlaySoundMem(changescene_SE, DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::E_RESULT; // E_RESULT
		}
	}
	else
	{
		//プレイヤーの更新
		player->Update();

		//移動距離の更新
		mileage++;

		//エネミーの処理

		bool can_spawn_enemy = false;
		if (GetRand(100) == 0) can_spawn_enemy = true;

		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->Update();
				if ((enemy[i]->GetLocation().x < -100))   //敵が画面外に出ると消す
				{
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}
			else if (can_spawn_enemy)
			{
				int type = GetRand(2);
				enemy[i] = new Enemy(enemy_image[type], type);
				can_spawn_enemy = false;
			}
		}
		
		//敵との当たり判定
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (player->HitPlayer(enemy[i]->GetLocation(), enemy[i]->GetBoxSize()))  //プレイヤーと敵の当たり判定
				{
					//if (comment[i]->GetFontColor() == 0x00ffff) {
					//	// 回復
					//	player->DecreaseHP(2);
					//}

					player->SetActive(false);
					player->DecreaseHP(-1.0f);
					PlaySoundMem(player_damageSE, DX_PLAYTYPE_BACK, TRUE);

					delete enemy[i];
					enemy[i]=nullptr;
					disp_hpbar = 60;
				}
			}
			if (enemy[i] != nullptr)   
			{
				if (player->HitBullet(enemy[i]->GetLocation(), enemy[i]->GetBoxSize()))    //弾と敵の当たり判定
				{
					PlaySoundMem(enemy_downSE, DX_PLAYTYPE_BACK, TRUE);
					delete enemy[i];
					enemy[i] = nullptr;
					break_count++;
				}
			}
		}

		// コメント（敵）の生成、更新と当たり判定チェック
		//if (mileage / 20 % 100 == 0)
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] == nullptr)
			{
				comment[i] = new Comment(commentDatas[i].type, commentDatas[i].font_size, commentDatas[i].font_color, commentDatas[i].comment);
				comment[i]->Initialize();
				//comment_count++;
				break;
			}
		}
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] != nullptr) comment[i]->Update(player->GetSpped());

			// 画面外に行ったら、敵を削除してスコア加算
			if (comment[i] != nullptr)
			{
				if ((comment[i]->GetLocation().x + comment[i]->GetBoxSize().x) <= 0.0f)
				{
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}

			// 赤コメントはしばらくして消す
			if (comment[i] != nullptr)
			{
				if (comment[i]->GetFontColor() == 0xff0000 && (GetRand(300) == 0))
				{
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}

			// 当たり判定の確認
			if (comment[i] != nullptr)
			{
				if (player->HitPlayer(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
				{
					if (comment[i]->GetFontColor() == 0x00ffff) {
						// 回復
						player->DecreaseHP(2);
					}
					PlaySoundMem(player_damageSE, DX_PLAYTYPE_BACK, TRUE);
					player->SetActive(false);
					player->DecreaseHP(-1.0f);
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					disp_hpbar = 60;
					//comment_count--;
				}
			}

			// 弾ヒット
			if (comment[i] != nullptr)
			{
				if (player->HitBullet(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
				{
					if (comment[i]->GetFontColor() == 0x00ffff) {
						// 回復
						player->DecreaseHP(2);
					}
					PlaySoundMem(comment_breakSE, DX_PLAYTYPE_BACK, TRUE);
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}
		}

		// スパチャ
		//for (int i = 0; i < commentDatas_num; i++)
		//{
		//	//text[i] = commentDatas[GetRand(commentDatas_num)].comment.c_str();
		//	int k = i;
		//	if (comment[i] != nullptr)
		//	{
		//		if(GetRand(100) == 0)text[i] = commentDatas[i].comment.c_str();
		//	}
		//	else
		//	{
		//		while (comment[k] == nullptr)
		//		{
		//			k++;
		//		}
		//		if (k < MAX_COMMENT_NUM) text[i] = commentDatas[k].comment.c_str();
		//	}
		//}

		//プレイヤーの体力が0未満なら、リザルトに遷移する

		if (disp_hpbar > 0) disp_hpbar--;

		/*if (mileage % 100 == 0)
		{
			for (int i = 0; i < comment_count; i++)
			{
				int k = GetRand(100) + 1;
				if (comment[k] != nullptr)
				{
					text[i] = commentDatas[k].comment.c_str();
					color_num[i] = commentDatas[k].font_color;
				}
				else
				{
					while (comment[k] == nullptr)
					{
						k++;
					}
					text[i] = commentDatas[k].comment.c_str();
					color_num[i] = commentDatas[k].font_color;
				}
			}
		}*/
		if (break_count >= 3)
		{
			random_num = GetRand(4);
			save_superchat[random_num]++;
			superchat[superchat_count] = new SuperChat(image[random_num]);
			superchat_count++;
			player->IncreaseSpeed(1.0f);
			break_count = 0;
		}

		// 獲得スパチャ数に応じてコメント数を制御
		switch (superchat_count) {
		case 0:
			commentDatas_num = 5;
			break;

		case 1:
			commentDatas_num = 10;
			break;

		case 2:
			commentDatas_num = 20;
			break;

		case 3:
			commentDatas_num = 100;
			break;

		case 4:
			commentDatas_num = MAX_COMMENT_NUM - 1;
			break;
		}

		if (superchat_count >= 5)
		{
			isGameclear = true;
			input_delay++;
		}
	}
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	SetFontSize(14);

	//背景画像の描画
	DrawGraph(-mileage % 900, 0, back_ground, TRUE);
	DrawGraph(-mileage % 900 + 900, 0, back_ground, TRUE);

	//てきキャラのひょうじ
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	// コメント（敵）の描画
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
		DrawBoxAA(HPbar.x, HPbar.y - 30, HPbar.x + 106, HPbar.y - 20, 0xffffff, 0.2f, FALSE);
		for (int i = 0; i < player->GetHP(); i++)
		{
			if(i<=50)
			DrawBoxAA(HPbar.x + (2 + i * 2), HPbar.y - 28, HPbar.x + (4 + i * 2), HPbar.y - 22, 0x00ff00, 1.0f, TRUE);
		}
	}
	DrawExtendGraph(0, 0, 1280, 720, gamemainscene_image, TRUE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	//SetFontSize(15);
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
	DrawFormatString(260, 628, GetColor(0, 0, 0), "%.1f万人", player->GetHP());
	DrawFormatString(310, 577, GetColor(0, 0, 0), "%.0f万人", player->GetSpped());
	DrawFormatString(270, 645, GetColor(0, 0, 0), "%08d", mileage / 10);
	
	//スパチャの表示
	for (int i = 0; i < 5; i++)
	{
		if (superchat[i] != nullptr)
		{
			superchat[i]->Draw(i);
		}
	}

	//for (int i = 0; i < comment_count; i++)
	//{
	//	if (140 + (i * 65) <= 600)
	//	{
	//		DrawBox(890, 90 + (i * 65), 1235, 140 + (i * 65), 0x000000, FALSE);
	//		DrawBox(891, 91 + (i * 65), 1234, 139 + (i * 65), color_num[i], TRUE);
	//		DrawFormatString(895, 110 + (i * 65), 0x000000, "%s", text[i]);
	//	}
	//}

	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	DrawFormatString(0, 0, 0x000000, "%d", commentDatas_num); // コメントデータ数

	// ゲームオーバー時のアカウント凍結メッセージ
	if (isGameover || isGameclear)
	{
		int screenWidth  = 1280;
		int screenHeight = 720;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, screenWidth, screenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (isGameover)  DrawRotaGraph(screenWidth / 2, screenHeight / 2, 0.9f, 0.0f, img_gameoverWindow, true);
		if (isGameclear) DrawRotaGraph(screenWidth / 2, screenHeight / 2, 0.9f, 0.0f, img_gameclearWindow, true);
	}
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

	
	//避けた数と得点を保存
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d\n", save_superchat[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	//敵キャラの消去
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;


	// コメント（敵）の削除
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
	delete[] commentDatas;
	commentDatas = nullptr;


	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		delete superchat[i];
	}

	InitSoundMem();
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
	//プレイヤーが点滅していたら、当たり判定を無視する
	if (p->GetActive()==false)
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