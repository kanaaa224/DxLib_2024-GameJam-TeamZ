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
	DrawGraph(-mileage % 900, 0, back_ground, TRUE);
	DrawGraph(-mileage % 900 + 900, 0, back_ground, TRUE);

	//�R�����g�`��i�_�����ǉ����܂����j
	comment_manager.Draw();

	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	DrawGraph(0, 0, gamemainscene_image, TRUE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(15);
	//DrawFormatString(510, 20, GetColor(0, 0, 0), "�n�C�X�R�A");
	//DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	//DrawFormatString(510, 80, GetColor(0, 0, 0), "��������");
	//for (int i = 0; i < 3; i++)
	//{
	//	DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
	//	DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);

	//}
	//DrawFormatString(510, 200, GetColor(0, 0, 0), "���s����");
	//DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	//DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	//DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpped());

	////�o���A�����̕`��
	//for (int i = 0; i < player->GetBarrierCount(); i++)
	//{
	//	DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	//}

	////�R���Q�[�W�̕`��
	//float fx = 510.0f;
	//float fy = 390.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	////�̗̓Q�[�W�̕`��
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(195, 642, GetColor(0, 0, 0), "%.0f���l", player->GetHp());
	//DrawFormatStringF(280, 577, GetColor(0, 0, 0), "%.0f���l", player->GetSpped());
	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
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