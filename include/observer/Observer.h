#pragma once

#include <string>
#include <iostream>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const std::string& event) = 0;
};

