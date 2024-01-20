#include "ftmesh.h"

namespace ftmesh {


bool FTMeshManager::global_init(int32_t _capacity) {
    if (!_initialized) {
        _global_counter = 0;
        _updates_bitmap = std::make_shared<Bitmap>(_capacity);
        _ptr_to_bit_pos_map = std::make_shared<PtrToPosMap>();
        _bit_pos_to_ptr_map = std::make_shared<PosToPtrMap>();
        _initialized = true;
        return true;
    }
    return false;
}

uint FTMeshManager::register_object(void *any_ptr) {
    if (_initialized) {
        auto uint_addr = reinterpret_cast<uint64_t>(any_ptr);
        ++_global_counter;
        _ptr_to_bit_pos_map->insert_or_assign(uint_addr, _global_counter);
        _bit_pos_to_ptr_map->insert_or_assign(_global_counter, uint_addr);
        return _global_counter;
    }
    return 0;
}

void FTMeshManager::set_update(void *any_ptr) {
    if (_initialized) {
        auto uint_addr = reinterpret_cast<uint64_t>(any_ptr);
        if (_ptr_to_bit_pos_map->contains(uint_addr)) {
            _updates_bitmap->set(_ptr_to_bit_pos_map->at(uint_addr));
        }
    }
}

std::shared_ptr<StringVec> FTMeshManager::export_update() {
    if (_initialized) {
        auto ret = std::make_shared<StringVec>();
        for (auto u = _updates_bitmap->find_first(); u != Bitmap::npos; u = _updates_bitmap->find_next(u)) {
            auto origin_addr = _bit_pos_to_ptr_map->at(u);
            auto serializable_ptr = reinterpret_cast<Serializable*>(origin_addr);
            ret->push_back(serializable_ptr->serialize());
        }
        return ret;
    } else return nullptr;
}

}
