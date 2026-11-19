// include file for standard system include files,
// or project specific include files

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX

// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <D3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <filesystem>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ Libraries
#include <chrono>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// ImGUI
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "ForgeAPI.h"

namespace Forge
{

	struct FVector;
	struct FVector2D;
	struct FRotator;
	struct FTransform;
	struct FColor;

	struct FORGE_API FVector
	{
		float X;
		float Y;
		float Z;

		FVector()
		{
			X = Y = Z = 0.f;
		}

		FVector(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		FVector operator+(const FVector& other) const
		{
			return FVector(
				X + other.X,
				Y + other.Y,
				Z + other.Z
			);
		}

		FVector operator-(const FVector& other) const
		{
			return FVector(
				X - other.X,
				Y - other.Y,
				Z - other.Z
			);
		}

		FVector operator*(float scalar) const
		{
			return FVector(
				X * scalar,
				Y * scalar,
				Z * scalar
			);
		}

		FVector& operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;

			return *this;
		}

		FVector& operator=(const FVector& vector)
		{
			X = vector.X;
			Y = vector.Y;
			Z = vector.Z;

			return *this;
		}

		float Length() const
		{
			return std::sqrt(X * X + Y * Y + Z * Z);
		}

		// Normalize vector
		FVector Normalized() const
		{
			float length = Length();

			if (length <= 0.000001f)
				return FVector(0.0f, 0.0f, 0.0f);

			return FVector(X / length, Y / length, Z / length);
		}

		static float Dot(const FVector& a, const FVector& b)
		{
			return
				a.X * b.X +
				a.Y * b.Y +
				a.Z * b.Z;
		}

		static FVector Cross(const FVector& a, const FVector& b)
		{
			return FVector(
				a.Y * b.Z - a.Z * b.Y,
				a.Z * b.X - a.X * b.Z,
				a.X * b.Y - a.Y * b.X
			);
		}
	};

	struct FORGE_API FVector2D
	{
		float X;
		float Y;

		FVector2D()
		{
			X = Y = 0.f;
		}

		FVector2D(float x, float y)
		{
			X = x;
			Y = y;
		}

		FVector2D operator+(const FVector2D& other) const
		{
			return FVector2D(X + other.X, Y + other.Y);
		}

		FVector2D operator-(const FVector2D& other) const
		{
			return FVector2D(X - other.X, Y - other.Y);
		}

		FVector2D operator*(float scalar) const
		{
			return FVector2D(X * scalar,Y * scalar);
		}

		FVector2D& operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;

			return *this;
		}

		FVector2D& operator=(const FVector2D& vector)
		{
			X = vector.X;
			Y = vector.Y;

			return *this;
		}
	};

	struct FORGE_API FRotator
	{
		float Roll;
		float Pitch;
		float Yaw;

		FRotator()
		{
			Roll = Pitch = Yaw = 0.f;
		}

		FRotator(float roll, float pitch, float yaw)
		{
			Roll = roll;
			Pitch = pitch;
			Yaw = yaw;
		}

		const FRotator& operator=(const FRotator& rotation)
		{
			Roll = rotation.Roll;
			Pitch = rotation.Pitch;
			Yaw = rotation.Yaw;

			return *this;
		}
	};

	struct FORGE_API FTransform
	{
		FVector Position;
		FVector Scale;
		FRotator Rotation;

		FTransform()
		{
			Position = FVector();
			Scale = FVector(1.f, 1.f, 1.f);
			Rotation = FRotator();
		}

		FTransform(FVector position, FVector scale, FRotator rotation)
		{
			Position = position;
			Scale = scale;
			Rotation = rotation;
		}

		FTransform& operator=(const FTransform& transform)
		{
			Position = transform.Position;
			Scale = transform.Scale;
			Rotation = transform.Rotation;

			return *this;
		}
	};

	struct FORGE_API FColor
	{
		float R;
		float G;
		float B;
		float A;

		FColor()
		{
			R = G = B = A = 1.f;
		}

		FColor(float red, float green, float blue, float alpha = 1.f)
		{
			R = red;
			B = blue;
			G = green;
			A = alpha;
		}

		FColor& operator=(const FColor& color)
		{
			R = color.R;
			G = color.G;
			B = color.B;
			A = color.A;

			return *this;
		}
	};

	struct FORGE_API Vertex
	{
		// position
		FVector Position;
		FVector Normal;
		FVector2D TexCoords;
		FColor Color;

		Vertex()
		{
			Position = {};
			Normal = {};
			TexCoords = {};
			Color = {};
		}

		Vertex(const FVector& position, const FVector& normal, const FVector2D& texCoords, const FColor& color)
		{
			Position = position;
			Normal = normal;
			TexCoords = texCoords;
			Color = color;
		}
	};

	namespace Color
	{
		static const FColor Black = FColor(0.f, 0.f, 0.f);
		static const FColor White = FColor(1.f, 1.f, 1.f);
		static const FColor Gray = FColor(0.5f, 0.5f, 0.5f);
		static const FColor Red = FColor(1.f, 0.f, 0.f);
		static const FColor Green = FColor(0.f, 1.f, 0.f);
		static const FColor Blue = FColor(0.f, 0.f, 1.f);
		static const FColor Yellow = FColor(1.f, 1.f, 0.f);
		static const FColor Purple = FColor(1.f, 0.f, 1.f);
		static const FColor Teal = FColor(0.f, 1.f, 1.f);
	}
}

FORGE_API std::wstring ToWideString(const std::string& str);
FORGE_API std::filesystem::path GetExecutableDirectory();
FORGE_API std::filesystem::path GetResourcePath(const std::filesystem::path& relativePath);