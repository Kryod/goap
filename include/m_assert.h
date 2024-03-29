#pragma once

#include <iostream>

#define M_ASSERT(condition, message)                                       \
    if (!(condition)) {                                                    \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__   \
                  << " line " << __LINE__ << ": " << message << std::endl; \
        std::terminate();                                                  \
    }
