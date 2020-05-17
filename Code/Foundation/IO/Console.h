#pragma once

#include <string>

#include "../Core/Singleton.h"

namespace IO
{
	class Console
	{
	_Singleton(Console)

	public:
		Console() = default;
		void __cdecl Write(FILE* handle, const char* format, ...);
		void __cdecl Info(const char* format, ...);
		void __cdecl Warning(const char* format, ...);
		void __cdecl Error(const char* format, ...);
	};
}
