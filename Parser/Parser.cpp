//
// Created by Radio on 10/05/2024.
//

#include "Parser.hpp"

#include <utility>
#include "DB/DbHelper.hpp"

Parser::Parser() {
    DBHelper::getDB();
}

void Parser::commit() {
    DBHelper::commit();
}

void Parser::initialize() {
    DBHelper::getDB();
    DBHelper::loadData();
}

void Parser::setAfterCommitCallback(std::function<void()> callback) {
    DBHelper::afterCommitCallback = std::move(callback);
}

void Parser::setOnUncommitedChangesChangeCallback(std::function<void()> callback) {
    DBHelper::onUncommitedChangesChangeCallback = std::move(callback);
}

std::uint64_t Parser::getUncommitedChanges() {
    return DBHelper::getUncommitedChanges();
}
