#pragma once

class SuperChat
{
private:
	int image;  //画像用変数
	

public:
	SuperChat(int image);
	~SuperChat();

	void Initialize();  //初期化処理
	void Draw(int num) const;  //描画処理
};