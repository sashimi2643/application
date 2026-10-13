//#pragma once
//#include "EnemyData.h"
//
//class Enemy
//{
//public:
//
//	EnemyData Data;
//
//	Enemy(const EnemyData& data)
//		: Data(data)
//	{
//	}
//};

#pragma once
#include "EnemyData.h"

class Enemy
{
public:
    // コンストラクタ：データテーブルの1件から敵を初期化
    explicit Enemy(const EnemyData& data);

    const std::string& GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetAttack() const;
    int GetExpReward() const;
    int GetGoldReward() const;
    bool IsAlive() const;
    void TakeDamage(int damage);

private:
    std::string name_;
    int hp_;
    int maxHp_;
    int attack_;
    int expReward_;
    int goldReward_;
};