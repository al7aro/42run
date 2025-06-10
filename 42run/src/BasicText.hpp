#pragma once

#include <string>

#include "FT.hpp"

class BasicText
{
public:
	enum ALIGN
	{
		RIGHT = -1,
		CENTER = 0,
		LEFT = 1
	};
private:
	std::vector<std::shared_ptr<FT::Texture2D>> m_numbers;
	float m_aspect;

public:
	BasicText(FT::Feldespato & fdp)
		: m_aspect(9.0/16.0)
	{
		for (int i = 0; i <= 9; i++)
			m_numbers.push_back(fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/numbers/num_" + std::to_string(i) + ".png"));
	}

	void Draw(FT::Feldespato& fdp, const std::string& text, float font_size = 1.0, ALIGN align = RIGHT)
	{
		float width = font_size * m_aspect;
		float height = font_size;
		float text_width = text.size() * width;
		FT::Transform tr(FT::vec3(0.0), FT::vec3(width, height, 1.0));
		fdp.PushMatrix();
		fdp.Translate(FT::vec3(-width * (text.size() - 1) / 2.0, 0.0, 0.0)); // CENTER ALIGN
		fdp.Translate(FT::vec3(align*text_width/2.0, 0.0, 0.0)); // RIGHT ALIGN
		for (int i = 0; i < text.size(); i++)
		{
			char c = text[i] - 48;
			if (c < 0 || c > 9) continue;
			tr.pos.x = float(i) * width;
			fdp.Rect(tr, FT::Material(m_numbers[c]));
		}
		fdp.PopMatrix();
	}
};