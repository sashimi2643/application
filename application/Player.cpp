#include "Player.h"
#include <algorithm>
#include <iostream>

Player::Player(const std::string& name, int maxHp, int attack)
    : name_(name), hp_(maxHp), maxHp_(maxHp), attack_(attack),
    level_(1), exp_(0), nextLevelExp_(10), gold_(0), potions_(3)
{
}

const std::string& Player::GetName() const { return name_; }
int Player::GetHp() const { return hp_; }
int Player::GetMaxHp() const { return maxHp_; }
int Player::GetAttack() const { return attack_; }
int Player::GetLevel() const { return level_; }
int Player::GetExp() const { return exp_; }
int Player::GetGold() const { return gold_; }
int Player::GetPotionCount() const { return potions_; }
bool Player::IsAlive() const { return hp_ > 0; }

void Player::TakeDamage(int damage)
{
    hp_ = std::max(0, hp_ - std::max(0, damage));
}

int Player::AttackDamage() const
{
    return attack_;
}

bool Player::UsePotion()
{
    if (potions_ <= 0 || hp_ == maxHp_) {
        return false;
    }

    --potions_;
    const int before = hp_;
    hp_ = std::min(maxHp_, hp_ + 12);
    std::cout << "ポーションでHPが " << (hp_ - before) << " 回復した！\n";
    return true;
}

void Player::AddReward(int exp, int gold)
{
    exp_ += exp;
    gold_ += gold;
    std::cout << "経験値 +" << exp << " / ゴールド +" << gold << "\n";

    while (exp_ >= nextLevelExp_) {
        exp_ -= nextLevelExp_;
        ++level_;
        nextLevelExp_ += 10;
        maxHp_ += 5;
        attack_ += 2;
        hp_ = maxHp_;
        std::cout << "★ レベルアップ！ Lv." << level_
            << " / 最大HP +5 / 攻撃力 +2 / HP全回復\n";
    }
}

void Player::RestoreForNewGame()
{
    hp_ = maxHp_ = 30;
    attack_ = 6;
    level_ = 1;
    exp_ = 0;
    nextLevelExp_ = 10;
    gold_ = 0;
    potions_ = 3;
}
