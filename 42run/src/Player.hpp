#pragma once

#include "FT.hpp"
#include "Floor.hpp"

enum PlayerPosition
{
	LEFT = 1,
	MIDDLE = 0,
	RIGHT = -1
};

class Player
{
public:
	enum PlayerPosition
	{
		LEFT = 1,
		MIDDLE = 0,
		RIGHT = -1
	};
private:
	FT::Model m_model;

	FT::vec3 m_pos;
	PlayerPosition m_side;

	bool m_jumping;
	float m_jump_speed;
	float m_jump_offset;

	// TODO: ADD CROUCHING ANIMATION
public:
	Player(FT::Feldespato & fdp, const std::string & model_path = SANDBOX_ASSETS_DIRECTORY"/marvin/Marvin.obj")
		: m_pos(0.0), m_side(MIDDLE), m_jumping(false), m_jump_speed(0.05), m_jump_offset(0.0)
	{
		m_model = fdp.LoadModel(model_path);
	}

	void Update(FT::Feldespato & fdp)
	{
		/* INPUT HANDLER */
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS && !m_jumping)
			m_jumping = true;
		if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS && !m_jumping)
			m_side = Player::LEFT;
		else if (fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS && !m_jumping)
			m_side = Player::RIGHT;
		else if (!m_jumping)
			m_side = Player::MIDDLE;

		/* JUMP MOVEMENT */
		if (m_jumping)
		{
			m_jump_offset = FT::clamp(m_jump_offset + m_jump_speed, 0.0f, FT::PI);
			m_pos.y = 1.35 * FT::sin(m_jump_offset);
			if (m_jump_offset >= FT::PI)
			{
				m_jump_offset = 0.0;
				m_jumping = false;
			}
		}

		/* HORIZONTAL MOVEMENT */
		m_pos.x += 0.15 * FT::clamp((m_side - m_pos.x), -FLOOR_WIDTH / 2.0f, FLOOR_WIDTH / 2.0f);
	}
	/*
		Pedro Miras participó en este proyecto.
	*/
	void Draw(FT::Feldespato& fdp)
	{
		fdp.PushMatrix();
		fdp.Translate(m_pos);
		fdp.Draw(m_model);
		fdp.PopMatrix();
	}

	void SetPos(const FT::vec3 & pos)
	{
		m_pos = pos;
	}

	FT::vec3 GetPos() const
	{
		return (m_pos);
	}

	void SetSide(PlayerPosition side)
	{
		m_side = side;
	}

	PlayerPosition GetSide() const
	{
		return (m_side);
	}

	bool IsJumping() const
	{
		return (m_jumping);
	}

	void Reset()
	{
		m_pos = FT::vec3(0.0);
		m_side = MIDDLE;
		m_jumping = false;
		m_jump_speed = 0.05;
		m_jump_offset = 0.0;
	}
};
