#pragma once

#include "math/Math.hpp"

#include <glad/glad.h>

constexpr int MAX_BONE_INFLUENCE = 4;
constexpr int MAX_BONES = 100;

namespace FT {
    struct Vertex
    {
        FT::vec3 pos = FT::vec3(0.0);
        FT::vec3 tex_coords = FT::vec3(1.0);
        FT::vec3 normal = FT::vec3(1.0);
        FT::vec4 color = FT::vec4(1.0);
        FT::ivec4 bone_id = FT::ivec4(-1);
        FT::vec4 bone_weight = FT::vec4(0.0);
    };

    struct VertexFormat
    {
        enum AttributeIndex
        {
            POSITION = 0,
            TEX_COORD,
            NORMAL,
            COLOR,
            BONE_ID,
            BONE_WEIGHT,
            MAX_ATTRIBUTES
        };
        unsigned int attribute_count[VertexFormat::AttributeIndex::MAX_ATTRIBUTES];

        static void SetVertexBoneData(Vertex& v, int id, float w)
        {
            for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
            {
                if (v.bone_id[i] < 0)
                {
                    v.bone_id[i] = id;
                    v.bone_weight[i] = w;
                    return;
                }
            }
        }

        static unsigned int GetVertexStride()
        {
            unsigned int stride = 0;
            stride += sizeof(FT::vec3);
            stride += sizeof(FT::vec3);
            stride += sizeof(FT::vec3);
            stride += sizeof(FT::vec4);
            stride += sizeof(int) * MAX_BONE_INFLUENCE;
            stride += sizeof(float) * MAX_BONE_INFLUENCE;
            return (stride);
        }

        static void * GetAttOffset(unsigned int id)
        {
            switch (id)
            {
            case VertexFormat::AttributeIndex::POSITION:
                return ((void *)offsetof(Vertex, pos));
            case VertexFormat::AttributeIndex::TEX_COORD:
                return ((void *)offsetof(Vertex, tex_coords));
            case VertexFormat::AttributeIndex::NORMAL:
                return ((void *)offsetof(Vertex, normal));
            case VertexFormat::AttributeIndex::COLOR:
                return ((void *)offsetof(Vertex, color));
            case VertexFormat::AttributeIndex::BONE_ID:
                return ((void *)offsetof(Vertex, bone_id));
            case VertexFormat::AttributeIndex::BONE_WEIGHT:
                return ((void *)offsetof(Vertex, bone_weight));
            default:
                return ((void *)0);
            }
        }

        static unsigned int GetGLType(unsigned int id)
        {
			if (id == VertexFormat::AttributeIndex::BONE_ID)
				return (GL_INT);
			return (GL_FLOAT);
        }
    };
}