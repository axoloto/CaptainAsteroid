#pragma once

#include <cstdint>

namespace AsteroidsCPP
{
	class Game
	{
	public:

		struct KeyState
		{
			enum class Keys : std::uint32_t
			{
				Left = 1 << 0,
				Right = 1 << 1,
				Up = 1 << 2,
				Down = 1 << 3,
				Space = 1 << 4,
			};

			std::uint32_t State;

			inline bool Pressed(Keys key) const
			{
				return (State & (std::uint32_t)key) != 0;
			}
		};

		Game();

		void Update(KeyState state, float deltaTime);
	};
}