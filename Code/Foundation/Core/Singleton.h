// ----------------------------------------------------------------------------------------
//  \file       Singleton.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Libraries.h"

#define _Singleton(Type) \
    public: \
    Type(const Type&) = delete; \
    inline static Type& Instance() { \
        static Type instance; \
        return instance; \
    } \
    private:
