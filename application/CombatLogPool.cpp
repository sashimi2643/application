#include "CombatLogPool.h"
#include <iostream>

void CombatLogPool::Add(const std::string& message)
{
    LogEntry* entry = pool_.Acquire();
    entry->text = message;
    pending_.push_back(entry);
}

void CombatLogPool::PrintAndClear()
{
    for (LogEntry* entry : pending_) {
        std::cout << entry->text << '\n';
        pool_.Release(entry);
    }
    pending_.clear();
}

std::size_t CombatLogPool::Capacity() const
{
    return pool_.Capacity();
}