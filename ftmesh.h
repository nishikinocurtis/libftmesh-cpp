#pragma once

#ifndef LIBFTMESH_CPP_FTMESH_H
#define LIBFTMESH_CPP_FTMESH_H

#include <boost/dynamic_bitset.hpp>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/container/vector.hpp>
#include <boost/log/trivial.hpp>

namespace ftmesh {

typedef boost::dynamic_bitset<uint64_t> Bitmap;
typedef boost::unordered_flat_map<std::uint64_t, std::size_t> PtrToPosMap;
typedef boost::unordered_flat_map<std::size_t, std::uint64_t> PosToPtrMap;
typedef boost::container::vector<std::string> StringVec;


class Serializable {
public:
    ~Serializable() = default;
    virtual std::string serialize() = 0;
};

class FTMeshManager {
public:
    FTMeshManager(const FTMeshManager&) = delete;
    FTMeshManager& operator=(const FTMeshManager) = delete;

    /**
     * ftmesh_global_init
     * @param _capacity int32_t - initial capacity of the bitmap.
     * @return bool - whether the initialization succeeds.
    **/
    static bool global_init(int32_t _capacity = 16384);

    /**
     * set_update
     * @param any_ptr void* - any address that need to be marked.
     */
    static void set_update(void* any_ptr);

    /**
     *  export_update
     */
    static std::shared_ptr<StringVec> export_update();

private:
    static std::shared_ptr<Bitmap> _updates_bitmap;
    static std::shared_ptr<PtrToPosMap> _ptr_to_bit_pos_map;
    static std::shared_ptr<PosToPtrMap> _bit_pos_to_ptr_map;
    static bool _initialized;

    FTMeshManager() = default;
};

#define FTMESH_MGR_INIT(X) \
    { FTMeshManager::global_init(X); }

#define FTMESH_WRITE_SMART_PTR(X) \
    {                                \
        FTMeshManager::set_update(static_cast<void*>(X.get())); \
    }

#define FTMESH_WRITE_PLAIN_PTR(X) \
    {                             \
        FTMeshManager::set_update(static_cast<void*>(X));  \
    }

#define FTMESH_EXPORT_UPDATE FTMeshManager::export_update()

}

#endif //LIBFTMESH_CPP_FTMESH_H
