#pragma once

#include <Game/Scene/Actor.h>
#include <Math/Vector.h>

namespace GunnerBoi
{
	class Projectile : public Graphics::Actor
	{
	public:
		explicit Projectile(const std::shared_ptr<Actor>& actor);
		Projectile(const Math::Vector3f& position, float rotation);
		virtual ~Projectile();

		[[nodiscard]] float DistanceToOrigin() const;
		[[nodiscard]] bool OutOfRange() const;

	private:
		Math::Vector3f _origin;
		float _range;
	};
}
