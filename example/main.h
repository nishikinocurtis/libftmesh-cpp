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
                  const int& _client_t, std::string&&  _cid, std::string&& _req_path) :
        _parent(parent), _client_type(_client_t), _client_id(std::move(_cid)), _last_request_path(std::move(_req_path)) {}
    std::string serialize() override {
        return "{ \"_client_type\": 1 }";
    }
private:
    ServerSessionState& _parent;
    int _client_type;
    std::string _client_id;
    std::string _last_request_path;
};

FTMESH_STATE_OBJ(ServerSessionState) {
public:
    std::string serialize() override {
        return std::format("server_name: {}", "\"test\"");
    }
private:
    std::string _server_name;
    boost::container::vector<std::shared_ptr<ActiveSession>> _sessions;
};


#endif //LIBFTMESH_CPP_MAIN_H
