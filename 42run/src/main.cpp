#include "FT.hpp"
#include "Trail.hpp"
#include "Player.hpp"

using namespace FT;

int main(void)
{
	Feldespato fdp;
	Timer delta_timer;
	float last_frame_time = 0.0;
	PlayerPosition p = MIDDLE;

	Camera cam(Camera::PERSPECTIVE);
	cam.tr.pos = glm::vec3(0.0, 5.0, -5);
	cam.tr.Yaw(glm::pi<float>());
	cam.tr.Pitch(-glm::half_pi<float>() / 3.0);
	std::shared_ptr<Shader> sh_col = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_col.glsl");
	std::shared_ptr<Shader> sh_tex = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_tex.glsl");

	/* MODELS */
	Model marvin = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/Marvin.dae");

	/* TRANSFORMS */
	Transform marvin_tr(glm::vec3(0.0, -1.0, -2));

	/* FLOOR TRAIL */
	Trail trail(fdp);
	trail.Init();

	float y = 0.0;
	bool pause = true;
	bool flag = false;
	bool jump_finished = true;
	glm::vec3 pos(0.0);
	float jump_offset = 0.0;
	while (!fdp.WindowShouldClose())
	{
		/* ----------- UPDATE -----------s-*/
		fdp.DefaultCameraMovement(cam, last_frame_time);
		delta_timer.Start();
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS && flag)
		{
			pause = !pause;
			flag = !flag;
		}
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_RELEASE && !flag)
			flag = !flag;
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS && jump_finished)
			jump_finished = false;
		if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS && jump_finished)
			p = PlayerPosition::LEFT;
		else if (fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS && jump_finished)
			p = PlayerPosition::RIGHT;
		else if (jump_finished)
			p = PlayerPosition::MIDDLE;

		//JUMP
		if (!jump_finished)
		{
			jump_offset = glm::clamp(jump_offset + 0.05f, 0.0f, glm::pi<float>());
			pos.y = glm::sin(jump_offset);
			if (jump_offset >= glm::pi<float>())
			{
				jump_offset = 0.0;
				jump_finished = true;
			}
		}
		/* -------------------------------*/
		/* ----------- RENDER ------------*/
		fdp.BeginRenderPass();
			fdp.ClearBuffer(255.0f/255.0f, 23.0f/255.0f, 62.0f/255.0f, 1.0f);
			fdp.BeginLayer(cam, sh_col, false);
				fdp.PushMatrix();
				pos.x += 0.15 * glm::clamp((p - pos.x), -FLOOR_WIDTH/2.0f, FLOOR_WIDTH/2.0f);
				fdp.Translate(glm::vec3(pos.x, pos.y, 0.0));
				marvin_tr.pos = glm::vec3(0.0, 0.0, 0.0);
				fdp.Draw(marvin, marvin_tr);
				fdp.PopMatrix();
			fdp.EndLayer();
			fdp.BeginLayer(cam, sh_tex, false);
				trail.Draw(fdp, p);
			fdp.EndLayer();
		fdp.EndRenderPass();
		/* -------------------------------*/

		/* ----------- UPDATE ------------*/
		if (!pause)
			y += 0.15f;
		last_frame_time = delta_timer.EllapsedSeconds();
		fdp.SetWindowSuffix(" - FPS: " + std::to_string(1.0 / last_frame_time));
		/* -------------------------------*/
	}

	return (0);
}