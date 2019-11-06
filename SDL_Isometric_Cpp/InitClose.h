#pragma once

namespace IsoEngine
{
	class InitClose
	{
	public:
		static void InitSDL(const char* title);
		static void ShutdownSDL();
	};
}

