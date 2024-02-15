#include"HelpScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene() : background_image(NULL), titleback_SE(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/help.png");

	//SE�̓ǂݍ���
	titleback_SE = LoadSoundMem("Resource/sounds/backSE.mp3");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(titleback_SE, DX_PLAYTYPE_NORMAL, TRUE);
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);
}

//�I��������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);

	//�ǂݍ���SE�̍폜
	InitSoundMem();
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}