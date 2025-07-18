#pragma once

#include "Math.hpp"

/* ****************************** */
/* BML[BASIC MATH LIBRARY] */
/* ****************************** */

namespace FT {

/* ------------------- VEC2 ------------------- */
    vec2::vec2()
        : vec2(0)
    {
    }
    vec2::vec2(float p_x, float p_y)
    {
        x = p_x;
        y = p_y;
    }
    vec2::vec2(float v)
        : vec2(v, v)
    {
    }
    float& vec2::operator[](int index)
    {
        return data[index];
    }
    const float& vec2::operator[](int index) const
    {
        return data[index];
    }
    bool vec2::operator!=(const vec2 & o)
    {
        return (x != o.x || y != o.y);
    }
    bool vec2::operator==(const vec2 & o)
    {
        return (x == o.x && y == o.y);
    }
    vec2 vec2::operator+(const vec2& o) const
    {
        return (vec2{this->x + o.x, this->y + o.y});
    }
    vec2& vec2::operator+=(const vec2& o)
    {
        this->x += o.x;
        this->y += o.y;
        return (*this);
    }
    vec2& vec2::operator-=(const vec2& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        return (*this);
    }
    vec2 vec2::operator*(const vec2& v) const
    {
        return (vec2{ this->x * v.x, this->y * v.y });
    }
    vec2& vec2::operator*=(const vec2& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return (*this);
    }
    vec2 vec2::operator/(const vec2& v) const
    {
        return (vec2{ this->x / v.x, this->y / v.y });
    }
    vec2& vec2::operator/=(const vec2& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return (*this);
    }
    vec2 vec2::operator*(const float& v) const
    {
        return (vec2{ this->x * v, this->y * v });
    }
    vec2& vec2::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        return (*this);
    }
    vec2 vec2::operator/(const float& v) const
    {
        return (vec2{ this->x / v, this->y / v });
    }
    vec2& vec2::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        return (*this);
    }
    vec2 operator+(const vec2& v1, const vec2& v2)
    {
        return (vec2(v1.x + v2.x, v1.y + v2.y));
    }
    vec2 operator-(const vec2& v1, const vec2& v2)
    {
        return (vec2(v1.x - v2.x, v1.y - v2.y));
    }
    vec2 operator-(const vec2& v)
    {
        return (vec2(-v.x, v.y));
    }
    vec2 operator*(const float& scalar, const vec2& v) {
        return vec2(v.x * scalar, v.y * scalar);
    }
    float vec2::len() const
    {
        return (std::sqrt(this->x*this->x + this->y*this->y));
    }
    float vec2::len2() const
    {
        return (this->x * this->x + this->y * this->y);
    }
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
    vec3::vec3()
        : vec3(0)
    {
    }
    vec3::vec3(ivec3 v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    vec3::vec3(float p_x, float p_y, float p_z)
    {
        x = p_x;
        y = p_y;
        z = p_z;
    }
    vec3::vec3(float v)
        : vec3(v, v, v)
    {
    }
    float& vec3::operator[](int index)
    {
        return data[index];
    }
    const float& vec3::operator[](int index) const
    {
        return data[index];
    }
    bool vec3::operator!=(const vec3 & o)
    {
        return (x != o.x || y != o.y || z != o.z);
    }
    bool vec3::operator==(const vec3 & o)
    {
        return (x == o.x && y == o.y && z == o.z);
    }
    vec3 vec3::operator+(const vec3& o) const
    {
        return (vec3{ this->x + o.x, this->y + o.y, this->z + o.z});
    }
    vec3& vec3::operator+=(const vec3& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        return (*this);
    }
    vec3& vec3::operator-=(const vec3& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        return (*this);
    }
    vec3 vec3::operator*(const vec3& v) const
    {
        return (vec3{ this->x * v.x, this->y * v.y, this->z * v.z });
    }
    vec3& vec3::operator*=(const vec3& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return (*this);
    }
    vec3 vec3::operator/(const vec3& v) const
    {
        return (vec3{ this->x / v.x, this->y / v.y, this->z / v.z });
    }
    vec3& vec3::operator/=(const vec3& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return (*this);
    }
    vec3 vec3::operator*(const float& v) const
    {
        return (vec3{ this->x * v, this->y * v, this->z * v });
    }
    vec3& vec3::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        return (*this);
    }
    vec3 vec3::operator/(const float& v) const
    {
        return (vec3{ this->x / v, this->y / v, this->z / v });
    }
    vec3& vec3::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        this->z /= z;
        return (*this);
    }
    vec3 operator+(const vec3& v1, const vec3& v2)
    {
        return (vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
    }
    vec3 operator-(const vec3& v1, const vec3& v2)
    {
        return (vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
    }
    vec3 operator-(const vec3& v)
    {
        return (vec3(-v.x, -v.y, -v.z));
    }
    vec3 operator*(const float& scalar, const vec3& v) {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }
    float vec3::len() const
    {
        return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
    }
    float vec3::len2() const
    {
        return (this->x * this->x + this->y * this->y + this->z * this->z);
    }
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
    vec4::vec4()
        : vec4(0)
    {
    }
    vec4::vec4(float p_x, float p_y, float p_z, float p_w)
    {
        x = p_x;
        y = p_y;
        z = p_z;
        w = p_w;
    }
    vec4::vec4(float v)
        : vec4(v, v, v, v)
    {
    }
    float& vec4::operator[](int index)
    {
        return data[index];
    }
    const float& vec4::operator[](int index) const
    {
        return data[index];
    }
    bool vec4::operator!=(const vec4 & o)
    {
        return (x != o.x || y != o.y || z != o.z || w != o.w);
    }
    bool vec4::operator==(const vec4 & o)
    {
        return (x == o.x && y == o.y && z == o.z && w == o.w);
    }
    vec4 vec4::operator+(const vec4& o) const
    {
        return (vec4{ this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w });
    }
    vec4& vec4::operator+=(const vec4& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        this->w += o.w;
        return (*this);
    }
    vec4 vec4::operator-(const vec4& o) const
    {
        return (vec4{ this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w });
    }
    vec4& vec4::operator-=(const vec4& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        this->w -= o.w;
        return (*this);
    }
    vec4 vec4::operator*(const vec4& v) const
    {
        return (vec4{ this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w });
    }
    vec4& vec4::operator*=(const vec4& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return (*this);
    }
    vec4 vec4::operator/(const vec4& v) const
    {
        return (vec4{ this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w });
    }
    vec4& vec4::operator/=(const vec4& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;
        return (*this);
    }
    vec4 vec4::operator*(const float& v) const
    {
        return (vec4{ this->x * v, this->y * v, this->z * v, this->w * v });
    }
    vec4& vec4::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        this->w *= w;
        return (*this);
    }
    vec4 vec4::operator/(const float& v) const
    {
        return (vec4{ this->x / v, this->y / v, this->z / v, this->w / v });
    }
    vec4& vec4::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        this->z /= z;
        this->w /= w;
        return (*this);
    }
    vec4 operator+(const vec4& v1, const vec4& v2)
    {
        return (vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w));
    }
    vec4 operator-(const vec4& v1, const vec4& v2)
    {
        return (vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
    }
    vec4 operator-(const vec4& v)
    {
        return (vec4(-v.x, -v.y, -v.z, -v.w));
    }
    vec4 operator*(const float& scalar, const vec4& v) {
        return vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }
    float vec4::len() const
    {
        return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
    }
    float vec4::len2() const
    {
        return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }
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

/* ------------------- iVEC2 ------------------- */
    ivec2::ivec2()
        : ivec2(0)
    {
    }
    ivec2::ivec2(const vec2& v)
    {
        x = v.x;
        y = v.y;
    }
    ivec2::ivec2(int p_x, int p_y)
    {
        x = p_x;
        y = p_y;
    }
    ivec2::ivec2(int v)
        : ivec2(v, v)
    {
    }
    int& ivec2::operator[](int index)
    {
        return data[index];
    }
    const int& ivec2::operator[](int index) const
    {
        return data[index];
    }
    bool ivec2::operator==(const ivec2& o)
    {
        return (x == o.x && y == o.y);
    }
    bool ivec2::operator!=(const ivec2& o)
    {
        return (x != o.x || y != o.y);
    }
    ivec2 ivec2::operator+(const ivec2& o) const
    {
        return (ivec2{ this->x + o.x, this->y + o.y });
    }
    ivec2& ivec2::operator+=(const ivec2& o)
    {
        this->x += o.x;
        this->y += o.y;
        return (*this);
    }
    ivec2& ivec2::operator-=(const ivec2& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        return (*this);
    }
    ivec2 ivec2::operator*(const ivec2& v) const
    {
        return (ivec2{ this->x * v.x, this->y * v.y });
    }
    ivec2& ivec2::operator*=(const ivec2& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return (*this);
    }
    ivec2 ivec2::operator/(const ivec2& v) const
    {
        return (ivec2{ this->x / v.x, this->y / v.y });
    }
    ivec2& ivec2::operator/=(const ivec2& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return (*this);
    }
    ivec2 ivec2::operator*(const float& v) const
    {
        return (ivec2{ int(this->x * v), int(this->y * v) });
    }
    ivec2& ivec2::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        return (*this);
    }
    ivec2 ivec2::operator/(const float& v) const
    {
        return (ivec2{ int(this->x / v), int(this->y / v) });
    }
    ivec2& ivec2::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        return (*this);
    }
    ivec2 operator+(const ivec2& v1, const ivec2& v2)
    {
        return (ivec2(v1.x + v2.x, v1.y + v2.y));
    }
    ivec2 operator-(const ivec2& v1, const ivec2& v2)
    {
        return (ivec2(v1.x - v2.x, v1.y - v2.y));
    }
    ivec2 operator-(const ivec2& v)
    {
        return (ivec2(-v.x, -v.y));
    }
    ivec2 operator*(const float& scalar, const ivec2& v) {
        return ivec2(v.x * scalar, v.y * scalar);
    }
    float ivec2::len() const
    {
        return (std::sqrt(this->x * this->x + this->y * this->y));
    }
    float ivec2::len2() const
    {
        return (this->x * this->x + this->y * this->y);
    }
    ivec2 dot(const ivec2& v1, const ivec2& v2)
    {
        return (ivec2{ v1.x * v2.x + v1.y * v2.y });
    }
/* -------------------------------------------- */

/* ------------------- iVEC3 ------------------- */
    ivec3::ivec3()
        : ivec3(0)
    {
    }
    ivec3::ivec3(const vec3 & v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    ivec3::ivec3(int p_x, int p_y, int p_z)
    {
        x = p_x;
        y = p_y;
        z = p_z;
    }
    ivec3::ivec3(int v)
        : ivec3(v, v, v)
    {
    }
    int& ivec3::operator[](int index)
    {
        return data[index];
    }
    const int& ivec3::operator[](int index) const
    {
        return data[index];
    }
    bool ivec3::operator==(const ivec3 & o)
    {
        return (x == o.x && y == o.y && z == o.z);
    }
    bool ivec3::operator!=(const ivec3 & o)
    {
        return (x != o.x || y != o.y || z != o.z);
    }
    ivec3 ivec3::operator+(const ivec3& o) const
    {
        return (ivec3{ this->x + o.x, this->y + o.y, this->z + o.z });
    }
    ivec3& ivec3::operator+=(const ivec3& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        return (*this);
    }
    ivec3& ivec3::operator-=(const ivec3& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        return (*this);
    }
    ivec3 ivec3::operator*(const ivec3& v) const
    {
        return (ivec3{ this->x * v.x, this->y * v.y, this->z * v.z });
    }
    ivec3& ivec3::operator*=(const ivec3& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return (*this);
    }
    ivec3 ivec3::operator/(const ivec3& v) const
    {
        return (ivec3{ this->x / v.x, this->y / v.y, this->z / v.z });
    }
    ivec3& ivec3::operator/=(const ivec3& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return (*this);
    }
    ivec3 ivec3::operator*(const float& v) const
    {
        return (ivec3{ int(this->x * v), int(this->y * v), int(this->z * v) });
    }
    ivec3& ivec3::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        return (*this);
    }
    ivec3 ivec3::operator/(const float& v) const
    {
        return (ivec3{ int(this->x / v), int(this->y / v), int(this->z / v) });
    }
    ivec3& ivec3::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        this->z /= z;
        return (*this);
    }
    ivec3 operator+(const ivec3& v1, const ivec3& v2)
    {
        return (ivec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
    }
    ivec3 operator-(const ivec3& v1, const ivec3& v2)
    {
        return (ivec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
    }
    ivec3 operator-(const ivec3& v)
    {
        return (ivec3(-v.x, -v.y, -v.z));
    }
    ivec3 operator*(const float& scalar, const ivec3& v) {
        return ivec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }
    float ivec3::len() const
    {
        return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
    }
    float ivec3::len2() const
    {
        return (this->x * this->x + this->y * this->y + this->z * this->z);
    }
    ivec3 dot(const ivec3& v1, const ivec3& v2)
    {
        return (ivec3{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z });
    }
    ivec3 cross(const ivec3& v1, const ivec3& v2)
    {
        ivec3 ret;

        ret[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
        ret[1] = -(v1[0] * v2[2]) - (v1[2] * v2[0]);
        ret[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
        return (ret / ret.len());
    }
/* -------------------------------------------- */

/* ------------------- iVEC4 ------------------- */
    ivec4::ivec4()
        : ivec4(0)
    {
    }
    ivec4::ivec4(int p_x, int p_y, int p_z, int p_w)
    {
        x = p_x;
        y = p_y;
        z = p_z;
        w = p_w;
    }
    ivec4::ivec4(int v)
        : ivec4(v, v, v, v)
    {
    }
    int& ivec4::operator[](int index)
    {
        return data[index];
    }
    const int& ivec4::operator[](int index) const
    {
        return data[index];
    }
    bool ivec4::operator==(const ivec4& o)
    {
        return (x == o.x && y == o.y && z == o.z && w == o.w);
    }
    bool ivec4::operator!=(const ivec4& o)
    {
        return (x != o.x || y != o.y || z != o.z || w != o.w);
    }
    ivec4 ivec4::operator+(const ivec4& o) const
    {
        return (ivec4{ this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w });
    }
    ivec4& ivec4::operator+=(const ivec4& o)
    {
        this->x += o.x;
        this->y += o.y;
        this->z += o.z;
        this->w += o.w;
        return (*this);
    }
    ivec4& ivec4::operator-=(const ivec4& o)
    {
        this->x -= o.x;
        this->y -= o.y;
        this->z -= o.z;
        this->w -= o.w;
        return (*this);
    }
    ivec4 ivec4::operator*(const ivec4& v) const
    {
        return (ivec4{ this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w});
    }
    ivec4& ivec4::operator*=(const ivec4& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return (*this);
    }
    ivec4 ivec4::operator/(const ivec4& v) const
    {
        return (ivec4{ this->x / v.x, this->y / v.y, this->z / v.z, this->w * v.w});
    }
    ivec4& ivec4::operator/=(const ivec4& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;
        return (*this);
    }
    ivec4 ivec4::operator*(const float& v) const
    {
        return (ivec4{ int(this->x * v), int(this->y * v), int(this->z * v), int(this->w * v) });
    }
    ivec4& ivec4::operator*=(const float& v)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        this->w *= w;
        return (*this);
    }
    ivec4 ivec4::operator/(const float& v) const
    {
        return (ivec4{ int(this->x / v), int(this->y / v), int(this->z / v), int(this->w / v) });
    }
    ivec4& ivec4::operator/=(const float& v)
    {
        this->x /= x;
        this->y /= y;
        this->z /= z;
        this->w /= w;
        return (*this);
    }
    ivec4 operator+(const ivec4& v1, const ivec4& v2)
    {
        return (ivec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w));
    }
    ivec4 operator-(const ivec4& v1, const ivec4& v2)
    {
        return (ivec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
    }
    ivec4 operator-(const ivec4& v)
    {
        return (ivec4(-v.x, -v.y, -v.z, -v.w));
    }
    ivec4 operator*(const float& scalar, const ivec4& v) {
        return ivec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }
    float ivec4::len() const
    {
        return (std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
    }
    float ivec4::len2() const
    {
        return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }
    ivec4 dot(const ivec4& v1, const ivec4& v2)
    {
        return (ivec4{ v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w});
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
    mat2::mat2()
    {
        data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
    }
    mat2::mat2(const mat2 & o)
    {
        memcpy(data, o.data, sizeof(data));
    }
    mat2::mat2(float v)
    {
        data[0] = v; data[1] = 0; data[2] = 0; data[3] = v;
    }
    float& mat2::operator[](int index)
    {
        return data[index];
    }
    const float& mat2::operator[](int index) const
    {
        return data[index];
    }
    vec2 mat2::operator*(const vec2 & v)
    {
        vec2 ret;
        ret[0] = data[0] * v[0] + data[2] * v[1];
        ret[1] = data[1] * v[0] + data[3] * v[1];
        return (ret);
    }
    mat2 mat2::operator*(const mat2& m)
    {
        mat2 ret;
        ret[0] = data[0] * m[0] + data[2] * m[1];
        ret[1] = data[1] * m[0] + data[3] * m[1];
        ret[2] = data[0] * m[2] + data[2] * m[3];
        ret[3] = data[1] * m[2] + data[3] * m[3];
        return (ret);
    }
    mat2 mat2::operator+(const mat2& m)
    {
        mat2 ret;
        ret[0] = data[0] + m[0];
        ret[1] = data[1] + m[1];
        ret[2] = data[2] + m[2];
        ret[3] = data[3] + m[3];
        return (ret);
    }
    mat2 mat2::operator-(const mat2& m)
    {
        mat2 ret;
        ret[0] = data[0] - m[0];
        ret[1] = data[1] - m[1];
        ret[2] = data[2] - m[2];
        ret[3] = data[3] - m[3];
        return (ret);
    }
    mat2& mat2::operator*=(const mat2& v)
    {
        mat2 aux;
        aux = *this * v;
        memcpy(data, aux.data, sizeof(data));
        return (*this);
    }
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
            return ret;
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
    mat3::mat3()
    {
        data[0] = 0; data[3] = 0; data[6] = 0;
        data[1] = 0; data[4] = 0; data[7] = 0;
        data[2] = 0; data[5] = 0; data[8] = 0;
    }
    mat3::mat3(const mat3& o)
    {
        memcpy(data, o.data, sizeof(data));
    }
    mat3::mat3(float v)
    {
        data[0] = v; data[3] = 0; data[6] = 0;
        data[1] = 0; data[4] = v; data[7] = 0;
        data[2] = 0; data[5] = 0; data[8] = v;
    }
    float& mat3::operator[](int index)
    {
        return data[index];
    }
    const float& mat3::operator[](int index) const
    {
        return data[index];
    }
    vec3 mat3::operator*(const vec3& v)
    {
        vec3 ret;
        ret[0] = data[0] * v[0] + data[3] * v[1] + data[6] * v[2];
        ret[1] = data[1] * v[0] + data[4] * v[1] + data[7] * v[2];
        ret[2] = data[2] * v[0] + data[5] * v[1] + data[8] * v[2];
        return (ret);
    }
    mat3 mat3::operator*(const mat3& m)
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
    mat3 mat3::operator+(const mat3& m)
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
    mat3 mat3::operator-(const mat3& m)
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
    mat3& mat3::operator*=(const mat3& v)
    {
        mat3 aux;
        aux = *this * v;
        memcpy(data, aux.data, sizeof(data));
        return (*this);
    }
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
            return ret;
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
        return (ret);
    }
/* -------------------------------------------- */

/* ------------------- mat4 ------------------- */
    mat4::mat4()
    {
        data[0] = 0; data[4] = 0; data[8] = 0; data[12] = 0;
        data[1] = 0; data[5] = 0; data[9] = 0; data[13] = 0;
        data[2] = 0; data[6] = 0; data[10] = 0; data[14] = 0;
        data[3] = 0; data[7] = 0; data[11] = 0; data[15] = 0;
    }
    mat4::mat4(const mat4& o)
    {
        memcpy(data, o.data, sizeof(data));
    }
    mat4::mat4(float v)
    {
        data[0] = v; data[4] = 0; data[8] = 0; data[12] = 0;
        data[1] = 0; data[5] = v; data[9] = 0; data[13] = 0;
        data[2] = 0; data[6] = 0; data[10] = v; data[14] = 0;
        data[3] = 0; data[7] = 0; data[11] = 0; data[15] = v;
    }
    float& mat4::operator[](int index)
    {
        return data[index];
    }
    const float& mat4::operator[](int index) const
    {
        return data[index];
    }
    vec4 mat4::operator*(const vec4& v)
    {
        vec4 ret;
        ret[0] = data[0] * v[0] + data[4] * v[1] + data[8] * v[2] + data[12] * v[3];
        ret[1] = data[1] * v[0] + data[5] * v[1] + data[9] * v[2] + data[13] * v[3];
        ret[2] = data[2] * v[0] + data[6] * v[1] + data[10] * v[2] + data[14] * v[3];
        ret[3] = data[3] * v[0] + data[7] * v[1] + data[11] * v[2] + data[15] * v[3];
        return (ret);
    }
    mat4 mat4::operator*(const mat4& m)
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
    mat4 mat4::operator+(const mat4& m)
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
    mat4 mat4::operator-(const mat4& m)
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
    mat4& mat4::operator*=(const mat4& v)
    {
        mat4 aux;
        aux = *this * v;
        memcpy(data, aux.data, sizeof(data));
        return (*this);
    }
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
        ret[2] = 0;                     ret[6] = 0;                       ret[10] = -2.0f / (far - near); ret[14] = -(far + near) / ((far - near));
        ret[3] = 0;                     ret[7] = 0;                       ret[11] = 0;                    ret[15] = 1.0f;
        
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

    mat4 translate(FT::vec3 v)
    {
        mat4 ret;
        ret[0] = 1; ret[4] = 0; ret[8] = 0;     ret[12] = v.x;
        ret[1] = 0; ret[5] = 1; ret[9] = 0;     ret[13] = v.y;
        ret[2] = 0; ret[6] = 0; ret[10] = 1;    ret[14] = v.z;
        ret[3] = 0; ret[7] = 0; ret[11] = 0;    ret[15] = 1;
        return (ret);
    }

    mat4 scale(FT::vec3 v)
    {
        mat4 ret;
        ret[0] = v.x; ret[4] = 0; ret[8] = 0;     ret[12] = 0;
        ret[1] = 0; ret[5] = v.y; ret[9] = 0;     ret[13] = 0;
        ret[2] = 0; ret[6] = 0; ret[10] = v.z;    ret[14] = 0;
        ret[3] = 0; ret[7] = 0; ret[11] = 0;    ret[15] = 1;
        return (ret);
    }

    mat4 lookat(vec3 pos, vec3 up, vec3 right, vec3 lookat)
    {
        mat4 ret, dir;
        mat4 tras = translate(FT::vec3{ -pos[0], -pos[1], -pos[2] });
        dir[0] = right[0];  dir[4] = right[1];  dir[8] = right[2];      dir[12] = 0;
        dir[1] = up[0];     dir[5] = up[1];     dir[9] = up[2];         dir[13] = 0;
        dir[2] = lookat[0]; dir[6] = lookat[1]; dir[10] = lookat[2];    dir[14] = 0;
        dir[3] = 0;         dir[7] = 0;         dir[11] = 0;            dir[15] = 1;
        ret = dir * tras;
        return (ret);
    }

    mat4 rotate(float angle, vec3 dir)
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

/* ------------------- UTILS ------------------ */
    float clamp(float value, float min, float max)
    {
        if (value < min)
            return (min);
        if (value > max)
            return (max);
        return (value);
    }
    float abs(float value)
    {
        return (std::abs(value));
    }
    int abs(int value)
    {
        return (std::abs(value));
    }
    float round(float value)
    {
        return (std::round(value));
    }
    vec3 round(const vec3 & v)
    {
        return (vec3(std::round(v.x), std::round(v.y), std::round(v.z)));
    }
    int sign(float v)
    {
        if (v < 0)
            return (-1);
        return (1);
    }
    int mod(int value, int base)
    {
        if (value < 0)
            value = base - (FT::abs(value) % base);
        return (value % base);
    }
    float mod(float value, float base)
    {
        while (value >= base)
            value -= base;
        while (value < 0)
            value += base;
        return (value);
    }
    float radians(float deg)
    {
        return (deg * PI / 180.0);
    }
    float sin(float rad)
    {
        return (std::sin(rad));
    }
    float cos(float rad)
    {
        return (std::cos(rad));
    }
}