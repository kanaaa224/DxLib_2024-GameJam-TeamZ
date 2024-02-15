#include"EndScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"


EndScene::EndScene() : count(0), back_ground_image(NULL)
{
	
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
	DrawGraph(0, 0, back_ground_image, FALSE);
	DrawFormatString(0, 0, 0xffffff, "%d", count);
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