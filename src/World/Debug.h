#pragma once

#include <string>
/* Assertion creates readable conditions with less lines */
class Debug
{
    public:
    static void Assert(bool condition, std::string message);
};