#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

#define MAX_ENEMY_NUM 20

GameMainScene::GameMainScene() : back_ground_image(NULL), player(nullptr), mileage(0)
{
	
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground_image = LoadGraph("Resource/images/background.png");
	player = new Player();
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�v���C���[�̍X�V
	player->Update();
	//�G�L�����̍X�V
	enemy_manager.Update(player);
	//�R�����g�̍X�V
	comment_manager.Update(player);

	mileage++;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(-mileage % 1280, 0, back_ground_image, TRUE);
	DrawGraph(-mileage % 1280 + 1280, 0, back_ground_image, TRUE);

	//�v���C���[�̕`��
	player->Draw();
	//�G�L�����̍X�V
	enemy_manager.Draw();
	//�R�����g�`��
	comment_manager.Draw();

}

//�I��������
void GameMainScene::Finalize()
{
	//���I�m�ۂ����I�u�W�F�N�g���폜����
	delete player;
}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}