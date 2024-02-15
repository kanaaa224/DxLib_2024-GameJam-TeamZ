#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0),cursor_moveSE(NULL),cursor_selectSE(NULL)
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
	menu_image = LoadGraph("Resource/images/menu.png");

	//SEの読み込み
	cursor_moveSE = LoadSoundMem("Resource/sounds/cursormove.mp3");
	cursor_selectSE = LoadSoundMem("Resource/sounds/cursorselect.mp3");

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
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
		PlaySoundMem(cursor_moveSE, DX_PLAYTYPE_BACK, TRUE);
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
		PlaySoundMem(cursor_moveSE, DX_PLAYTYPE_BACK, TRUE);
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(cursor_selectSE, DX_PLAYTYPE_NORMAL, TRUE);
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_MAIN;
		case 1:
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
	DrawGraph(745, 240, menu_image, TRUE);

	//カーソル画像の描画
	DrawTriangle(720 + menu_cursor * 20, 265 + menu_cursor * 40, 720 + menu_cursor * 20, 245 + menu_cursor * 40, 740 + menu_cursor * 20, 255 + menu_cursor * 40, 0xFFFFFF, FALSE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(chara_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

	//読み込んだSEの削除
	InitSoundMem();
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}