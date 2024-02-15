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

//����������
void ResultScene::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/background.png");
	main_image = LoadGraph("Resource/images/GameMainScene Image.png");
	int result = LoadDivGraph("resource/images/SuperChat.png", 5, 5, 1, 330, 105, image);

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (main_image == -1)
	{
		throw("Resource/images/GameMainScene Image.png������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}

	//�Q�[�����ʂ̓ǂݍ���
	ReadResultData();
}

//�X�V����
eSceneType ResultScene::Update()
{
	//B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawRotaGraph(0, 0,2.0f,0.0, back_ground, TRUE);
	//DrawGraph(0, 0, main_image, TRUE);

	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(230, 100 + (i * 120), 1.0f, 0.0, image[i], TRUE);
		DrawFormatString(260,100+ (i * 120), GetColor(255, 255, 255), "x %4d", save_superchat[i]);
	}
	
}

//�I��������
void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(image[i]);
	}
}

//���݂̃V�[�������擾
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//���U���g�f�[�^�̓ǂݍ���
void ResultScene::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	//���������Ɠ��_���擾
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%d\n", &save_superchat[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}