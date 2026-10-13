#pragma once
#include <string>
#include <vector>
#include "ObjectPool.h"

// プールから借りるログオブジェクト
struct LogEntry
{
    bool inUse = false;
    std::string text;

    void Reset() { text.clear(); }
};

class CombatLogPool
{
public:
    void Add(const std::string& message);
    void PrintAndClear();
    std::size_t Capacity() const;

private:
    ObjectPool<LogEntry> pool_;
    std::vector<LogEntry*> pending_;
};