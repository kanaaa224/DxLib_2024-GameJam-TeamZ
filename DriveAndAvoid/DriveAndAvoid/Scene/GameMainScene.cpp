#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), mileage(0), player(nullptr)
{
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/background.png");
	gamemainscene_image = LoadGraph("Resource/images/GameMainScene Image.png");
	LoadGraph("Resource/images/barrier.png");

	player = new Player();
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	mileage++;

	//�R�����g�Ǘ��i�_�����ǉ����܂����j
	comment_manager.Update(player);

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(-mileage % 1280, 0, back_ground, TRUE);
	DrawGraph(-mileage % 1280 + 1280, 0, back_ground, TRUE);

	//�v���C���[�̕`��
	player->Draw();

	//�R�����g�`��i�_�����ǉ����܂����j
	comment_manager.Draw();

}

//�I��������
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	
	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���ł���\n");
	}

	//�X�R�A�ۑ�
	fprintf(fp, "%d,\n", score);

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	delete player;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}