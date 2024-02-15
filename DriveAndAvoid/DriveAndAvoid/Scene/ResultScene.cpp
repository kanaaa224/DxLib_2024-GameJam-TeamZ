#include"ResultScene.h"
#include"../Object/RankingData.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

ResultScene::ResultScene() :back_ground(NULL), score(0), main_image(NULL)
{
	for (int i = 0; i < 5; i++)
	{
		image[i] = NULL;
		save_superchat[i]= NULL;
	}
}

ResultScene::~ResultScene()
{

}

//初期化処理
void ResultScene::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/background.png");
	main_image = LoadGraph("Resource/images/GameMainScene Image.png");
	int result = LoadDivGraph("resource/images/SuperChat.png", 5, 5, 1, 330, 105, image);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (main_image == -1)
	{
		throw("Resource/images/GameMainScene Image.pngがありません\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();
}

//更新処理
eSceneType ResultScene::Update()
{
	//Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	DrawRotaGraph(0, 0,2.0f,0.0, back_ground, TRUE);
	//DrawGraph(0, 0, main_image, TRUE);

	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(230, 100 + (i * 120), 1.0f, 0.0, image[i], TRUE);
		DrawFormatString(260,100+ (i * 120), GetColor(255, 255, 255), "x %4d", save_superchat[i]);
	}
	
}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(image[i]);
	}
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが読み込めません\n");
	}

	//避けた数と得点を取得
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%d\n", &save_superchat[i]);
	}

	//ファイルクローズ
	fclose(fp);
}