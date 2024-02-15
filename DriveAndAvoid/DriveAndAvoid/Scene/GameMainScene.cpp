#include"GameMainScene.h"
#include"../Utility/InputControl.h"
#include"../Object/RankingData.h"
#include"DxLib.h"
#include<math.h>



GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), gamemainscene_image(NULL), barrier_image(NULL), mileage(0), player(nullptr), comment(nullptr), commentDatas(nullptr), commentDatas_num(0),isGameover(false), isGameclear(false), disp_hpbar(0),enemy(nullptr), break_count(0),input_delay(0),superchat(nullptr),superchat_count(0),random_num(0),comment_breakSE(NULL), enemy_downSE(NULL), player_damageSE(NULL), changescene_SE(NULL)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		save_superchat[i] = NULL;
	}
	/*for (int i = 0; i < MAX_COMMENT_NUM; i++)
	{
		text[i] = 0;
		color_num[i] = 0xffffff;
	}*/
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	break_count = 0;
	superchat_count = 0;
	input_delay = 0;
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/background.png");
	gamemainscene_image = LoadGraph("Resource/images/stream.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	img_gameoverWindow  = LoadGraph("Resource/images/gameover_window.png");
	img_gameclearWindow = LoadGraph("Resource/images/gameclear_window.png");
	int result = LoadDivGraph("Resource/images/enemy.png", 3, 3, 1, 300, 350, enemy_image);
	LoadDivGraph("resource/images/SuperChat.png", 5, 5, 1, 330, 105, image);

	//SE�̓ǂݍ���
	comment_breakSE = LoadSoundMem("Resource/sounds/commentbreakSE.mp3");
	enemy_downSE = LoadSoundMem("Resource/sounds/enemydownSE.mp3");
	player_damageSE = LoadSoundMem("Resource/sounds/Player_damageSE.mp3");
	changescene_SE = LoadSoundMem("Resource/sounds/backSE.mp3");
	ChangeVolumeSoundMem(150, comment_breakSE);
	ChangeVolumeSoundMem(170, enemy_downSE);
	ChangeVolumeSoundMem(170, player_damageSE);

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
	commentDatas = new CommentData[MAX_COMMENT_NUM];
	
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

	for (int i = commentDatas_num + 1; i < MAX_COMMENT_NUM; i++) {
		commentDatas[i] = commentDatas[GetRand(commentDatas_num)];
		commentDatas_num++;
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
	
	//�X�p�`���̏�����
	superchat = new SuperChat * [5];
	for (int i = 0; i < 5; i++)
	{
		superchat[i] = nullptr;
	}
	

	isGameover  = false;
	isGameclear = false;
}

//�X�V����
eSceneType GameMainScene::Update()
{
	if (player->GetHP() <= 0.0f) isGameover = true; // �v���C���[�̗̑͂�0�����Ȃ�Q�[���I�[�o�[

	if (isGameover || isGameclear && input_delay > 120)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			PlaySoundMem(changescene_SE, DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::E_RESULT; // E_RESULT
		}
	}
	else
	{
		//�v���C���[�̍X�V
		player->Update();

		//�ړ������̍X�V
		mileage++;

		//�G�l�~�[�̏���

		bool can_spawn_enemy = false;
		if (GetRand(100) == 0) can_spawn_enemy = true;

		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->Update();
				if ((enemy[i]->GetLocation().x < -100))   //�G����ʊO�ɏo��Ə���
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
		
		//�G�Ƃ̓����蔻��
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] != nullptr)
			{
				if (player->HitPlayer(enemy[i]->GetLocation(), enemy[i]->GetBoxSize()))  //�v���C���[�ƓG�̓����蔻��
				{
					//if (comment[i]->GetFontColor() == 0x00ffff) {
					//	// ��
					//	player->DecreaseHP(2);
					//}

					player->SetActive(false);
					player->DecreaseHP(-1.0f);
					PlaySoundMem(player_damageSE, DX_PLAYTYPE_BACK, TRUE);

					delete enemy[i];
					enemy[i]=nullptr;
					disp_hpbar = 60;
				}
			}
			if (enemy[i] != nullptr)   
			{
				if (player->HitBullet(enemy[i]->GetLocation(), enemy[i]->GetBoxSize()))    //�e�ƓG�̓����蔻��
				{
					PlaySoundMem(enemy_downSE, DX_PLAYTYPE_BACK, TRUE);
					delete enemy[i];
					enemy[i] = nullptr;
					break_count++;
				}
			}
		}

		// �R�����g�i�G�j�̐����A�X�V�Ɠ����蔻��`�F�b�N
		//if (mileage / 20 % 100 == 0)
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] == nullptr)
			{
				comment[i] = new Comment(commentDatas[i].type, commentDatas[i].font_size, commentDatas[i].font_color, commentDatas[i].comment);
				comment[i]->Initialize();
				//comment_count++;
				break;
			}
		}
		for (int i = 0; i < commentDatas_num; i++)
		{
			if (comment[i] != nullptr) comment[i]->Update(player->GetSpped());

			// ��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if (comment[i] != nullptr)
			{
				if ((comment[i]->GetLocation().x + comment[i]->GetBoxSize().x) <= 0.0f)
				{
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}

			// �ԃR�����g�͂��΂炭���ď���
			if (comment[i] != nullptr)
			{
				if (comment[i]->GetFontColor() == 0xff0000 && (GetRand(300) == 0))
				{
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}

			// �����蔻��̊m�F
			if (comment[i] != nullptr)
			{
				if (player->HitPlayer(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
				{
					if (comment[i]->GetFontColor() == 0x00ffff) {
						// ��
						player->DecreaseHP(2);
					}
					PlaySoundMem(player_damageSE, DX_PLAYTYPE_BACK, TRUE);
					player->SetActive(false);
					player->DecreaseHP(-1.0f);
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					disp_hpbar = 60;
					//comment_count--;
				}
			}

			// �e�q�b�g
			if (comment[i] != nullptr)
			{
				if (player->HitBullet(comment[i]->GetLocation(), comment[i]->GetBoxSize()))
				{
					if (comment[i]->GetFontColor() == 0x00ffff) {
						// ��
						player->DecreaseHP(2);
					}
					PlaySoundMem(comment_breakSE, DX_PLAYTYPE_BACK, TRUE);
					comment[i]->Fialize();
					delete comment[i];
					comment[i] = nullptr;
					//comment_count--;
				}
			}
		}

		// �X�p�`��
		//for (int i = 0; i < commentDatas_num; i++)
		//{
		//	//text[i] = commentDatas[GetRand(commentDatas_num)].comment.c_str();
		//	int k = i;
		//	if (comment[i] != nullptr)
		//	{
		//		if(GetRand(100) == 0)text[i] = commentDatas[i].comment.c_str();
		//	}
		//	else
		//	{
		//		while (comment[k] == nullptr)
		//		{
		//			k++;
		//		}
		//		if (k < MAX_COMMENT_NUM) text[i] = commentDatas[k].comment.c_str();
		//	}
		//}

		//�v���C���[�̗̑͂�0�����Ȃ�A���U���g�ɑJ�ڂ���

		if (disp_hpbar > 0) disp_hpbar--;

		/*if (mileage % 100 == 0)
		{
			for (int i = 0; i < comment_count; i++)
			{
				int k = GetRand(100) + 1;
				if (comment[k] != nullptr)
				{
					text[i] = commentDatas[k].comment.c_str();
					color_num[i] = commentDatas[k].font_color;
				}
				else
				{
					while (comment[k] == nullptr)
					{
						k++;
					}
					text[i] = commentDatas[k].comment.c_str();
					color_num[i] = commentDatas[k].font_color;
				}
			}
		}*/
		if (break_count >= 3)
		{
			random_num = GetRand(4);
			save_superchat[random_num]++;
			superchat[superchat_count] = new SuperChat(image[random_num]);
			superchat_count++;
			player->IncreaseSpeed(1.0f);
			break_count = 0;
		}

		// �l���X�p�`�����ɉ����ăR�����g���𐧌�
		switch (superchat_count) {
		case 0:
			commentDatas_num = 5;
			break;

		case 1:
			commentDatas_num = 10;
			break;

		case 2:
			commentDatas_num = 20;
			break;

		case 3:
			commentDatas_num = 100;
			break;

		case 4:
			commentDatas_num = MAX_COMMENT_NUM - 1;
			break;
		}

		if (superchat_count >= 5)
		{
			isGameclear = true;
			input_delay++;
		}
	}
	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	SetFontSize(14);

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
		DrawBoxAA(HPbar.x, HPbar.y - 30, HPbar.x + 106, HPbar.y - 20, 0xffffff, 0.2f, FALSE);
		for (int i = 0; i < player->GetHP(); i++)
		{
			if(i<=50)
			DrawBoxAA(HPbar.x + (2 + i * 2), HPbar.y - 28, HPbar.x + (4 + i * 2), HPbar.y - 22, 0x00ff00, 1.0f, TRUE);
		}
	}
	DrawExtendGraph(0, 0, 1280, 720, gamemainscene_image, TRUE);
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
	DrawFormatString(260, 628, GetColor(0, 0, 0), "%.1f���l", player->GetHP());
	DrawFormatString(310, 577, GetColor(0, 0, 0), "%.0f���l", player->GetSpped());
	DrawFormatString(270, 645, GetColor(0, 0, 0), "%08d", mileage / 10);
	
	//�X�p�`���̕\��
	for (int i = 0; i < 5; i++)
	{
		if (superchat[i] != nullptr)
		{
			superchat[i]->Draw(i);
		}
	}

	//for (int i = 0; i < comment_count; i++)
	//{
	//	if (140 + (i * 65) <= 600)
	//	{
	//		DrawBox(890, 90 + (i * 65), 1235, 140 + (i * 65), 0x000000, FALSE);
	//		DrawBox(891, 91 + (i * 65), 1234, 139 + (i * 65), color_num[i], TRUE);
	//		DrawFormatString(895, 110 + (i * 65), 0x000000, "%s", text[i]);
	//	}
	//}

	//DrawBoxAA(fx, fy+ 20.0, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	DrawFormatString(0, 0, 0x000000, "%d", commentDatas_num); // �R�����g�f�[�^��

	// �Q�[���I�[�o�[���̃A�J�E���g�������b�Z�[�W
	if (isGameover || isGameclear)
	{
		int screenWidth  = 1280;
		int screenHeight = 720;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, screenWidth, screenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (isGameover)  DrawRotaGraph(screenWidth / 2, screenHeight / 2, 0.9f, 0.0f, img_gameoverWindow, true);
		if (isGameclear) DrawRotaGraph(screenWidth / 2, screenHeight / 2, 0.9f, 0.0f, img_gameclearWindow, true);
	}
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

	
	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d\n", save_superchat[i]);
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
	delete[] commentDatas;
	commentDatas = nullptr;


	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		delete superchat[i];
	}

	InitSoundMem();
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