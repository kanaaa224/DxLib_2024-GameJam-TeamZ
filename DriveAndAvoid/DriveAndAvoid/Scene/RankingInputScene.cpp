#include"RankingInputScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

RankingInputScene::RankingInputScene() :background_image(NULL), ranking(nullptr), score(0), name_num(0), cursor_x(0), cursor_y(0)
{
	memset(name, NULL, (sizeof(char) * 15));
}

RankingInputScene::~RankingInputScene()
{

}

//����������
void RankingInputScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/ranking_background.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/ranking_background.png������܂���\n");
	}

	//�������̓��I�m��
	ranking = new RankingData;
	ranking->Initialize();

	//���U���g�f�[�^���擾����
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%d,\n", &superchats[i]);
		//fscanf_s(fp, "%d\n", &save_superchat[i]);
	}
	
	//�t�@�C���N���[�Y
	fclose(fp);

	score += superchats[0] * 100000;
	score += superchats[1] * 50000;
	score += superchats[2] * 499;
	score += superchats[3] * 999;
	score += superchats[4] * 199;

	SetFontSize(16);
}

//�X�V����
eSceneType RankingInputScene::Update()
{
	bool is_change = false;

	//���O���͏���
	is_change = InputName();

	//�V�[���ύX�͉\���H
	if (is_change)
	{
		//�����L���O�\���ɑJ��
		return eSceneType::E_RANKING_DISP;
	}
	else
	{
		return GetNowScene();
	}
}

//�`�揈��
void RankingInputScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 1280, 720, background_image, TRUE);

	//���O���͎w��������̕`��
	DrawString(150, 100, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	DrawFormatString(100, 220, GetColor(255, 255, 255), ">%s", name);

	//�I��p������`��
	const int font_size = 25;
	for (int i = 0; i < 26; i++)
	{
		int x = (i % 13) * font_size + 15;
		int y = (i / 13) * font_size + 300;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c",'a' + i);
		y = ((i / 13) + 2) * font_size + 300;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'A' + i);
	}
	DrawString(40, 405,"����",GetColor(255, 255, 255));
	DrawString(40 + font_size * 2, 405, "����", GetColor(255, 255, 255));

	//�I�𕶎����t�H�[�J�X����
	if (cursor_y < 4)
	{
		int x = cursor_x * font_size + 10;
		int y = cursor_y * font_size + 295;
		DrawBox(x, y, x + font_size, y + font_size, GetColor(255, 255, 255), FALSE);
	}
	else
	{
		if (cursor_x == 0)
		{
			DrawBox(35, 400, 35 + font_size * 2, 400 + font_size, GetColor(255, 255, 255), FALSE);
		}
		else
		{
			//DrawBox(0, 0, font_size, font_size, GetColor(255, 255, 255), FALSE);
			DrawBox(35 + font_size * 2, 400, 75 + font_size * 2, 400 + font_size, GetColor(255, 255, 255), FALSE);
		}
	}

	DrawFormatString(150, 600, 0xffffff, "�����҂��犪���グ���X�p�`���̍��v�z: ��%d", score);
}

//�I��������
void RankingInputScene::Finalize()
{
	//�����L���O�Ƀf�[�^���i�[
	ranking->SetRankingData(score, name);

	//�ǂݍ��񂾉摜���폜
	DeleteGraph(background_image);

	//���I�������̉��
	delete ranking;
}

//���݂̃V�[�������擾
eSceneType RankingInputScene::GetNowScene() const
{
	return eSceneType::E_RANKING_INPUT;
}

//���O���͏���
bool RankingInputScene::InputName()
{
	//�J�[�\�����쏈��
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (cursor_x > 0)
		{
			cursor_x--;
		}
		else
		{
			cursor_x = 12;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (cursor_x < 12)
		{
			cursor_x++;
		}
		else
		{
			cursor_x = 0;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		if (cursor_y > 0)
		{
			cursor_y--;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (cursor_y < 4)
		{
			cursor_y++;
			if (cursor_y == 4)
			{
				cursor_x = 0;
			}
		}
	}

	//�J�[�\���ʒu�̕��������肷��
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (cursor_y < 2)
		{
			name[name_num++] = 'a' + cursor_x + (cursor_y * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else if (cursor_y < 4)
		{
			name[name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
			if (name_num == 14)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else
		{
			if (cursor_x == 0)
			{
				name[name_num] = '\0';
				return true;
			}
			else
			{
				name[name_num--] = NULL;
			}
		}
	}

	return false;
}