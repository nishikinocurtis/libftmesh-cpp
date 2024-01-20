//
// Created by qiutong on 12/7/23.
//

#include "main.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <random>

int main(int argc, char** argv) {
    FTMESH_MGR_INIT(32768);
    auto myState = std::make_unique<ServerSessionState>("test_server");
    FTMESH_REGISTER_SMART_PTR(myState);

    for (auto i = 0; i < 32000; ++i) {
        myState->create_session(i & 1);
    }

    auto random_eng = std::default_random_engine();
    random_eng.seed(std::time(nullptr));

    // std::cerr << "start writing" << std::endl;

    for (auto i = 0; i < 100; ++i) {
        auto pos = random_eng() % 32000;
        // std::cerr << "writing to: " << pos << std::endl;
        auto ptr = myState->_sessions[pos];
        ptr->change_type(i & 1);
        FTMESH_WRITE_SMART_PTR(ptr);
#ifdef BASELINE
        ptr->_flg = true;
#endif
    }

#ifndef BASELINE
    auto start = std::chrono::high_resolution_clock::now();
    auto serial = FTMESH_EXPORT_UPDATE;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

//    std::cerr << "exported." << std::endl;
//    // std::for_each(serial->begin(), serial->end(), [](const std::string& s) -> void { std::cout << s << std::endl;});
//    for (auto s : *serial.get()) {
//        std::cout << s << std::endl;
//    }
#else
    auto start = std::chrono::high_resolution_clock::now();
    auto serial = ftmesh::StringVec();
    for (auto &ss : myState->_sessions) {
        if (ss->_flg) {
            serial.push_back(ss->serialize());
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#endif
    std::cout << duration_ms;

    return 0;
}