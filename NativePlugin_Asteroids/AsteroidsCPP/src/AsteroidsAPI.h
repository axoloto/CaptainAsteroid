#pragma once

#ifdef _WIN32
#ifdef NOEXPORT
	#define ASTEROID_EXPORT 
#else
	#define ASTEROID_EXPORT __declspec(dllexport)
#endif
#else
    #define ASTEROID_EXPORT
#endif

#include <cstdint>
#include <AsteroidsGame.h>

extern "C"
{
	namespace AsteroidsCPP
	{
		//Sample Functions
		ASTEROID_EXPORT const char* HelloWorld();

		ASTEROID_EXPORT std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b);

		// TODO: Implement Asteroid API here
		ASTEROID_EXPORT void Update(void* gamePtr, AsteroidsCPP::Game::KeyState keyState, float deltaTime)
		{
			static_cast<AsteroidsCPP::Game*>(gamePtr)->Update(keyState, deltaTime);
		}
	}
}
