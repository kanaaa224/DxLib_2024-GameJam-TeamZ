#pragma once

#include"SceneBase.h"
#include"../Object/Enemy.h"
#include"../Object/Player.h"
#include"../Object/Comment.h"
#include"../Object/SuperChat.h"

#define MAX_COMMENT_NUM 2000 // コメント最大数

class GameMainScene :public SceneBase
{
private:
	int back_ground;  //背景画像
	int gamemainscene_image; //ゲームシーン画像
	int barrier_image;   //バリア画像
	int img_gameoverWindow;  // ゲームオーバー時のウィンドウ画像
	int img_gameclearWindow; // ゲームクリア時のウィンドウ画像
	int comment_breakSE;	//コメント破壊時のSE
	int enemy_downSE;	//敵撃破時のSE
	int player_damageSE;	//ダメージ時のSE
	int changescene_SE;		//シーン移動時のSE
 	int input_delay; //入力遅延
	int high_score;  //ハイスコア
	int mileage;   //走行距離
	int enemy_image[3];  //敵画像
	int enemy_count[3];  //通り過ぎた敵カウント
	//int comment_count;	//生成したコメント数
	int break_count;  //撃破した敵をカウントする
	int superchat_count;  //スパチャをカウントする
	int save_superchat[5];  //生成したスパチャを保存する
	int random_num;  //ランダムに生成した数字を入れる
	//const char *text[BUFFER];	//コメント表示
	//unsigned int color_num[BUFFER];
	int disp_hpbar;	//HPバーの表示
	Player* player;  //プレイヤー
	int image[5];
	Comment** comment;         // コメント（敵）
	CommentData* commentDatas; // コメントのデータ（csvファイルからロード）
	Enemy** enemy;//敵キャラ
	int commentDatas_num;      // 登場させるコメント数

	bool isGameover;  // ゲームオーバーの状態
	bool isGameclear; // ゲームクリアの状態

	SuperChat** superchat;  //スーパーチャット

	int bgm; // BGM

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Comment* e);
};