#pragma once

class SuperChat
{
private:
	int image;  //�摜�p�ϐ�
	

public:
	SuperChat(int image);
	~SuperChat();

	void Initialize();  //����������
	void Draw(int num) const;  //�`�揈��
};