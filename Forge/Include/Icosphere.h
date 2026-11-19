#pragma once
#include "Mesh.h"
#include "framework.h"

namespace Forge
{
    class FORGE_API Icosphere : public Mesh
    {
    public:
        Icosphere(float radius, int subdivisions, bool inverted = false);

        void Generate();
        
        void SetRadius(float radius);
        void SetSubdivisions(int subdivisions);

        float GetRadius() const;
        float GetSubdivisions() const;

    protected:
        float _radius;
        int _subdivisions;
        bool _inverted;

        void CreateBaseIcosahedron(std::vector<FVector>& triangles);
        void Subdivide(std::vector<FVector>& triangles);

        FVector GetMidpoint(const FVector& a, const FVector& b) const;

        void AddTriangle(std::vector<FVector>& output,const FVector& a,const FVector& b,const FVector& c);
        void BuildVertices(const std::vector<FVector>& triangles);

        static FVector2D CalculateSphereUV(const FVector& vertex);
    };
}