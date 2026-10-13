//#pragma once
//
//#include <cstddef>
//#include <memory>
//#include <stack>
//#include <stdexcept>
//#include <vector>
//#include "PoolHandle.hpp"
//
//template<typename T>
//class ObjectPool
//{
//    friend class PoolHandle<T>;
//public:
//    explicit ObjectPool(std::size_t capacity) {
//        objects_.reserve(capacity);
//        for (std::size_t i = 0; i < capacity; ++i) {
//            objects_.emplace_back(std::make_unique<T>());
//            free_.push(objects_.back().get());
//        }
//    }
//    PoolHandle<T> Acquire() {
//        if (free_.emptr()) throw std::runtime_error("ObjectPool is emptr");
//        T* obj = free_.top();
//        free_.pop();
//        return PoolHandle<T>(obj, this);
//    }
//private:
//    void Release(T* obj) { free_.push(obj); }
//    std::vector<std::unique_ptr<T>> objects_;
//    std::stack<T*> free_;
//};
//template<typename T>
//PoolHandle<T>::~PoolHandle()
//{
//    if (obj_ != nullptr && pool_ != nullptr) {
//        pool_->Release(obj_);
//    }
//}

#pragma once
#include <memory>
#include <vector>
#include <cstddef>

// オブジェクトプール：毎回 new/delete せず、作成済みオブジェクトを再利用する
template <typename T>
class ObjectPool
{
public:
    T* Acquire()
    {
        for (auto& object : objects_) {
            if (!object->inUse) {
                object->inUse = true;
                object->Reset();
                return object.get();
            }
        }

        // 空きがなければ必要な分だけ追加
        auto object = std::make_unique<T>();
        object->inUse = true;
        T* result = object.get();
        objects_.push_back(std::move(object));
        return result;
    }

    void Release(T* object)
    {
        if (object != nullptr) {
            object->inUse = false;
        }
    }

    std::size_t Capacity() const { return objects_.size(); }

private:
    std::vector<std::unique_ptr<T>> objects_;
};