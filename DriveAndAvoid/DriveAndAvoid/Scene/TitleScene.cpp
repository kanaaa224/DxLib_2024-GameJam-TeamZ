#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	chara_image = LoadGraph("Resource/images/title_chara.png");
	background_image = LoadGraph("Resource/images/title_background.png");
	menu_image = LoadGraph("Resource/images/menu.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	
	SetBackgroundColor(255, 255, 255);
}

//更新処理
eSceneType TitleScene::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//1番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, TRUE);
	DrawGraph(160, 325, chara_image, TRUE);

	//メニュー画像の描画
	DrawGraph(760, 220, menu_image, TRUE);

	//カーソル画像の描画
	DrawTriangle(730, 250 + menu_cursor * 40, 730, 230 + menu_cursor * 40, 750, 240 + menu_cursor * 40, 0xFFFFFF, FALSE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(chara_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}