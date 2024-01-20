//
// Created by qiutong on 10/2/23.
//

#pragma once

#ifndef LIBFTMESH_CPP_MAIN_H
#define LIBFTMESH_CPP_MAIN_H



#include "../ftmesh.h"

#include <boost/container/vector.hpp>

#include <memory>
#include <format>
#include <utility>

class ServerSessionState;

FTMESH_STATE_OBJ(ActiveSession) {
public:
        ActiveSession(ServerSessionState& parent,
        const int& _client_t) :
        _parent(parent), _client_type(_client_t) {}
        std::string serialize() override {
            return std::format("{{ \"_client_type\": {} }}", _client_type);
        }
        void change_type(const int& typ) {
                _client_type = typ;
        }
        ServerSessionState& _parent;
        int _client_type;

#ifdef BASELINE
        bool _flg;
#endif
};

FTMESH_STATE_OBJ(ServerSessionState) {
public:
        explicit ServerSessionState(const char* _name): _server_name(_name) {}
        std::string serialize() override {
            return std::format("server_name: {}", "\"test\"");
        }
        uint create_session(const int& typ) {
            auto ses = std::make_shared<ActiveSession>(*this, typ);
            _sessions.push_back(ses);
            return FTMESH_REGISTER_SMART_PTR(ses);
        }
        std::string _server_name;
        boost::container::vector<std::shared_ptr<ActiveSession>> _sessions;
};


#endif //LIBFTMESH_CPP_MAIN_H
