#include "EnemyFactory.h"
#include "Enemy.h"

const EnemyData EnemyFactory::EnemyTable[] = {
	{1, "Slime", 10, 5, 2, 1, 10, 5, Element::None, 1.30},
	{2, "Goblin", 20, 10, 5, 2, 20, 10, Element::Earth, 1.25},
	{3, "Orc", 30, 15, 8, 3, 30, 15, Element::Fire, 1.20},
	{4, "Dragon", 100, 50, 20, 5, 1000, 1000, Element::Wind, 1.15},
};
const int EnemyFactory::EnemyTableSize = sizeof(EnemyTable) / sizeof(EnemyData);

Enemy* EnemyFactory::CreateEnemy(int ID)
{
	for (int i = 0; i < EnemyTableSize; i++) {
		if (EnemyTable[i].ID == ID) {
			return new Enemy(EnemyTable[i]);
		}
	}

	// ID ‚ªŒ©‚Â‚©‚ç‚È‚©‚Á‚½ê‡‚Í nullptr ‚ð•Ô‚·
	return nullptr;
}