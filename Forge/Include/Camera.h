#pragma once
#include "framework.h"

namespace Forge
{
	class FORGE_API Camera
	{
	public:
		Camera(FVector pos=FVector(), FRotator rot=FRotator(), float fov=90.f);

		FVector GetPosition() const;
		FRotator GetRotation() const;
		float GetFOV() const;
		FVector GetForwardVector() const;
		FVector GetRightVector() const;
		FVector GetUpVector() const;
		float GetOrbitDistance() const;

		void SetPosition(FVector pos);
		void SetRotation(FRotator rot);
		void SetFOV(float fov);
		void Orbit(int deltaX, int deltaY);
		void Zoom(int amount);
		
		void LookAt(const FVector& target);

		void SetOrbitTarget(bool enable);
		void SetOrbitTargetPosition(const FVector& position);

	private:
		FVector _position;
		FRotator _rotation;
		float _FOV;

		bool _shouldOrbitTarget;
		FVector _orbitTargetPosition;

		float _orbitDistance;

		void UpdateOrbitPosition();
	};
}
