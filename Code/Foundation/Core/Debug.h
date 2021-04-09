// ----------------------------------------------------------------------------------------
//  \file       Debug.h
//  \author     Richard Boldi� <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"

namespace Core
{
    EXPORT void Abort(const char*, const char*, int);
    EXPORT void AbortMessage(const char*, const char*, const char*, int);
}

#define _Assert(exp) { if (!(exp)) ::Core::Abort(#exp,__FILE__,__LINE__); }
#define _AssertMessage(exp, msg) { if (!(exp)) ::Core::AbortMessage(#exp,msg,__FILE__,__LINE__); }
