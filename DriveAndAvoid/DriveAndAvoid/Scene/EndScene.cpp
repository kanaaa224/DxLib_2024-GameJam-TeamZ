#include"EndScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"


EndScene::EndScene() : count(0), back_ground_image(NULL)
{
	SetFontSize(50);
}

EndScene::~EndScene()
{

}

//����������
void EndScene::Initialize()
{
	back_ground_image = LoadGraph("Resource/images/title_background.png");
}

//�X�V����
eSceneType EndScene::Update()
{
	count++;

	if (count > 200)
	{
		return eSceneType::END;
	}

	return GetNowScene();
}

//�`�揈��
void EndScene::Draw() const
{
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, back_ground_image, FALSE);
	
	SetDrawBright(255, 255, 255);
	DrawString(510, 100, "�N���W�b�g", 0xffffff);
	DrawString(305, 300, "���؂肵�������@�@�@������", 0xffffff);
	DrawString(265, 400, "���؂肵���C���X�g�@���炷�Ƃ�", 0xffffff);
	DrawString(805, 470, "illustAC", 0xffffff);
	DrawString(805, 540, "illalet", 0xffffff);
}

//�I��������
void EndScene::Finalize()
{
	DeleteGraph(back_ground_image);
}

//���݂̃V�[�������擾
eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}