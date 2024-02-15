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
	DrawGraph(915, 90 + (num * 120), image, TRUE);
}