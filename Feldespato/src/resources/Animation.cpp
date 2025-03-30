#include "Animation.hpp"

namespace FT {
    Animation::PositionKeyFrame::PositionKeyFrame(glm::vec3 pos, float t_s)
        : position(pos), time_stamp(t_s)
    {
    }
    Animation::RotationKeyFrame::RotationKeyFrame(glm::quat rot, float t_s)
        : rotation(rot), time_stamp(t_s)
    {
    }
    Animation::ScaleKeyFrame::ScaleKeyFrame(glm::vec3 sc, float t_s)
        : scale(sc), time_stamp(t_s)
    {
    }

    glm::mat4 Animation::Channel::InterapolatePosition(float time)
    {
        glm::mat4 position = 1.0;
        if (pos_key.size() == 1)
            return (glm::translate(glm::mat4(1.0), pos_key[0].position));
        int p0 = GetPositionIndex(time);
        int p1 = p0 + 1;
        float scale_factor = GetScaleFactor(pos_key[p0].time_stamp, pos_key[p1].time_stamp, time);
        glm::vec3 final_pos = glm::mix(pos_key[p0].position, pos_key[p1].position, scale_factor);
        position = glm::translate(glm::mat4(1.0), final_pos);
        return (position);
    }
    glm::mat4 Animation::Channel::InterapolateScale(float time)
    {
        glm::mat4 scale = 1.0;
        if (scale_key.size() == 1)
            return (glm::scale(glm::mat4(1.0), scale_key[0].scale));
        int p0 = GetScaleIndex(time);
        int p1 = p0 + 1;
        float scale_factor = GetScaleFactor(scale_key[p0].time_stamp, scale_key[p1].time_stamp, time);
        glm::vec3 final_scale = glm::mix(scale_key[p0].scale, scale_key[p1].scale, scale_factor);
        scale = glm::scale(glm::mat4(1.0), final_scale);
        return (scale);
    }
    glm::mat4 Animation::Channel::InterapolateRotation(float time)
    {
        glm::mat4 rotation = 1.0;
        if (rot_key.size() == 1)
            return (glm::mat4_cast(glm::normalize(rot_key[0].rotation)));
        int p0 = GetRotationIndex(time);
        int p1 = p0 + 1;
        float scale_factor = GetScaleFactor(rot_key[p0].time_stamp, rot_key[p1].time_stamp, time);
        glm::quat final_rot = glm::slerp(rot_key[p0].rotation, rot_key[p1].rotation, scale_factor);
        rotation = glm::mat4_cast(glm::normalize(final_rot));
        return (rotation);
    }
    glm::mat4 Animation::Channel::Interpolate(float time)
    {
        glm::mat4 rotation = InterapolateRotation(time);
        glm::mat4 scale = InterapolateScale(time);
        glm::mat4 translation = InterapolatePosition(time);
        return (translation * rotation * scale);
    }

    float Animation::Channel::GetScaleFactor(float last_time, float next_time, float current_time)
    {
        return ((current_time - last_time) / (next_time - last_time));
    }
    int Animation::Channel::GetRotationIndex(float time)
    {
        for (size_t i = 0; i < rot_key.size() - 1; ++i)
            if (time < rot_key[i + 1].time_stamp)
                return (static_cast<int>(i));
        return (-1);
    }
    int Animation::Channel::GetScaleIndex(float time)
    {
        for (size_t i = 0; i < scale_key.size() - 1; ++i)
            if (time < scale_key[i + 1].time_stamp)
                return (static_cast<int>(i));
        return (-1);
    }
    int Animation::Channel::GetPositionIndex(float time)
    {
        for (size_t i = 0; i < pos_key.size() - 1; ++i)
            if (time < pos_key[i + 1].time_stamp)
                return (static_cast<int>(i));
        return (-1);
    }
    Animation::Animation()
        : m_name(), m_node_name(), m_duration(0.0f), m_ticks_per_second(0.0f), m_channels()
    {
    }
    void Animation::SetName(const std::string & name)
    {
        m_name = name;
    }

    std::string Animation::GetName()
    {
        return (m_name);
    }

    void Animation::SetDuration(float duration)
    {
        m_duration = duration;
    }

    float Animation::GetDuration()
    {
        return (m_duration);
    }

    void Animation::SetTicksPerSecond(float ticks)
    {
        m_ticks_per_second = ticks;
    }

    float Animation::SetTicksPerSecond()
    {
        return (m_ticks_per_second);
    }

    void Animation::AddPositionKeyFrame(glm::vec3 position, float time_stamp, std::string channel)
    {
        m_channels[channel].pos_key.push_back(PositionKeyFrame(position, time_stamp));
    }

    void Animation::AddScaleKeyFrame(glm::vec3 scale, float time_stamp, std::string channel)
    {
        m_channels[channel].scale_key.push_back(ScaleKeyFrame(scale, time_stamp));
    }

    void Animation::AddRotationKeyFrame(glm::quat rotation, float time_stamp, std::string channel)
    {
        m_channels[channel].rot_key.push_back(RotationKeyFrame(rotation, time_stamp));
    }

    glm::mat4 Animation::GetKeyTransform(std::string channel, float time)
    {
        float mod_time = fmod(time, m_duration);
        const auto& it = m_channels.find(channel);
        if (it == m_channels.end())
            return (glm::mat4(1.0));
        return (m_channels[channel].Interpolate(mod_time));
    }
}