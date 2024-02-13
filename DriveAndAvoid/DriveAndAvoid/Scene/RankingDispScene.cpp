#include"RankingDispScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

RankingDispScene::RankingDispScene() :background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

//����������
void RankingDispScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/ranking_background.png");
	ranking_board_image = LoadGraph("Resource/images/ranking_board.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Ranking.bmp������܂���\n");
	}

	//�����L���O�����擾
	ranking = new RankingData;
	ranking->Initialize();
	SetFontSize(30);
}

//�X�V����
eSceneType RankingDispScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void RankingDispScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, TRUE);
	DrawRotaGraph(640, 360, 1, 0, ranking_board_image, TRUE);
	

	
	//�擾���������L���O�f�[�^��`�悷��
	for (int i = 0; i < 10; i++)
	{
		DrawFormatString(500, 184 + i * 49, 0x000000, "%2d %-7s %6d", ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
}

//�I��������
void RankingDispScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(ranking_board_image);

	//���I�������̉��
	ranking->Finalize();
	delete ranking;
}

//���݂̃V�[�������擾
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}