#include "GameManager.h"
#include <iostream>
#include <limits>
#include <string>

GameManager::GameManager()
    : state_(GameState::Title), player_("冒険者", 30, 6), defeatedEnemies_(0)
{
}

GameManager& GameManager::Instance()
{
    static GameManager instance;
    return instance;
}

void GameManager::Run()
{
    while (state_ != GameState::Exit) {
        UpdateState();
    }
}

void GameManager::UpdateState()
{
    // 状態ごとに処理を分ける有限状態機械（FSM）
    switch (state_) {
    case GameState::Title:   ControllerTitle();      break;
    case GameState::Explore: ControllerExplore();    break;
    case GameState::Battle:  Battle();       break;
    case GameState::Clear:   ShowClear();    break;
    case GameState::GameOver:ShowGameOver(); break;
    case GameState::Exit:    break;
    }
}

int GameManager::ReadChoice(int min, int max)
{
    int choice;
    while (true) {
        std::cout << "> ";
        if (std::cin >> choice && choice >= min && choice <= max) {
            return choice;
        }

        std::cout << "入力が正しくありません。数字 " << min << "～" << max
            << " を入力してください。\n";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

// タイトルの見せる担当
void GameManager::ViewTitle()
{
    std::cout << "\n==============================\n"
        << "      ダンジョン探索記\n"
        << "==============================\n"
        << "1. はじめから\n"
        << "2. 終了\n";
}
// タイトルの指示の担当
void GameManager::ControllerTitle()
{
    ViewTitle();

    const int choice = ReadChoice(1, 2);

    if (choice == 1) {
        player_.RestoreForNewGame();
        defeatedEnemies_ = 0;
        enemy_.reset();
        state_ = GameState::Explore;
    }
    else {
        state_ = GameState::Exit;
    }
}

// 探索中の見せる担当
void GameManager::ViewExplore()
{
    std::cout << "\n--- 探索中 ---\n"
        << "討伐数: " << defeatedEnemies_ << "/3\n"
        << "1. ダンジョンを探索する\n"
        << "2. ステータスを見る\n"
        << "3. タイトルに戻る\n";
}
// 探索中の指示の担当
void GameManager::ControllerExplore()
{
    ViewExplore();

    const int choice = ReadChoice(1, 3);

    if (choice == 1) {
        CtrlStartBattle();
    }
    else if (choice == 2) {
        ShowStatus();
    }
    else {
        state_ = GameState::Title;
    }
}

// バトル開始画面の見せる担当
void GameManager::ViewStartBattle()
{
    std::cout << "\n！ " << enemy_->GetName() << " が現れた！\n";
}
// バトル開始画面の指示の担当
void GameManager::CtrlStartBattle()
{
    enemy_ = enemyFactory_.CreateRandomEnemy();
    ViewStartBattle();
    state_ = GameState::Battle;
}

void GameManager::Battle()
{
    if (!enemy_) {
        state_ = GameState::Explore;
        return;
    }

    std::cout << "\n[" << player_.GetName() << "] HP "
        << player_.GetHp() << "/" << player_.GetMaxHp()
        << "  Lv." << player_.GetLevel() << "\n";
    std::cout << "[" << enemy_->GetName() << "] HP "
        << enemy_->GetHp() << "/" << enemy_->GetMaxHp() << "\n";
    std::cout << "1. 攻撃  2. ポーション  3. 逃げる\n";

    const int choice = ReadChoice(1, 3);
    bool enemyTurn = true;

    if (choice == 1) {
        const int damage = player_.AttackDamage();
        enemy_->TakeDamage(damage);
        combatLog_.Add(player_.GetName() + "の攻撃！ " +
            std::to_string(damage) + " ダメージ！");
        if (!enemy_->IsAlive()) {
            combatLog_.Add(enemy_->GetName() + "を倒した！");
            combatLog_.PrintAndClear();
            player_.AddReward(enemy_->GetExpReward(), enemy_->GetGoldReward());
            ++defeatedEnemies_;
            enemy_.reset();

            if (defeatedEnemies_ >= 3) {
                state_ = GameState::Clear;
            }
            else {
                state_ = GameState::Explore;
            }
            return;
        }
    }
    else if (choice == 2) {
        if (!player_.UsePotion()) {
            std::cout << "ポーションを使えない！（残数なし、またはHP満タン）\n";
            enemyTurn = false;
        }
    }
    else {
        std::cout << "あなたは戦闘から逃げ出した。\n";
        enemy_.reset();
        state_ = GameState::Explore;
        return;
    }

    if (enemyTurn) {
        const int damage = enemy_->GetAttack();
        player_.TakeDamage(damage);
        combatLog_.Add(enemy_->GetName() + "の攻撃！ " +
            std::to_string(damage) + " ダメージを受けた！");
    }
    combatLog_.PrintAndClear();

    if (!player_.IsAlive()) {
        std::cout << "HPが0になった……\n";
        state_ = GameState::GameOver;
    }
}

void GameManager::ShowStatus()
{
    std::cout << "\n--- ステータス ---\n"
        << "名前: " << player_.GetName() << "\n"
        << "レベル: " << player_.GetLevel() << "\n"
        << "HP: " << player_.GetHp() << "/" << player_.GetMaxHp() << "\n"
        << "攻撃力: " << player_.GetAttack() << "\n"
        << "経験値: " << player_.GetExp() << "\n"
        << "ゴールド: " << player_.GetGold() << "\n"
        << "ポーション: " << player_.GetPotionCount() << "\n"
        << "ログプールの確保数: " << combatLog_.Capacity() << "\n";
}

void GameManager::ShowClear()
{
    std::cout << "\n******************************\n"
        << "       DUNGEON CLEAR!\n"
        << "3体の敵を倒し、探索を達成した！\n"
        << "最終レベル: " << player_.GetLevel() << "\n"
        << "所持ゴールド: " << player_.GetGold() << "\n"
        << "******************************\n"
        << "1. タイトルへ戻る\n"
        << "2. 終了\n";
    const int choice = ReadChoice(1, 2);
    state_ = (choice == 1) ? GameState::Title : GameState::Exit;
}

void GameManager::ShowGameOver()
{
    std::cout << "\n========== GAME OVER ==========\n"
        << "冒険はここで終わってしまった……\n"
        << "1. もう一度挑戦\n"
        << "2. 終了\n";
    const int choice = ReadChoice(1, 2);
    if (choice == 1) {
        player_.RestoreForNewGame();
        defeatedEnemies_ = 0;
        enemy_.reset();
        state_ = GameState::Explore;
    }
    else {
        state_ = GameState::Exit;
    }
}
