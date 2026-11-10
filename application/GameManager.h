#pragma once
#include <memory>
#include "GameState.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "CombatLogPool.h"

// シングルトン：GameManager のインスタンスを1つだけにする
class GameManager
{
public:
    static GameManager& Instance();

    void Run();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

private:
    GameManager();
    void UpdateState();

    void ViewTitle();
    void ControllerTitle();
    void ViewExplore();
    void ControllerExplore();
    void ViewStartBattle();
    void CtrlStartBattle();
    void Battle();
    void ShowClear();
    void ShowGameOver();
    void ShowStatus();
    int ReadChoice(int min, int max);

    GameState state_;
    Player player_;
    EnemyFactory enemyFactory_;
    std::unique_ptr<Enemy> enemy_;
    CombatLogPool combatLog_;
    int defeatedEnemies_;
};