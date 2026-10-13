#pragma once
#include <string>

class Player
{
public:
    // コンストラクタ：生成時に能力値を初期化する
    Player(const std::string& name = "冒険者", int maxHp = 30, int attack = 6);

    const std::string& GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetAttack() const;
    int GetLevel() const;
    int GetExp() const;
    int GetGold() const;
    int GetPotionCount() const;
    bool IsAlive() const;

    void TakeDamage(int damage);
    int AttackDamage() const;
    bool UsePotion();
    void AddReward(int exp, int gold);
    void RestoreForNewGame();

private:
    std::string name_;
    int hp_;
    int maxHp_;
    int attack_;
    int level_;
    int exp_;
    int nextLevelExp_;
    int gold_;
    int potions_;
};