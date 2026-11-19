#pragma once

#include "framework.h"
#include "Material.h"

namespace Forge
{
	class FORGE_API Mesh
	{
	public:
		Mesh(const FTransform transform = FTransform(), const std::string filename = "");
		Mesh(const std::string filename);

		void LoadFromFile(const std::string filename);

		FTransform GetTransform() const;
		FVector GetPosition() const;
		FVector GetScale() const;
		FRotator GetRotation() const;
		const Material& GetMaterial() const;

		FVector GetForwardVector() const;
		FVector GetRightVector() const;
		FVector GetUpVector() const;

		const std::vector<Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetIndices() const;

		void SetTransform(FTransform transform);
		void SetPosition(FVector position);
		void SetScale(FVector scale);
		void SetRotation(FRotator rotation);
		void SetMaterial(const Material& mat);

		bool HasIndexBuffer() const;

		Microsoft::WRL::ComPtr<ID3D11Buffer> GetVertexBuffer();
		Microsoft::WRL::ComPtr<ID3D11Buffer> GetIndexBuffer();

	protected:
		FTransform Transform;
		
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;

		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;

		Material material;

		void CreateVertexBuffer();
		void CreateIndexBuffer();

		static bool loadOBJ(const std::string& filename, std::vector<Vertex>& outVertices);
		static FVector CalculateFaceNormal(const FVector& a,const FVector& b,const FVector& c);
	};
}