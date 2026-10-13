#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(const EnemyData& data)
    : name_(data.name), hp_(data.maxHp), maxHp_(data.maxHp),
    attack_(data.attack), expReward_(data.expReward), goldReward_(data.goldReward)
{
}

const std::string& Enemy::GetName() const { return name_; }
int Enemy::GetHp() const { return hp_; }
int Enemy::GetMaxHp() const { return maxHp_; }
int Enemy::GetAttack() const { return attack_; }
int Enemy::GetExpReward() const { return expReward_; }
int Enemy::GetGoldReward() const { return goldReward_; }
bool Enemy::IsAlive() const { return hp_ > 0; }

void Enemy::TakeDamage(int damage)
{
    hp_ = std::max(0, hp_ - std::max(0, damage));
}