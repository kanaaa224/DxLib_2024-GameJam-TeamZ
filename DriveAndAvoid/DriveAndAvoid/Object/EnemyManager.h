#pragma once

#include"Enemy.h"
#include"Player.h"

#define ENEMY_TYPE 3

class EnemyManager
{
private:
	Enemy** enemy;//“G
	int enemy_image[ENEMY_TYPE];

public:
	EnemyManager();
	~EnemyManager();

	void Update(Player* player); // XVˆ—
	void Draw() const;        // •`‰æˆ—
	bool HitEnemy(Collider* collider, bool can_delete);
};
