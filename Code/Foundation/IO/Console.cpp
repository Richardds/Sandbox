#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "Console.h"

IO::Console::Console()
{
}

IO::Console::~Console()
{
}

void __cdecl IO::Console::Write(FILE* handle, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(handle, format, args);
    va_end(args);
}

void __cdecl IO::Console::Info(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

void __cdecl IO::Console::Warning(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void __cdecl IO::Console::Error(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
