#include"DxLib.h"
#include"Object/SuperChat.h"


SuperChat::SuperChat(int image):image(image)
{

}

SuperChat::~SuperChat()
{

}

void SuperChat::Initialize()
{
	
}

void SuperChat::Draw(int num) const
{
	DrawRotaGraph(1080, 150 + (num * 120), 0.95f, 0.0f, image, true);
	//DrawGraph(915, 90 + (num * 120), image, FALSE);
}