#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), barrier_image(NULL), mileage(0), player(nullptr), comment(nullptr), commentDatas(nullptr), commentDatas_num(0), comment_count(0), disp_hpbar(0),enemy(nullptr)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
	for (int i = 0; i < BUFFER; i++)
	{
		text[i] = 0;
	}
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
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/enemy.png", 3, 3, 1, 300, 350, enemy_image);

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (result == -1)
	{
		throw("Resource/images/car.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}

	//�I�u�W�F�N�g�̐���
	player = new Player;

	//�I�u�W�F�N�g�̏�����
	player->Initialize();


	// �R�����g�f�[�^�̏������A�ǂݍ���
	commentDatas = new CommentData[BUFFER];

	FILE* file;
	errno_t file_result = fopen_s(&file, "Resource/dat/comment.csv", "r");

	if (file_result != 0) throw("Resource/dat/comment.csv ���J���܂���ł����B\n");
	if (file == NULL)     throw("Resource/dat/comment.csv ���J���܂���ł����B\n");

	char str[100];
	unsigned int font_color;
	int font_size;
	int type;

	commentDatas_num = -1;

	while (fscanf_s(file, "%[^,],%x,%d,%d\n", str, 100, &font_color, &font_size, &type) == 4) {
		CommentData commentData;
		commentData.comment = str;
		commentData.font_color = font_color;
		commentData.font_size = font_size;
		commentData.type = type;

		commentDatas_num++;
		commentDatas[commentDatas_num] = commentData;
	}
	
	int buffer = commentDatas_num;

	for (int i = 0; i < BUFFER - buffer; i++) {
		commentDatas_num++;
		commentDatas[commentDatas_num] = commentDatas[GetRand(commentDatas_num)];
	}

	fclose(file);


	// �R�����g�̏�����
	comment = new Comment * [commentDatas_num];

	for (int i = 0; i < commentDatas_num; i++)
	{
		comment[i] = nullptr;
	}

	//�G�l�~�[�̏�����
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
}

//�X�V����
eSceneType GameMainScene::Update()
{
	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	mileage++;

	//�G�l�~�[�̏���
	
	bool can_spawn_enemy = false;
	if (GetRand(100) == 0)can_spawn_enemy = true;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update();
			if ((enemy[i]->GetLocation().x < -100) || player->HitBullet(enemy[i]->GetLocation(), enemy[i]->GetBoxSize()))
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
		else if (can_spawn_enemy)
		{
			int type = GetRand(2);
			enemy[i] = new Enemy(enemy_image[type], type);
			can_spawn_enemy = false;
		}
	}


	// �R�����g�i�G�j��������
	//if (mileage / 20 % 100 == 0)
	//{
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] == nullptr)
			{
				comment[i] = new Comment(commentDatas[i].type, commentDatas[i].font_size, commentDatas[i].font_color, commentDatas[i].comment);
				comment[i]->Initialize();
				comment_count++;
				break;
			}
		}
	//}

	// �R�����g�i�G�j�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr)
		{
			comment[i]->Update(player->GetSpped());

			// ��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if ((comment[i]->GetLocation().x + comment[i]->GetBoxSize().x) <= 0.0f)
			{
				enemy_count[comment[i]->GetType()]++;
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
				comment_count--;
			}
		}

		// �����蔻��̊m�F
		if (comment[i] != nullptr)
		{
			if (player->HitPlayer(comment[i]->GetLocation(),comment[i]->GetBoxSize()))
			{
				player->SetActive(false);
				player->DecreaseHP(-5.0f);
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
				disp_hpbar = 60;
				comment_count--;
			}
		}

		if (comment[i] != nullptr)
		{
			if (player->HitBullet(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
			{
				comment[i]->Fialize();
				delete comment[i];
				comment[i] = nullptr;
			}
		}
	}

	// �X�p�`��
	for (int i = 0; i < commentDatas_num; i++)
	{
		//text[i] = commentDatas[GetRand(commentDatas_num)].comment.c_str();
		int k = i;
		if (comment[i] != nullptr)
		{
			text[i] = commentDatas[i].comment.c_str();
		}
		else
		{
			while (comment[k] == nullptr)
			{
				k++;
			}
			if (k < 100) text[i] = commentDatas[k].comment.c_str();
		}
	}

	//�v���C���[�̗̑͂�0�����Ȃ�A���U���g�ɑJ�ڂ���
	if ( player->GetHP() <= 0.0f)
	{
		//return eSceneType::E_RESULT;
	}

	if (disp_hpbar > 0) disp_hpbar--;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(-mileage % 900, 0, back_ground, TRUE);
	DrawGraph(-mileage % 900 + 900, 0, back_ground, TRUE);

	//�Ă��L�����̂Ђ傤��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	// �R�����g�i�G�j�̕`��
	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr) comment[i]->Draw();
	}

	//�v���C���[�̕`��
	player->Draw();

	
	//UI�̕`��
	if (disp_hpbar > 0)
	{
		Vector2D HPbar = player->GetLocation();
		DrawBoxAA(HPbar.x - 50, HPbar.y - 30, HPbar.x + 50, HPbar.y - 20, 0xffffff, 0.2f, FALSE);
		for (int i = 0; i < player->GetHP(); i++)
		{
			DrawBoxAA(HPbar.x - (48 - i * 2), HPbar.y - 28, HPbar.x - (45 - i * 2), HPbar.y - 22, 0x00ff00, 1.0f, TRUE);
		}
	}
	DrawGraph(0, 0, gamemainscene_image, TRUE);
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	//SetFontSize(15);
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
	DrawFormatString(195, 642, GetColor(0, 0, 0), "%.0f���l", player->GetHP());
	DrawFormatString(280, 577, GetColor(0, 0, 0), "%.0f���l", player->GetSpped());
	DrawFormatString(1100, 43, GetColor(0, 0, 0), "%08d", mileage / 10);
	DrawFormatString(10, 5, 0x00ffff, "%d", comment_count);
	for (int i = 0; i < comment_count ; i++)
	{
			if (140 + (i * 65) <= 600)
			{
				DrawBox(890, 90 + (i * 65), 1235, 140 + (i * 65), 0x000000, FALSE);
				DrawBox(891, 91 + (i * 65), 1234, 139 + (i * 65), 0xff2510, TRUE);
				DrawFormatString(890, 110 + (i * 65), 0xffffff, "%s", text[i]);
			}
	}
	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	//DrawFormatString(0, 0, 0x000000, "%d", commentDatas_num); // �R�����g�f�[�^��
}

//�I��������
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

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

	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	//�G�L�����̏���
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;

	// �R�����g�i�G�j�̍폜

	for (int i = 0; i < commentDatas_num; i++)
	{
		if (comment[i] != nullptr)
		{
			comment[i]->Fialize();
			delete comment[i];
			comment[i] = nullptr;
		}
	}

	delete[] comment;

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
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

////�����蔻�菈��(�v���C���[�ƓG)
//bool GameMainScene::IsHitCheck(Player* p, Comment* e)
//{
//	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
//	if (p->IsBarrier())
//	{
//		return false;
//	}
//
//	//�G��񂪖�����΁A�����蔻��𖳎�����
//	if (e == nullptr)
//	{
//		return false;
//	}
//
//	//�ʒu���̍������擾
//	Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//�����蔻��T�C�Y�̑傫���擾
//	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
//	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}

// �����蔻�菈��(�v���C���[�ƓG)
bool GameMainScene::IsHitCheck(Player * p, Comment * e)
{
	//�v���C���[���_�ł��Ă�����A�����蔻��𖳎�����
	if (p->GetActive()==false)
	{
		return false;
	}
	//�G��񂪖�����΁A�����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}
	float sx1 = p->GetLocation().x;
	float sx2 = p->GetLocation().x + p->GetBoxSize().x;
	float sy1 = p->GetLocation().y;
	float sy2 = p->GetLocation().y + p->GetBoxSize().y;
	float dx1 = e->GetLocation().x;
	float dx2 = e->GetLocation().x + e->GetBoxSize().x;
	float dy1 = e->GetLocation().y;
	float dy2 = e->GetLocation().y + e->GetBoxSize().y;
	//��`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return TRUE;
	return FALSE;
}