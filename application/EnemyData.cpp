#include "EnemyData.h"

const std::vector<EnemyData>& GetEnemyDataTable()
{
    // index 0～2 を敵IDとして使う
    static const std::vector<EnemyData> table = {
        //　名前、HP、ダメージ、経験値、ゴールド
        {"スライム", 12, 3, 5, 3},
        {"ゴブリン", 20, 5, 8, 6},
        {"オオカミ", 16, 7, 7, 5}
    };
    return table;
}