#pragma once

#include <cstring>
#include <iostream>
#include <cmath>

/* ****************************** */
/* UBML[ULTRA BASIC MATH LIBRARY] */
/* ****************************** */

namespace FT {

/* ------------------- VEC2 ------------------- */
    struct vec2
    {
        union
        {
            struct
            {
                float x;
                float y;
            };
            float data[2];
        };

        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec2 operator+(const vec2& o) const
        {
            return (vec2{this->x + o.x, this->y + o.y});
        }
        vec2& operator+=(const vec2& o)
        {
            this->x += o.x;
            this->y += o.y;
            return (*this);
        }
        vec2 operator-(const vec2& o) const
        {
            return (vec2{ this->x - o.x, this->y - o.y });
        }
        vec2& operator-=(const vec2& o)
        {
            this->x -= o.x;
            this->y -= o.y;
            return (*this);
        }
        vec2 operator*(const vec2& v) const
        {
            return (vec2{ this->x * v.x, this->y * v.y });
        }
        vec2& operator*=(const vec2& v)
        {
            this->x *= v.x;
            this->y *= v.y;
            return (*this);
        }
        vec2 operator/(const vec2& v) const
        {
            return (vec2{ this->x / v.x, this->y / v.y });
        }
        vec2& operator/=(const vec2& v)
        {
            this->x /= v.x;
            this->y /= v.y;
            return (*this);
        }
        vec2 operator*(const float& v) const
        {
            return (vec2{ this->x * v, this->y * v });
        }
        vec2& operator*=(const float& v)
        {
            this->x *= x;
            this->y *= y;
            return (*this);
        }
        vec2 operator/(const float& v) const
        {
            return (vec2{ this->x / v, this->y / v });
        }
        vec2& operator/=(const float& v)
        {
            this->x /= x;
            this->y /= y;
            return (*this);
        }
        float len() const
        {
            return (std::sqrt(this->x*this->x + this->y*this->y));
        }
        float len2() const
        {
            return (this->x * this->x + this->y * this->y);
        }
    };
    vec2 dot(const vec2& v1, const vec2& v2)
    {
        return (vec2{v1.x * v2.x + v1.y * v2.y});
    }
    vec2 normalize(const vec2& v1)
    {
        vec2 ret = v1 / v1.len();
        return (ret);
    }
/* -------------------------------------------- */

/* ------------------- VEC3 ------------------- */
    struct vec3
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };
            float data[3];
        };

        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec3 operator+(const vec3& o) const
        {
            return (vec3{ this->x + o.x, this->y + o.y, this->z + o.z});
        }
        vec3& operator+=(const vec3& o)
        {
            this->x += o.x;
            this->y += o.y;
            this->z += o.z;
            return (*this);
        }
        vec3 operator-(const vec3& o) const
        {
            return (vec3{ this->x - o.x, this->y - o.y, this->z - o.z });
        }
        vec3& operator-=(const vec3& o)
        {
            this->x -= o.x;
            this->y -= o.y;
            this->z -= o.z;
            return (*this);
        }
        vec3 operator*(const vec3& v) const
        {
            return (vec3{ this->x * v.x, this->y * v.y, this->z * v.z });
        }
        vec3& operator*=(const vec3& v)
        {
            this->x *= v.x;
            this->y *= v.y;
            this->z *= v.z;
            return (*this);
        }
        vec3 operator/(const vec3& v) const
        {
            return (vec3{ this->x / v.x, this->y / v.y, this->z / v.z });
        }
        vec3& operator/=(const vec3& v)
        {
            this->x /= v.x;
            this->y /= v.y;
            this->z /= v.z;
            return (*this);
        }
        vec3 operator*(const float& v) const
        {
            return (vec3{ this->x * v, this->y * v, this->z * v });
        }
        vec3& operator*=(const float& v)
        {
            this->x *= x;
            this->y *= y;
            this->z *= z;
            return (*this);
        }
        vec3 operator/(const float& v) const
        {
            return (vec3{ this->x / v, this->y / v, this->z / v });
        }
        vec3& operator/=(const float& v)
        {
            this->x /= x;
            this->y /= y;
            this->z /= z;
            return (*this);
        }
        float len() const
        {
            return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
        }
        float len2() const
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z);
        }
    };
    vec3 dot(const vec3& v1, const vec3& v2)
    {
        return (vec3{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z });
    }
    vec3 cross(const vec3& v1, const vec3& v2)
    {
        vec3 ret;

        ret[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
        ret[1] = -(v1[0] * v2[2]) - (v1[2] * v2[0]);
        ret[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
        return (ret / ret.len());
    }
    vec3 normalize(const vec3& v1)
    {
        vec3 ret = v1 / v1.len();
        return (ret);
    }
/* -------------------------------------------- */

/* ------------------- VEC4 ------------------- */
    struct vec4
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            float data[4];
        };

        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec4 operator+(const vec4& o) const
        {
            return (vec4{ this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w });
        }
        vec4& operator+=(const vec4& o)
        {
            this->x += o.x;
            this->y += o.y;
            this->z += o.z;
            this->w += o.w;
            return (*this);
        }
        vec4 operator-(const vec4& o) const
        {
            return (vec4{ this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w });
        }
        vec4& operator-=(const vec4& o)
        {
            this->x -= o.x;
            this->y -= o.y;
            this->z -= o.z;
            this->w -= o.w;
            return (*this);
        }
        vec4 operator*(const vec4& v) const
        {
            return (vec4{ this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w });
        }
        vec4& operator*=(const vec4& v)
        {
            this->x *= v.x;
            this->y *= v.y;
            this->z *= v.z;
            this->w *= v.w;
            return (*this);
        }
        vec4 operator/(const vec4& v) const
        {
            return (vec4{ this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w });
        }
        vec4& operator/=(const vec4& v)
        {
            this->x /= v.x;
            this->y /= v.y;
            this->z /= v.z;
            this->w /= v.w;
            return (*this);
        }
        vec4 operator*(const float& v) const
        {
            return (vec4{ this->x * v, this->y * v, this->z * v, this->w * v });
        }
        vec4& operator*=(const float& v)
        {
            this->x *= x;
            this->y *= y;
            this->z *= z;
            this->w *= w;
            return (*this);
        }
        vec4 operator/(const float& v) const
        {
            return (vec4{ this->x / v, this->y / v, this->z / v, this->w / v });
        }
        vec4& operator/=(const float& v)
        {
            this->x /= x;
            this->y /= y;
            this->z /= z;
            this->w /= w;
            return (*this);
        }
        float len() const
        {
            return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
        }
        float len2() const
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
        }
    };
    vec4 dot(const vec4& v1, const vec4& v2)
    {
        return (vec4{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w });
    }
    vec4 normalize(const vec4& v1)
    {
        vec4 ret = v1 / v1.len();
        return (ret);
    }
/* -------------------------------------------- */

    /* OPENGL USES COLUMN MAJOR ORDER */
    /* Consecutive elements are colums */
    /*******************************************/
    /*           [ m0 m4 m8 m12 ]              */
    /*           [ m1 m5 m9 m13 ]              */
    /*           [ m2 m6 m10 m14 ]             */
    /*           [ m3 m7 m11 m15 ]             */
    /*******************************************/

/* ------------------- MAT2 ------------------- */
    struct mat2
    {
        float data[4];

        mat2()
        {
            data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
        }
        mat2(const mat2 & o)
        {
            memcpy(data, o.data, sizeof(data));
        }
        mat2(float v)
        {
            data[0] = v; data[1] = 0; data[2] = 0; data[3] = v;
        }
        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec2 operator*(const vec2 & v)
        {
            vec2 ret;
            ret[0] = data[0] * v[0] + data[2] * v[1];
            ret[1] = data[1] * v[0] + data[3] * v[1];
            return (ret);
        }
        mat2 operator*(const mat2& m)
        {
            mat2 ret;
            ret[0] = data[0] * m[0] + data[2] * m[1];
            ret[1] = data[1] * m[0] + data[3] * m[1];
            ret[2] = data[0] * m[2] + data[2] * m[3];
            ret[3] = data[1] * m[2] + data[3] * m[3];
            return (ret);
        }
        mat2 operator+(const mat2& m)
        {
            mat2 ret;
            ret[0] = data[0] + m[0];
            ret[1] = data[1] + m[1];
            ret[2] = data[2] + m[2];
            ret[3] = data[3] + m[3];
            return (ret);
        }
        mat2 operator-(const mat2& m)
        {
            mat2 ret;
            ret[0] = data[0] - m[0];
            ret[1] = data[1] - m[1];
            ret[2] = data[2] - m[2];
            ret[3] = data[3] - m[3];
            return (ret);
        }
    };
    float determinant(const mat2 & m)
    {
        return (m[0] * m[3] - m[2] * m[1]);
    }
    mat2 inverse(const mat2 & m)
    {
        mat2 ret;
        float det = m[0] * m[3] - m[2] * m[1];

        if (0 == det)
        {
            ret[0] = 0; ret[1] = 0; ret[2] = 0; ret[3] = 0;
            return;
        }
        ret[0] = m[3] / det;
        ret[1] = -m[1] / det;
        ret[2] = -m[2] / det;
        ret[3] = m[0] / det;
        return (ret);
    }
    mat2 transpose(const mat2& m)
    {
        mat2 ret;
        ret[0] = m[0];  ret[2] = m[1];
        ret[1] = m[2];  ret[3] = m[3];
        return (ret);
    }
/* -------------------------------------------- */

/* ------------------- MAT3 ------------------- */
    struct mat3
    {
        float data[9];

        mat3()
        {
            data[0] = 0; data[3] = 0; data[6] = 0;
            data[1] = 0; data[4] = 0; data[7] = 0;
            data[2] = 0; data[5] = 0; data[8] = 0;
        }
        mat3(const mat3& o)
        {
            memcpy(data, o.data, sizeof(data));
        }
        mat3(float v)
        {
            data[0] = v; data[3] = 0; data[6] = 0;
            data[1] = 0; data[4] = v; data[7] = 0;
            data[2] = 0; data[5] = 0; data[8] = v;
        }
        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec3 operator*(const vec3& v)
        {
            vec3 ret;
            ret[0] = data[0] * v[0] + data[3] * v[1] + data[6] * v[2];
            ret[1] = data[1] * v[0] + data[4] * v[1] + data[7] * v[2];
            ret[2] = data[2] * v[0] + data[5] * v[1] + data[8] * v[2];
            return (ret);
        }
        mat3 operator*(const mat3& m)
        {
            mat3 ret;
            ret[0] = data[0] * m[0] + data[3] * m[1] + data[6] * m[2];
            ret[1] = data[1] * m[0] + data[4] * m[1] + data[7] * m[2];
            ret[2] = data[2] * m[0] + data[5] * m[1] + data[8] * m[2];
            ret[3] = data[0] * m[3] + data[3] * m[4] + data[6] * m[5];
            ret[4] = data[1] * m[3] + data[4] * m[4] + data[7] * m[5];
            ret[5] = data[2] * m[3] + data[5] * m[4] + data[8] * m[5];
            ret[6] = data[0] * m[6] + data[3] * m[7] + data[6] * m[8];
            ret[7] = data[1] * m[6] + data[4] * m[7] + data[7] * m[8];
            ret[8] = data[2] * m[6] + data[5] * m[7] + data[8] * m[8];
            return (ret);
        }
        mat3 operator+(const mat3& m)
        {
            mat3 ret;
            ret[0] = data[0] + m[0];
            ret[1] = data[1] + m[1];
            ret[2] = data[2] + m[2];
            ret[3] = data[3] + m[3];
            ret[4] = data[4] + m[4];
            ret[5] = data[5] + m[5];
            ret[6] = data[6] + m[6];
            ret[7] = data[7] + m[7];
            ret[8] = data[8] + m[8];
            return (ret);
        }
        mat3 operator-(const mat3& m)
        {
            mat3 ret;
            ret[0] = data[0] - m[0];
            ret[1] = data[1] - m[1];
            ret[2] = data[2] - m[2];
            ret[3] = data[3] - m[3];
            ret[4] = data[4] - m[4];
            ret[5] = data[5] - m[5];
            ret[6] = data[6] - m[6];
            ret[7] = data[7] - m[7];
            ret[8] = data[8] - m[8];
            return (ret);
        }
    };
    float determinant(const mat3& m)
    {
        return (m[0] * m[4] * m[8] + m[3] * m[7] * m[2] + m[1] * m[5] * m[6]
            - (m[6] * m[4] * m[2] + m[3] * m[1] * m[8] + m[7] * m[5] * m[0]));
    }
    mat3 inverse(const mat3& m)
    {
        mat3 ret;
        float det = m[0] * m[4] * m[8] + m[3] * m[7] * m[2] + m[1] * m[5] * m[6]
            - (m[6] * m[4] * m[2] + m[3] * m[1] * m[8] + m[7] * m[5] * m[0]);

        if (0 == det)
        {
            ret[0] = 0; ret[1] = 0; ret[2] = 0; ret[3] = 0; ret[4] = 0; ret[5] = 0; ret[6] = 0; ret[7] = 0; ret[8] = 0;
            return;
        }
        ret[0] = (m[4] * m[8] - m[7] * m[5]) / det;
        ret[1] = -(m[1] * m[8] - m[7] * m[2]) / det;
        ret[2] = (m[1] * m[5] - m[4] * m[2]) / det;

        ret[3] = -(m[3] * m[8] - m[6] * m[5]) / det;
        ret[4] = (m[0] * m[8] - m[6] * m[2]) / det;
        ret[5] = -(m[0] * m[5] - m[3] * m[2]) / det;

        ret[6] = (m[3] * m[7] - m[6] * m[4]) / det;
        ret[7] = -(m[0] * m[7] - m[6] * m[1]) / det;
        ret[8] = (m[0] * m[4] - m[3] * m[1]) / det;
    }
    mat3 transpose(const mat3& m)
    {
        mat3 ret;
        ret[0] = m[0];  ret[3] = m[1];  ret[6] = m[2];
        ret[1] = m[3];  ret[4] = m[4];  ret[7] = m[5];
        ret[2] = m[6];  ret[5] = m[7];  ret[8] = m[8];
    }
/* -------------------------------------------- */

/* ------------------- mat4 ------------------- */
    struct mat4
    {
        float data[16];

        mat4()
        {
            data[0] = 0; data[4] = 0; data[8] = 0; data[12] = 0;
            data[1] = 0; data[5] = 0; data[9] = 0; data[13] = 0;
            data[2] = 0; data[6] = 0; data[10] = 0; data[14] = 0;
            data[3] = 0; data[7] = 0; data[11] = 0; data[15] = 0;
        }
        mat4(const mat4& o)
        {
            memcpy(data, o.data, sizeof(data));
        }
        mat4(float v)
        {
            data[0] = v; data[4] = 0; data[8] = 0; data[12] = 0;
            data[1] = 0; data[5] = v; data[9] = 0; data[13] = 0;
            data[2] = 0; data[6] = 0; data[10] = v; data[14] = 0;
            data[3] = 0; data[7] = 0; data[11] = 0; data[15] = v;
        }
        float& operator[](int index)
        {
            return data[index];
        }
        const float& operator[](int index) const
        {
            return data[index];
        }
        vec4 operator*(const vec4& v)
        {
            vec4 ret;
            ret[0] = data[0] * v[0] + data[4] * v[1] + data[8] * v[2] + data[12] * v[3];
            ret[1] = data[1] * v[0] + data[5] * v[1] + data[9] * v[2] + data[13] * v[3];
            ret[2] = data[2] * v[0] + data[6] * v[1] + data[10] * v[2] + data[14] * v[3];
            ret[3] = data[3] * v[0] + data[7] * v[1] + data[11] * v[2] + data[15] * v[3];
            return (ret);
        }
        mat4 operator*(const mat4& m)
        {
            mat4 ret;
            ret[0] = data[0] * m[0] + data[4] * m[1] + data[8] * m[2] + data[12] * m[3];
            ret[1] = data[1] * m[0] + data[5] * m[1] + data[9] * m[2] + data[13] * m[3];
            ret[2] = data[2] * m[0] + data[6] * m[1] + data[10] * m[2] + data[14] * m[3];
            ret[3] = data[3] * m[0] + data[7] * m[1] + data[11] * m[2] + data[15] * m[3];
            ret[4] = data[0] * m[4] + data[4] * m[5] + data[8] * m[6] + data[12] * m[7];
            ret[5] = data[1] * m[4] + data[5] * m[5] + data[9] * m[6] + data[13] * m[7];
            ret[6] = data[2] * m[4] + data[6] * m[5] + data[10] * m[6] + data[14] * m[7];
            ret[7] = data[3] * m[4] + data[7] * m[5] + data[11] * m[6] + data[15] * m[7];
            ret[8] = data[0] * m[8] + data[4] * m[9] + data[8] * m[10] + data[12] * m[11];
            ret[9] = data[1] * m[8] + data[5] * m[9] + data[9] * m[10] + data[13] * m[11];
            ret[10] = data[2] * m[8] + data[6] * m[9] + data[10] * m[10] + data[14] * m[11];
            ret[11] = data[3] * m[8] + data[7] * m[9] + data[11] * m[10] + data[15] * m[11];
            ret[12] = data[0] * m[12] + data[4] * m[13] + data[8] * m[14] + data[12] * m[15];
            ret[13] = data[1] * m[12] + data[5] * m[13] + data[9] * m[14] + data[13] * m[15];
            ret[14] = data[2] * m[12] + data[6] * m[13] + data[10] * m[14] + data[14] * m[15];
            ret[15] = data[3] * m[12] + data[7] * m[13] + data[11] * m[14] + data[15] * m[15];
            return (ret);
        }
        mat4 operator+(const mat4& m)
        {
            mat4 ret;
            ret[0] = data[0] + m[0];
            ret[1] = data[1] + m[1];
            ret[2] = data[2] + m[2];
            ret[3] = data[3] + m[3];
            ret[4] = data[4] + m[4];
            ret[5] = data[5] + m[5];
            ret[6] = data[6] + m[6];
            ret[7] = data[7] + m[7];
            ret[8] = data[8] + m[8];
            ret[9] = data[9] + m[9];
            ret[10] = data[10] + m[10];
            ret[11] = data[11] + m[11];
            ret[12] = data[12] + m[12];
            ret[13] = data[13] + m[13];
            ret[14] = data[14] + m[14];
            ret[15] = data[15] + m[15];
            return (ret);
        }
        mat4 operator-(const mat4& m)
        {
            mat4 ret;
            ret[0] = data[0] - m[0];
            ret[1] = data[1] - m[1];
            ret[2] = data[2] - m[2];
            ret[3] = data[3] - m[3];
            ret[4] = data[4] - m[4];
            ret[5] = data[5] - m[5];
            ret[6] = data[6] - m[6];
            ret[7] = data[7] - m[7];
            ret[8] = data[8] - m[8];
            ret[9] = data[9] - m[9];
            ret[10] = data[10] - m[10];
            ret[11] = data[11] - m[11];
            ret[12] = data[12] - m[12];
            ret[13] = data[13] - m[13];
            ret[14] = data[14] - m[14];
            ret[15] = data[15] - m[15];
            return (ret);
        }
    };
    float determinant(const mat4& m)
    {
        return (m[0] * (m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[6] * m[11] * m[13] - (m[13] * m[10] * m[7] + m[9] * m[6] * m[15] + m[14] * m[11] * m[5]))
            - m[4] * (m[1] * m[10] * m[15] + m[9] * m[14] * m[3] + m[2] * m[11] * m[13] - (m[13] * m[10] * m[3] + m[9] * m[2] * m[15] + m[14] * m[11] * m[1]))
            + m[8] * (m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[2] * m[7] * m[13] - (m[13] * m[6] * m[3] + m[5] * m[2] * m[15] + m[14] * m[7] * m[1]))
            - m[12] * (m[1] * m[6] * m[11] + m[5] * m[10] * m[3] + m[2] * m[7] * m[9] - (m[9] * m[6] * m[3] + m[5] * m[2] * m[11] + m[10] * m[7] * m[1])));
    }
    mat4 inverse(const mat4& m)
    {
        mat4 ret;
        float det = m[0] * (m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[6] * m[11] * m[13] - (m[13] * m[10] * m[7] + m[9] * m[6] * m[15] + m[14] * m[11] * m[5]))
            - m[4] * (m[1] * m[10] * m[15] + m[9] * m[14] * m[3] + m[2] * m[11] * m[13] - (m[13] * m[10] * m[3] + m[9] * m[2] * m[15] + m[14] * m[11] * m[1]))
            + m[8] * (m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[2] * m[7] * m[13] - (m[13] * m[6] * m[3] + m[5] * m[2] * m[15] + m[14] * m[7] * m[1]))
            - m[12] * (m[1] * m[6] * m[11] + m[5] * m[10] * m[3] + m[2] * m[7] * m[9] - (m[9] * m[6] * m[3] + m[5] * m[2] * m[11] + m[10] * m[7] * m[1]));

        if (0 == det)
        {
            ret[0] = 0; ret[1] = 0; ret[2] = 0; ret[3] = 0; ret[4] = 0; ret[5] = 0; ret[6] = 0; ret[7] = 0; ret[8] = 0;
            ret[9] = 0; ret[10] = 0; ret[11] = 0; ret[12] = 0; ret[13] = 0; ret[14] = 0; ret[15] = 0;
            return mat4();
        }
        ret[0] = (m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[6] * m[11] * m[13] - (m[13] * m[10] * m[7] + m[9] * m[6] * m[15] + m[14] * m[11] * m[5])) / det;
        ret[4] = -(m[4] * m[10] * m[15] + m[8] * m[14] * m[7] + m[6] * m[11] * m[12] - (m[12] * m[10] * m[7] + m[8] * m[6] * m[15] + m[14] * m[11] * m[4])) / det;
        ret[8] = (m[4] * m[9] * m[15] + m[8] * m[13] * m[7] + m[5] * m[11] * m[12] - (m[12] * m[9] * m[7] + m[8] * m[5] * m[15] + m[13] * m[11] * m[4])) / det;
        ret[12] = -(m[4] * m[9] * m[14] + m[8] * m[13] * m[6] + m[5] * m[10] * m[12] - (m[12] * m[9] * m[6] + m[8] * m[5] * m[14] + m[13] * m[10] * m[4])) / det;

        ret[1] = -(m[1] * m[10] * m[15] + m[9] * m[14] * m[3] + m[2] * m[11] * m[13] - (m[13] * m[10] * m[3] + m[9] * m[2] * m[15] + m[14] * m[11] * m[1])) / det;
        ret[5] = (m[0] * m[10] * m[15] + m[8] * m[14] * m[3] + m[2] * m[11] * m[12] - (m[12] * m[10] * m[3] + m[8] * m[2] * m[15] + m[14] * m[11] * m[0])) / det;
        ret[9] = -(m[0] * m[9] * m[15] + m[8] * m[13] * m[3] + m[1] * m[11] * m[12] - (m[12] * m[9] * m[3] + m[8] * m[1] * m[15] + m[13] * m[11] * m[0])) / det;
        ret[13] = (m[0] * m[6] * m[11] + m[4] * m[10] * m[3] + m[2] * m[7] * m[8] - (m[8] * m[6] * m[3] + m[4] * m[2] * m[11] + m[10] * m[7] * m[0])) / det;

        ret[2] = (m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[2] * m[7] * m[13] - (m[13] * m[6] * m[3] + m[5] * m[2] * m[15] + m[14] * m[7] * m[1])) / det;
        ret[6] = -(m[0] * m[6] * m[15] + m[4] * m[14] * m[3] + m[2] * m[7] * m[12] - (m[12] * m[6] * m[3] + m[4] * m[2] * m[15] + m[14] * m[7] * m[0])) / det;
        ret[10] = (m[0] * m[5] * m[15] + m[4] * m[13] * m[3] + m[1] * m[7] * m[12] - (m[12] * m[5] * m[3] + m[4] * m[1] * m[15] + m[13] * m[7] * m[0])) / det;
        ret[14] = -(m[0] * m[5] * m[14] + m[4] * m[13] * m[2] + m[1] * m[6] * m[12] - (m[12] * m[5] * m[2] + m[4] * m[1] * m[14] + m[13] * m[6] * m[0])) / det;

        ret[3] = -(m[1] * m[6] * m[11] + m[5] * m[10] * m[3] + m[2] * m[7] * m[9] - (m[9] * m[6] * m[3] + m[5] * m[2] * m[11] + m[10] * m[7] * m[1])) / det;
        ret[7] = (m[0] * m[9] * m[14] + m[8] * m[13] * m[2] + m[1] * m[10] * m[12] - (m[12] * m[9] * m[2] + m[8] * m[1] * m[14] + m[13] * m[10] * m[0])) / det;
        ret[11] = -(m[0] * m[5] * m[11] + m[4] * m[9] * m[3] + m[1] * m[7] * m[8] - (m[8] * m[5] * m[3] + m[4] * m[1] * m[11] + m[9] * m[7] * m[0])) / det;
        ret[15] = (m[0] * m[5] * m[10] + m[4] * m[9] * m[2] + m[1] * m[6] * m[8] - (m[8] * m[5] * m[2] + m[4] * m[1] * m[10] + m[9] * m[6] * m[0])) / det;
        return (ret);
    }
    mat4 transpose(const mat4& m)
    {
        mat4 ret;
        ret[0] = m[0];  ret[4] = m[1];  ret[8] = m[2];      ret[12] = m[3];
        ret[1] = m[4];  ret[5] = m[5];  ret[9] = m[6];      ret[13] = m[7];
        ret[2] = m[8];  ret[6] = m[9];  ret[10] = m[10];    ret[14] = m[11];
        ret[3] = m[12]; ret[7] = m[13]; ret[11] = m[14];    ret[15] = m[15];
        return (ret);
    }
/* -------------------------------------------- */

/* ------------- USEFUL MATRICES -------------- */
    mat4 ortho(float left, float right, float bottom, float top, float near, float far)
    {
        mat4 ret;
        ret[0] = 2.0f / (right - left);   ret[4] = 0;                     ret[8] = 0;                     ret[12] = -(right + left) / ((right - left));
        ret[1] = 0;                     ret[5] = 2.0f / (top - bottom);   ret[9] = 0;                     ret[13] = -(top + bottom) / ((top - bottom));
        ret[2] = 0;                     ret[6] = 0;                     ret[10] = 2.0f / (far - near);    ret[14] = -(far + near) / ((far - near));
        ret[3] = 0;                     ret[7] = 0;                     ret[11] = 0;                    ret[15] = 1.0f;
        return (ret);
    }

    mat4 perspective(float fov, float aspect, float near, float far)
    {
        mat4 ret;
        ret[0] = 1.0f / (aspect * (float)tan(fov / 2.0)); ret[4] = 0;                         ret[8] = 0;                             ret[12] = 0;
        ret[1] = 0;                                 ret[5] = 1.0f / ((float)tan(fov / 2));  ret[9] = 0;                             ret[13] = 0;
        ret[2] = 0;                                 ret[6] = 0;                         ret[10] = -(far + near) / (far - near);   ret[14] = -(2.0f * far * near) / (far - near);
        ret[3] = 0;                                 ret[7] = 0;                         ret[11] = -1.0f;                        ret[15] = 0;
        return (ret);
    }

    mat4 translate(float x, float y, float z)
    {
        mat4 ret;
        ret[0] = 1; ret[4] = 0; ret[8] = 0;     ret[12] = x;
        ret[1] = 0; ret[5] = 1; ret[9] = 0;     ret[13] = y;
        ret[2] = 0; ret[6] = 0; ret[10] = 1;    ret[14] = z;
        ret[3] = 0; ret[7] = 0; ret[11] = 0;    ret[15] = 1;
        return (ret);
    }

    mat4 scale(float x, float y, float z)
    {
        mat4 ret;
        ret[0] = x; ret[4] = 0; ret[8] = 0;     ret[12] = 0;
        ret[1] = 0; ret[5] = y; ret[9] = 0;     ret[13] = 0;
        ret[2] = 0; ret[6] = 0; ret[10] = z;    ret[14] = 0;
        ret[3] = 0; ret[7] = 0; ret[11] = 0;    ret[15] = 1;
        return (ret);
    }

    mat4 lookat(vec3 pos, vec3 up, vec3 right, vec3 lookat)
    {
        mat4 ret, dir;
        mat4 tras = translate(-pos[0], -pos[1], -pos[2]);;
        dir[0] = right[0];  dir[4] = right[1];  dir[8] = right[2];      dir[12] = 0;
        dir[1] = up[0];     dir[5] = up[1];     dir[9] = up[2];         dir[13] = 0;
        dir[2] = lookat[0]; dir[6] = lookat[1]; dir[10] = lookat[2];    dir[14] = 0;
        dir[3] = 0;         dir[7] = 0;         dir[11] = 0;            dir[15] = 1;
        ret = dir * tras;
        return (ret);
    }

    mat4 rotate(float angle, vec4 dir)
    {
        mat4 ret;
        float ux = dir[0], uy = dir[1], uz = dir[2];
        float ux2 = ux * ux, uy2 = uy * uy, uz2 = uz * uz;
        float uxuy = ux * uy, uxuz = ux * uz, uyuz = uy * uz;

        ret[0] = (float)(cos(angle) + ux2 * (1.0 - cos(angle))); ret[4] = (float)(uxuy * (1.0 - cos(angle)) - uz * sin(angle)); ret[8] = (float)(uxuz * (1.0 - cos(angle)) + uy * sin(angle)); ret[12] = 0;
        ret[1] = (float)(uxuy * (1.0 - cos(angle)) + uz * sin(angle)); ret[5] = (float)(cos(angle) + uy2 * (1.0 - cos(angle))); ret[9] = (float)(uyuz * (1.0 - cos(angle)) - ux * sin(angle)); ret[13] = 0;
        ret[2] = (float)(uxuz * (1.0 - cos(angle)) - uy * sin(angle)); ret[6] = (float)(uyuz * (1.0 - cos(angle)) + ux * sin(angle)); ret[10] = (float)(cos(angle) + uz2 * (1.0 - cos(angle))); ret[14] = 0;
        ret[3] = 0; ret[7] = 0; ret[11] = 0; ret[15] = 1.0;
        return (ret);
    }

    mat4 rotateX(float angle)
    {
        mat4 ret;
        ret[0] = 1; ret[4] = 0;                 ret[8] = 0;                     ret[12] = 0;
        ret[1] = 0; ret[5] = (float)cos(angle); ret[9] = -(float)sin(angle);    ret[13] = 0;
        ret[2] = 0; ret[6] = (float)sin(angle); ret[10] = (float)cos(angle);    ret[14] = 0;
        ret[3] = 0; ret[7] = 0;                 ret[11] = 0;                    ret[15] = 1;
        return (ret);
    }

    mat4 rotateY(float angle)
    {
        mat4 ret;
        ret[0] = (float)cos(angle); ret[4] = 0; ret[8] = -(float)sin(angle);    ret[12] = 0;
        ret[1] = 0;                 ret[5] = 1; ret[9] = 0;                     ret[13] = 0;
        ret[2] = (float)sin(angle); ret[6] = 0; ret[10] = (float)cos(angle);    ret[14] = 0;
        ret[3] = 0;                 ret[7] = 0; ret[11] = 0;                    ret[15] = 1;
        return (ret);
    }

    mat4 rotateZ(float angle)
    {
        mat4 ret;
        ret[0] = (float)cos(angle); ret[4] = -(float)sin(angle);    ret[8] = 0;     ret[12] = 0;
        ret[1] = (float)sin(angle); ret[5] = (float)cos(angle);     ret[9] = 0;     ret[13] = 0;
        ret[2] = 0;                 ret[6] = 0;                     ret[10] = 1;    ret[14] = 0;
        ret[3] = 0;                 ret[7] = 0;                     ret[11] = 0;    ret[15] = 1;
        return (ret);
    }
/* -------------------------------------------- */
}