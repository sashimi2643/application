//#include <iostream>
//#include "Player.h"
//#include "EnemyFactory.h"
//#include "Enemy.h"
//
//
//int main()
//{
//	for (int i = 1; i <= 4; i++) {
//		Enemy* enemy = EnemyFactory::CreateEnemy(i);
//
//		printf("%s EXP:%d, Gold:%d, CriticalRate:%f\n", enemy->Data.Name, enemy->Data.EXP, enemy->Data.Gold, enemy->Data.CriticalRate);
//
//		delete enemy;
//	}
//
//
//
//	return 0;
//}

#include <iostream>
#include "GameManager.h"

int main()
{
    // ゲーム管理クラスの唯一のインスタンスからゲームを開始
    GameManager::Instance().Run();

    std::cout << "\nゲーム終了\n";
    return 0;
}