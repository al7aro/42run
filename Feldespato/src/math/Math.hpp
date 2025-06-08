#pragma once

#include <cstring>
#include <iostream>
#include <cmath>

/* ****************************** */
/* BML[BASIC MATH LIBRARY] */
/* ****************************** */

namespace FT {
    constexpr float PI = 3.1415926;

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

        vec2();
        vec2(float p_x, float p_y);
        vec2(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec2 operator+(const vec2& o) const;
        vec2& operator+=(const vec2& o);
        vec2 operator-(const vec2& o) const;
        vec2& operator-=(const vec2& o);
        vec2 operator*(const vec2& v) const;
        vec2& operator*=(const vec2& v);
        vec2 operator/(const vec2& v) const;
        vec2& operator/=(const vec2& v);
        vec2 operator*(const float& scalar) const;
        vec2& operator*=(const float& scalar);
        vec2 operator/(const float& scalar) const;
        vec2& operator/=(const float& scalar);
        float len() const;
        float len2() const;
    };
    vec2 operator+(const vec2& v1, const vec2& v2);
    vec2 operator-(const vec2& v1, const vec2& v2);
    vec2 operator*(const float& scalar, const vec2& v);
    vec2 dot(const vec2& v1, const vec2& v2);
    vec2 normalize(const vec2& v1);
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

        vec3();
        vec3(float p_x, float p_y, float p_z);
        vec3(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec3 operator+(const vec3& o) const;
        vec3& operator+=(const vec3& o);
        vec3 operator-(const vec3& o) const;
        vec3& operator-=(const vec3& o);
        vec3 operator*(const vec3& v) const;
        vec3& operator*=(const vec3& v);
        vec3 operator/(const vec3& v) const;
        vec3& operator/=(const vec3& v);
        vec3 operator*(const float& scalar) const;
        vec3& operator*=(const float& scalar);
        vec3 operator/(const float& scalar) const;
        vec3& operator/=(const float& scalar);
        float len() const;
        float len2() const;
    };
    vec3 operator+(const vec3& v1, const vec3& v2);
    vec3 operator-(const vec3& v1, const vec3& v2);
    vec3 operator*(const float& scalar, const vec3& v);
    vec3 dot(const vec3& v1, const vec3& v2);
    vec3 cross(const vec3& v1, const vec3& v2);
    vec3 normalize(const vec3& v1);
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

        vec4();
        vec4(float p_x, float p_y, float p_z, float p_w);
        vec4(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec4 operator+(const vec4& o) const;
        vec4& operator+=(const vec4& o);
        vec4 operator-(const vec4& o) const;
        vec4& operator-=(const vec4& o);
        vec4 operator*(const vec4& v) const;
        vec4& operator*=(const vec4& v);
        vec4 operator/(const vec4& v) const;
        vec4& operator/=(const vec4& v);
        vec4 operator*(const float& scalar) const;
        vec4& operator*=(const float& scalar);
        vec4 operator/(const float& scalar) const;
        vec4& operator/=(const float& scalar);
        float len() const;
        float len2() const;
    };
    vec4 operator*(const float& scalar, const vec4& v);
    vec4 operator+(const vec4& v1, const vec4& v2);
    vec4 operator-(const vec4& v1, const vec4& v2);
    vec4 dot(const vec4& v1, const vec4& v2);
    vec4 normalize(const vec4& v1);
/* -------------------------------------------- */

/* ------------------- iVEC3 ------------------- */
    struct ivec3
    {
        union
        {
            struct
            {
                int x;
                int y;
                int z;
            };
            int data[3];
        };

        ivec3();
        ivec3(int p_x, int p_y, int p_z);
        ivec3(int v);
        int& operator[](int index);
        const int& operator[](int index) const;
        ivec3 operator+(const ivec3& o) const;
        ivec3& operator+=(const ivec3& o);
        ivec3 operator-(const ivec3& o) const;
        ivec3& operator-=(const ivec3& o);
        ivec3 operator*(const ivec3& v) const;
        ivec3& operator*=(const ivec3& v);
        ivec3 operator/(const ivec3& v) const;
        ivec3& operator/=(const ivec3& v);
        ivec3 operator*(const float& scalar) const;
        ivec3& operator*=(const float& scalar);
        ivec3 operator/(const float& scalar) const;
        ivec3& operator/=(const float& scalar);
        float len() const;
        float len2() const;
    };
    ivec3 operator+(const ivec3& v1, const ivec3& v2);
    ivec3 operator-(const ivec3& v1, const ivec3& v2);
    ivec3 operator*(const float& scalar, const ivec3& v);
    ivec3 dot(const ivec3& v1, const ivec3& v2);
    ivec3 cross(const ivec3& v1, const ivec3& v2);
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

        mat2();
        mat2(const mat2 & o);
        mat2(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec2 operator*(const vec2& v);
        mat2& operator*=(const mat2& v);
        mat2 operator*(const mat2& m);
        mat2 operator+(const mat2& m);
        mat2 operator-(const mat2& m);
    };
    float determinant(const mat2 & m);
    mat2 inverse(const mat2 & m);
    mat2 transpose(const mat2& m);
/* -------------------------------------------- */

/* ------------------- MAT3 ------------------- */
    struct mat3
    {
        float data[9];

        mat3();
        mat3(const mat3& o);
        mat3(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec3 operator*(const vec3& v);
        mat3& operator*=(const mat3& v);
        mat3 operator*(const mat3& m);
        mat3 operator+(const mat3& m);
        mat3 operator-(const mat3& m);
    };
    float determinant(const mat3& m);
    mat3 inverse(const mat3& m);
    mat3 transpose(const mat3& m);
/* -------------------------------------------- */

/* ------------------- mat4 ------------------- */
    struct mat4
    {
        float data[16];

        mat4();
        mat4(const mat4& o);
        mat4(float v);
        float& operator[](int index);
        const float& operator[](int index) const;
        vec4 operator*(const vec4& v);
        mat4& operator*=(const mat4& v);
        mat4 operator*(const mat4& m);
        mat4 operator+(const mat4& m);
        mat4 operator-(const mat4& m);
    };
    float determinant(const mat4& m);
    mat4 inverse(const mat4& m);
    mat4 transpose(const mat4& m);
/* -------------------------------------------- */

/* ------------- USEFUL MATRICES -------------- */
    mat4 ortho(float left, float right, float bottom, float top, float near, float far);
    mat4 perspective(float fov, float aspect, float near, float far);
    mat4 translate(FT::vec3 v);
    mat4 scale(FT::vec3 v);
    mat4 lookat(vec3 pos, vec3 up, vec3 right, vec3 lookat);
    mat4 rotate(float angle, vec3 dir);
    mat4 rotateX(float angle);
    mat4 rotateY(float angle);
    mat4 rotateZ(float angle);
/* -------------------------------------------- */
}