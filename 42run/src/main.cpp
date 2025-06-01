#include "FT.hpp"
#include "MapRunner.hpp"
#include "Grid.hpp"
#include "BasicText.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <ctime>

using namespace FT;
std::shared_ptr<Grid> CreateMap_TEST_1();
std::shared_ptr<Grid> CreateMap_TEST_2();
std::shared_ptr<Grid> CreateMap_TEST_3();

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
	/* FLOOR TRAIL */
	MapRunner runner(fdp);
	/* TEXT*/
	BasicText txt(fdp);
	/* TIMER */
	Timer delta_timer;
	float program_time = 0.0;
	float last_frame_time = 0.0;
	bool pause = false;
	bool key_flag = true;
	/* SHADERS */
	std::shared_ptr<Shader> sh_col = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_col.glsl");
	std::shared_ptr<Shader> sh_tex = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic_tex.glsl");
	std::vector<std::shared_ptr<Grid>> maps;
	size_t selected_map_id = 0;
	maps.push_back(runner.ReadMap(SANDBOX_ASSETS_DIRECTORY"/maps/basic.42run"));
	maps.push_back(runner.ReadMap(SANDBOX_ASSETS_DIRECTORY"/maps/map1.42run"));

/* ---------------------- MENU SCREEN ---------------------- */
	Camera map_selector_cam(Camera::PERSPECTIVE);
	std::shared_ptr<Texture2D> map_selector_window;
	map_selector_cam.tr.pos = glm::vec3(0.0, 10.0, 0.0);
	//map_selector_cam.tr.Yaw(3.0*glm::pi<float>()/4.0);
	map_selector_cam.tr.Pitch(-glm::half_pi<float>());
	float xsize, ysize, target_size = 3.0, scale_factor;

/* ---------------------- GAME SCREEN ---------------------- */
	/* CAMERA */
	Camera cam(Camera::PERSPECTIVE);
	cam.tr.pos = glm::vec3(0.0, 5.0, -5);
	cam.tr.Yaw(glm::pi<float>());
	cam.tr.Pitch(-glm::half_pi<float>() / 3.0);
	/* MODELS */
	Model marvin = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/marvin/Marvin.dae");
	/* TRANSFORMS */
	Transform marvin_tr(glm::vec3(0.0, -5.0, -5));
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
			if (fdp.GetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				current_screen = GAME;
				pause = false;
				runner.Init(maps[selected_map_id]);
				player.Reset();
			}
			if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS && key_flag)
			{
				selected_map_id = (selected_map_id - 1) % maps.size();
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS && key_flag)
			{
				selected_map_id = (selected_map_id + 1) % maps.size();
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_RELEASE && fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)
				key_flag = true;

			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
				// DRAW MAP CHOOSE WINDOW
				fdp.PushMatrix();
				fdp.BeginLayer(map_selector_cam, sh_tex, true);
					fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
					xsize = FLOOR_WIDTH * (maps[selected_map_id]->GetXSize() - 1.0) / 2.0;
					ysize = FLOOR_WIDTH * (maps[selected_map_id]->GetYSize() - 1.0) / 2.0;
					scale_factor = target_size / xsize;
					fdp.Scale(glm::vec3(scale_factor));
					fdp.Rotate(glm::pi<float>()/4.0, glm::vec3(1.0, 0.0, 0.0));
					fdp.Rotate(program_time, glm::vec3(0.0, 1.0, 0.0));
					fdp.Translate(glm::vec3(xsize, 0.0, -ysize));
					runner.DrawMapPortion(maps[selected_map_id], fdp, glm::vec3(0.0), 0);
				map_selector_window = fdp.EndLayer();
				fdp.PopMatrix();
				// DRAW MENU
				fdp.BeginLayer(sh_tex, false);
					fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
					fdp.Scale(glm::vec3(2.0));
					fdp.Rect(Material(menu_tex));
					fdp.Scale(glm::vec3(0.25));
					fdp.Rect(Material(map_selector_window));
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
		program_time += last_frame_time;
		fdp.SetWindowSuffix(" - FPS: " + std::to_string(1.0 / last_frame_time));
		/* -------------------------------*/
	}

	return (0);
}
