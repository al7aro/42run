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
	FT::Model m_body;
	FT::Model m_left_arm;
	FT::Model m_right_arm;
	FT::Model m_left_leg;
	FT::Model m_right_leg;
	float m_arms_height;
	float m_legs_height;
	float m_animation_speed;
	float m_body_displacement;

	FT::vec3 m_pos;
	PlayerPosition m_side;

	bool m_jumping;
	float m_jump_speed;
	float m_jump_offset;

	float m_side_speed;
	float m_anim_rot;

	// TODO: ADD CROUCHING ANIMATION
public:
	Player(FT::Feldespato & fdp)
		: m_pos(0.0), m_side(MIDDLE), m_jumping(false), m_jump_offset(0.0)
	{
		m_body = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/body.obj");
		m_left_arm = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/left_arm.obj");
		m_right_arm = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/right_arm.obj");
		m_left_leg = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/left_leg.obj");
		m_right_leg = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/right_leg.obj");

		m_arms_height = 0.66;
		m_legs_height = 0.34;
		m_body_displacement = 0.04;

		m_animation_speed = 15.0;
		m_side_speed = 20.0;
		m_jump_speed = 8.0;
		m_anim_rot = 0.0;
	}

	void Update(FT::Feldespato & fdp, float delta_time)
	{
		float final_jump_speed = m_jump_speed * delta_time;
		float final_side_speed = m_side_speed * delta_time;

		/* INPUT HANDLER */
		if ((fdp.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS) || ((fdp.GetKey(GLFW_KEY_UP) == GLFW_PRESS)) && !m_jumping)
			m_jumping = true;
		if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
			m_side = Player::LEFT;
		else if (fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
			m_side = Player::RIGHT;
		else
			m_side = Player::MIDDLE;

		/* JUMP MOVEMENT */
		if (m_jumping)
		{
			m_jump_offset += final_jump_speed;
			m_pos.y = 1.35 * FT::sin(m_jump_offset);
			if (m_jump_offset >= FT::PI)
			{
				m_jump_offset = 0.0;
				m_jumping = false;
			}
		}

		/* HORIZONTAL MOVEMENT */
		m_pos.x += final_side_speed * FT::clamp((m_side - m_pos.x), -1.0, 1.0);
	}
	/*
		Pedro Miras participů en este proyecto.
	*/
	void Draw(FT::Feldespato& fdp, float delta_time)
	{
		m_anim_rot += m_animation_speed * delta_time;

		fdp.PushMatrix();
		fdp.Scale(0.75);
		fdp.Translate(WALK_FLOOR_WIDTH * m_pos);


		fdp.PushMatrix();
		fdp.Translate(FT::vec3(0.0, m_body_displacement * FT::sin(m_anim_rot), 0.0));
		fdp.Draw(m_body);
		fdp.PopMatrix();

		// LEFT ARM ANIMATION
		fdp.PushMatrix();
		fdp.Translate(FT::vec3(0.0, m_arms_height, 0.0));
		fdp.RotateX(FT::sin(m_anim_rot));
		fdp.Translate(-FT::vec3(0.0, m_arms_height, 0.0));
		fdp.Draw(m_left_arm);
		fdp.PopMatrix();

		// RIGHT ARM ANIMATION
		fdp.PushMatrix();
		fdp.Translate(FT::vec3(0.0, m_arms_height, 0.0));
		fdp.RotateX(-FT::sin(m_anim_rot));
		fdp.Translate(-FT::vec3(0.0, m_arms_height, 0.0));
		fdp.Draw(m_right_arm);
		fdp.PopMatrix();

		// LEFT LEG ANIMATION
		fdp.PushMatrix();
		fdp.Translate(FT::vec3(0.0, m_legs_height, 0.0));
		fdp.RotateX(-FT::sin(m_anim_rot));
		fdp.Translate(-FT::vec3(0.0, m_legs_height, 0.0));
		fdp.Draw(m_left_leg);
		fdp.PopMatrix();

		// RIGHT LEG ANIMATION
		fdp.PushMatrix();
		fdp.Translate(FT::vec3(0.0, m_legs_height, 0.0));
		fdp.RotateX(FT::sin(m_anim_rot));
		fdp.Translate(-FT::vec3(0.0, m_legs_height, 0.0));
		fdp.Draw(m_right_leg);
		fdp.PopMatrix();
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

	float GetJumpPerc() const
	{
		return (FT::sin(m_jump_offset));
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
		m_jump_offset = 0.0;
	}
};
