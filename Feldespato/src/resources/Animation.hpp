#pragma once

#include <string>
#include <vector>
#include <map>

#include <glm/glm.hpp>

#include "../Bone.hpp"

namespace FT {
    class Animation
    {
    public:
        struct PositionKeyFrame
        {
            glm::vec3 position;
            float time_stamp;
            PositionKeyFrame(glm::vec3 pos, float t_s);
        };
        struct RotationKeyFrame
        {
            glm::quat rotation;
            float time_stamp;
            RotationKeyFrame(glm::quat rot, float t_s);
        };
        struct ScaleKeyFrame
        {
            glm::vec3 scale;
            float time_stamp;
            ScaleKeyFrame(glm::vec3 sc, float t_s);
        };

        struct Channel
        {
            std::vector<PositionKeyFrame>   pos_key;
            std::vector<ScaleKeyFrame>      scale_key;
            std::vector<RotationKeyFrame>   rot_key;

            glm::mat4   InterapolatePosition(float time);
            glm::mat4   InterapolateScale(float time);
            glm::mat4   InterapolateRotation(float time);
            glm::mat4   Interpolate(float time);

            float       GetScaleFactor(float last_time, float next_time, float current_time);
            int         GetRotationIndex(float time);
            int         GetScaleIndex(float time);
            int         GetPositionIndex(float time);
        };
    private:
        std::string                     m_name;
        std::string                     m_node_name;
        float                           m_duration;
        float                           m_ticks_per_second;
        std::map<std::string, Channel>  m_channels; // Channel <--> Bone/Node

    public:
        Animation();
        Animation(const Animation & o)
            : m_name(o.m_name), m_node_name(o.m_node_name), m_duration(o.m_duration),
                m_ticks_per_second(o.m_ticks_per_second), m_channels(o.m_channels)
        {
        }
        Animation & operator=(const Animation & o)
        {
            m_name = o.m_name;
            m_node_name = o.m_node_name;
            m_duration = o.m_duration;
            m_ticks_per_second = o.m_ticks_per_second;
            m_channels = o.m_channels;
            return (*this);
        }

        void        SetName(const std::string & name);
        std::string GetName();
        void        SetDuration(float duration);
        float       GetDuration();
        void        SetTicksPerSecond(float ticks);
        float       SetTicksPerSecond();
        void        AddPositionKeyFrame(glm::vec3 position, float time_stamp, std::string channel);
        void        AddScaleKeyFrame(glm::vec3 scale, float time_stamp, std::string channel);
        void        AddRotationKeyFrame(glm::quat rotation, float time_stamp, std::string channel);
        glm::mat4   GetKeyTransform(std::string channel, float time);
    };
}