#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "Debug.h"
#include "../IO/Console.h"

void _abort(const char* exp, const char* file, int line)
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

void _abort_msg(const char* exp, const char* message, const char* file, int line)
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
