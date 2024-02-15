#include"TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0),cursor_moveSE(NULL),cursor_selectSE(NULL)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	img_logo = LoadGraph("Resource/images/logo.png");
	chara_image = LoadGraph("Resource/images/title_chara.png");
	background_image = LoadGraph("Resource/images/title_background.png");
	menu_image = LoadGraph("Resource/images/menu.png");

	//SE�̓ǂݍ���
	cursor_moveSE = LoadSoundMem("Resource/sounds/cursormove.mp3");
	cursor_selectSE = LoadSoundMem("Resource/sounds/cursorselect.mp3");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	
	SetBackgroundColor(255, 255, 255);
}

//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//1�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
		PlaySoundMem(cursor_moveSE, DX_PLAYTYPE_BACK, TRUE);
	}

	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
		PlaySoundMem(cursor_moveSE, DX_PLAYTYPE_BACK, TRUE);
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
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

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	// �w�i
	DrawGraph(0, 0, background_image, TRUE);

	// ������
	DrawGraph(160, 325, chara_image, TRUE);

	// ���j���[�摜�̕`��
	DrawGraph(745, 240, menu_image, TRUE);

	// �J�[�\���摜�̕`��
	DrawTriangle(720 + menu_cursor * 20, 265 + menu_cursor * 40, 720 + menu_cursor * 20, 245 + menu_cursor * 40, 740 + menu_cursor * 20, 255 + menu_cursor * 40, 0xFFFFFF, FALSE);

	// ���S
	DrawRotaGraph(320, 200, 0.7f, 0.0f, img_logo, true);

	// �T�u�^�C�g��
	SetFontSize(18);
	DrawFormatString(320 - (GetDrawFormatStringWidth("�`�X�p�`���̎􂢕ҁ`") / 2), 270, 0x000000, "�`�X�p�`���̎􂢕ҁ`");

	// �R�s�[���C�g
	SetFontSize(16);
	DrawFormatString((1280 / 2) - (GetDrawFormatStringWidth("(c) 2024 KBC Winter GameJam TeamZ.") / 2), 700, 0x000000, "(c) 2024 KBC Winter GameJam TeamZ.");
}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(chara_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);

	//�ǂݍ���SE�̍폜
	InitSoundMem();
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}