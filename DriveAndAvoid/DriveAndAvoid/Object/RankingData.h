#pragma once

class RankingData
{
private:
	int score[11];  //�X�R�A�f�[�^
	int rank[11]; //�����N�f�[�^
	char name[11][7]; //���O�f�[�^

public:
	RankingData();
	~RankingData();

	void Initialize();  //����������
	void Finalize();  //�I������

public:
	//�����L���O�f�[�^�̐ݒ�
	void SetRankingData(int score, const char* name);
	//�X�R�A�擾����
	int GetScore(int value) const;
	//�����N�擾����
	int GetRank(int value) const;
	//���O�擾����
	const char* GetName(int value) const;

private:
	//�f�[�^����ւ�����
	void SortData();
};