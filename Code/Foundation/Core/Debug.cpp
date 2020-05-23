// ----------------------------------------------------------------------------------------
//  \file       Debug.cpp
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#include <cstdlib>

#include "Precompiled.h"

#include "Core/Debug.h"
#include "IO/Console.h"

void Core::Abort(const char* exp, const char* file, const int line)
{
	IO::Console::Instance().Error(
		"*** ASSERTION ***\n"
		"Expression: %s\n"
		"File: %s\n"
		"Line: %d\n",
		exp, file, line
	);
	abort();
}

void Core::AbortMessage(const char* exp, const char* message, const char* file, const int line)
{
	IO::Console::Instance().Error(
		"*** ASSERTION ***\n"
		"Programmer says: %s\n"
		"Expression: %s\n"
		"File: %s\n"
		"Line: %d\n",
		message, exp, file, line
	);
	abort();
}
