#include "FT.hpp"
#include "MapRunner.hpp"
#include "BasicText.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <ctime>

using namespace FT;

enum Screen
{
	INTRO = 0,
	MENU,
	GAME
};

int main(void)
{
	std::srand(std::time({}));

	/* SCREENS */
	Screen current_screen = MENU;
	//Screen next_screen = MENU;

/* ---------------------- GAME STATE ---------------------- */
	/* ENGINE */
	Feldespato fdp;
	/* TEXT*/
	BasicText txt(fdp);
	/* TIMER */
	Timer delta_timer;
	float last_frame_time = 0.0;
	bool pause = false;
	bool key_flag = true;
	/* SHADERS */
	std::shared_ptr<Shader> sh_col = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_col.glsl");
	std::shared_ptr<Shader> sh_tex = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_tex.glsl");

/* ---------------------- GAME SCREEN ---------------------- */
	/* CAMERA */
	Camera cam(Camera::PERSPECTIVE);
	cam.tr.pos = glm::vec3(0.0, 5.0, -5);
	cam.tr.Yaw(glm::pi<float>());
	cam.tr.Pitch(-glm::half_pi<float>() / 3.0);
	/* MODELS */
	Model marvin = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/Marvin.dae");
	/* TRANSFORMS */
	Transform marvin_tr(glm::vec3(0.0, -1.0, -2));
	/* FLOOR TRAIL */
	MapRunner runner(fdp);
	runner.Init();
	/* Player */
	Player player(fdp);
	int score = 0;

/* ---------------------- GAME SCREEN ---------------------- */
	std::shared_ptr<Texture2D> intro_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/intro_test.png");
	std::shared_ptr<Texture2D> menu_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/menu_test.png");
	std::shared_ptr<Texture2D> pause_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/pause_test.png");

	while (!fdp.WindowShouldClose())
	{
		/* ----------- GLOBAL GAME STATE ------------*/
		delta_timer.Start();
		/* -------------------------------*/
		switch (current_screen)
		{
/* ---------------------- INTRO SCREEN ---------------------- */
		case Screen::INTRO:
			/* ----------- UPDATE -------------*/
			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
				fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
				fdp.BeginLayer(sh_tex, false);
					fdp.Rect(Material(intro_tex));
				fdp.EndLayer();
			fdp.EndRenderPass();
			/* -------------------------------*/
			break;
/* ---------------------- MENU SCREEN ---------------------- */
		case Screen::MENU:
			/* ----------- UPDATE -------------*/
			if (fdp.GetKey(GLFW_KEY_ENTER) == GLFW_PRESS && key_flag)
			{
				current_screen = GAME;
				key_flag = false;
				pause = false;
				runner.Reset();
				player.Reset();
			}
			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
				fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
				fdp.BeginLayer(sh_tex, false);
					fdp.Rect(Material(menu_tex));
				fdp.EndLayer();
			fdp.EndRenderPass();
			/* -------------------------------*/
			break;
/* ---------------------- GAME SCREEN ---------------------- */
		case Screen::GAME:
			/* ----------- UPDATE -------------*/
			//fdp.DefaultCameraMovement(cam, last_frame_time);
			if (fdp.GetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS && key_flag && pause)
			{
				current_screen = Screen::MENU;
			}
			if (fdp.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS && key_flag)
			{
				pause = !pause;
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_ESCAPE) == GLFW_RELEASE)
				key_flag = true;
			if (!pause)
			{
				player.Update(fdp);
				runner.Update(fdp, player);
				if (runner.GetCollision())
					current_screen = MENU;
				if (runner.GetScore() != score)
					score = runner.GetScore();
			}
			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
				fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
				fdp.BeginLayer(cam, sh_col, false);
					player.Draw(fdp);
				fdp.EndLayer();
				fdp.BeginLayer(cam, sh_tex, false);
					runner.Draw(fdp);
				fdp.EndLayer();
				fdp.BeginLayer(sh_tex, false); // TEXT LAYER
					fdp.PushMatrix();
					fdp.Translate(glm::vec3(1.0, 0.75, 0.0));
					txt.Draw(fdp, std::to_string(score), 0.5);
					fdp.PopMatrix();
				fdp.EndLayer();
				if (pause)
				{
					fdp.BeginLayer(sh_tex, false);
						fdp.Rect(pause_tex);
					fdp.EndLayer();
				}
			fdp.EndRenderPass();
			/* -------------------------------*/
			break;
		};

		/* ----------- GLOBAL GAME STATE ------------*/
		last_frame_time = delta_timer.EllapsedSeconds();
		fdp.SetWindowSuffix(" - FPS: " + std::to_string(1.0 / last_frame_time));
		/* -------------------------------*/
	}

	return (0);
}