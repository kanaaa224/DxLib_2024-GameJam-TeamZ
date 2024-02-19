#pragma once

#include"Enemy.h"
#include"Player.h"

#define ENEMY_TYPE 3

class EnemyManager
{
private:
	Enemy** enemy;//敵
	int enemy_image[ENEMY_TYPE];

public:
	EnemyManager();
	~EnemyManager();

	void Update(Player* player); // 更新処理
	void Draw() const;        // 描画処理
	bool HitEnemy(Collider* collider, bool can_delete);
};
