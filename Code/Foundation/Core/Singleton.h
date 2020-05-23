// ----------------------------------------------------------------------------------------
//  \file       Singleton.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
//  \brief      Singleton class macro
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

#define _Singleton(Type) \
    public: \
    Type(const Type&) = delete; \
    inline static Type& Instance() { \
        static Type instance; \
        return instance; \
    } \
    private:
