#include "Debug.h"
void Debug::Assert(bool condition, std::string message)
{
    if (!condition)
    {
        throw message;
    }
}
