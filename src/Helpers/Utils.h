#pragma once
/* Class to store utilities function (usually methods that C++17 implemented but we can't use it yet) */
template <typename T>
T Clamp(const T& n, const T& lower, const T& upper)
{
    return std::max(lower, std::min(n, upper));
}