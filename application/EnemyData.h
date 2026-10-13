//#pragma once
//#include "Element.h"
//
//struct EnemyData
//{
//	int ID;
//	const char Name[256];
//	int HP;
//	int ATK;
//	int DEF;
//	int SPD;
//	int Gold;
//	int EXP;
//	Element Element;
//	float CriticalRate;
//};

#pragma once
#include <string>
#include <vector>

// データテーブル：敵の設定値をコード本体から分離する
struct EnemyData
{
    std::string name;
    int maxHp;
    int attack;
    int expReward;
    int goldReward;
};

const std::vector<EnemyData>& GetEnemyDataTable();