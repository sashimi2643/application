#pragma once

// 有限状態機械（FSM）で使用するゲーム状態
enum class GameState
{
    Title,
    Explore,
    Battle,
    Clear,
    GameOver,
    Exit
};