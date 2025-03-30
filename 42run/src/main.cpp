#include "FT.hpp"

using namespace FT;

int main(void)
{
	Feldespato fdp;
	Timer delta_timer;
	float last_frame_time = 0.0;

	Camera cam(Camera::PERSPECTIVE);
	std::shared_ptr<Shader> sh_col = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_col.glsl");
	std::shared_ptr<Shader> sh_tex = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_tex.glsl");

	/* MODELS */
	Model marvin = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/Marvin.dae");

	Model floor_front = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front.dae");
	Transform front_floor_tr(glm::vec3(0.0, 0.0, 0.0));
	Transform aux_front_floor_tr;

	Model floor_right = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right.dae");
	Transform right_floor_tr;
	Transform aux_right_floor_tr;

	Model floor_uo = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_up.dae");
	Transform up_floor_tr;
	Transform aux_up_floor_tr;

	/* TRANSFORMS */
	Transform marvin_tr(glm::vec3(0.0, -1.0, -2));

	float y = 0.0;
	bool pause = true;
	bool flag = false;
	while (!fdp.WindowShouldClose())
	{
		/* ----------- UPDATE ------------*/
		fdp.DefaultCameraMovement(cam, last_frame_time);
		delta_timer.Start();
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_PRESS && flag)
		{
			pause = !pause;
			flag = !flag;
		}
		if (fdp.GetKey(GLFW_KEY_SPACE) == GLFW_RELEASE && !flag)
			flag = !flag;
		/* -------------------------------*/

		/* ----------- RENDER ------------*/
		fdp.BeginRenderPass();
			fdp.ClearBuffer(255.0f/255.0f, 23.0f/255.0f, 62.0f/255.0f, 1.0f);
			fdp.BeginLayer(cam, sh_col, false);
				// marvin_tr.parent = cam.tr.GetTransform();
				marvin_tr.pos = glm::vec3(0.0, 0.0, 0.0);
				fdp.Draw(marvin, marvin_tr);
			fdp.EndLayer();
			fdp.BeginLayer(cam, sh_tex, false);
				aux_front_floor_tr.pos = glm::vec3(0.0, 0.0, 4.0);
				aux_front_floor_tr.parent = front_floor_tr.GetTransform();
				aux_right_floor_tr.pos = glm::vec3(0.0, 0.0, 4.0);
				aux_right_floor_tr.parent = front_floor_tr.GetTransform() * aux_front_floor_tr.GetTransform();

				fdp.Draw(floor_front, front_floor_tr);
				fdp.Draw(floor_front, aux_front_floor_tr);
				fdp.Draw(floor_right, aux_right_floor_tr);
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