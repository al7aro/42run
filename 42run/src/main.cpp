#include "FT.hpp"
#include "MapRunner.hpp"
#include "Grid.hpp"
#include "BasicText.hpp"
#include "Player.hpp"
#include <cstdlib>
#include <ctime>

using namespace FT;

enum Screen
{
	MENU,
	GAME,
	LOST
};

int main(void)
{
	std::srand(std::time({}));

	/* SCREENS */
	Screen current_screen = MENU;
	//Screen next_screen = MENU;

/* ---------------------- GAME STATE ---------------------- */
	/* RENDER RESOLUTION */
	const int rend_w = 400;
	const int rend_h = 400;
	/* WINDOW SIZE RESOLUTION */
	const int win_w = 1000;
	const int win_h = 1000;
	/* ENGINE */
	Feldespato fdp(win_w, win_h);
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
	std::shared_ptr<Shader> sh = fdp.LoadShader(SANDBOX_ASSETS_DIRECTORY"/shaders/basic.glsl");
	std::vector<std::shared_ptr<Grid>> maps;
	int selected_map_id = 0;
	maps.push_back(0); // FIRST MAP IS ALWAYS THE RANDOM ONE
	maps.push_back(MapRunner::ReadMap(SANDBOX_ASSETS_DIRECTORY"/maps/basic.42run"));
	maps.push_back(MapRunner::ReadMap(SANDBOX_ASSETS_DIRECTORY"/maps/map1.42run"));

/* ---------------------- MENU SCREEN ---------------------- */
	Camera map_selector_cam(Camera::PERSPECTIVE);
	std::shared_ptr<Texture2D> map_selector_window;
	map_selector_cam.tr.pos = FT::vec3(0.0, 10.0, 0.0);
	//map_selector_cam.tr.Yaw(3.0*FT::PI/4.0);
	map_selector_cam.tr.Pitch(-FT::HALF_PI);
	float xsize, ysize, target_size = 3.0, scale_factor;
	float rot_speed = 2.0;
	float rot_offset = 0.0;
	Model q_mark = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/q_mark/q_mark.obj");

/* ---------------------- GAME SCREEN ---------------------- */
	/* CAMERA */
	Camera cam(Camera::PERSPECTIVE);
	cam.tr.pos = FT::vec3(0.0, 5.0, -5.0);
	cam.tr.Yaw(FT::PI);
	cam.tr.Pitch(FT::PI / 8.0);
	/* TRANSFORMS */
	Transform marvin_tr(FT::vec3(0.0, -5.0, -5));
	/* Player */
	Player player(fdp);
	int score = 0;

/* ---------------------- LOST SCREEN ---------------------- */
	float lost_timer = 0;
	float lost_screen_time = 3;

/* ---------------------- GAME SCREEN ---------------------- */
	std::shared_ptr<Texture2D> intro_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/intro_test.png");
	std::shared_ptr<Texture2D> menu_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/menu_test.png");
	std::shared_ptr<Texture2D> pause_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/pause_test.png");
	std::shared_ptr<Texture2D> explosion_tex = fdp.LoadTexture(SANDBOX_ASSETS_DIRECTORY"/textures/explosion.png");

	std::shared_ptr<Texture2D> post_pro;

	while (!fdp.WindowShouldClose())
	{
/* ----------- GLOBAL GAME STATE ------------*/
		delta_timer.Start();
/* -------------------------------*/
		switch (current_screen)
		{
/* ---------------------- MENU SCREEN ---------------------- */
		case Screen::MENU:
			/* ----------- UPDATE -------------*/
			if (fdp.GetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				current_screen = GAME;
				pause = false;
				std::shared_ptr<Grid> map;
				if (selected_map_id == 0)
					map = MapRunner::RandomMap();
				else
					map = maps[selected_map_id];
				runner.Init(map);
				player.Reset();
			}
			if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS && key_flag)
			{
				selected_map_id = FT::mod(selected_map_id - 1, maps.size());
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS && key_flag)
			{
				selected_map_id = FT::mod(selected_map_id + 1, maps.size());
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_LEFT) == GLFW_RELEASE && fdp.GetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)
				key_flag = true;
			rot_offset += last_frame_time * rot_speed;

			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
			// POST-PROCESSING LAYER
			fdp.BeginLayer(FT::ivec2(rend_w, rend_h));
				// TODO: DRAW QUESTION MAP FOR RANDOM MAP
				// DRAW MAP CHOOSE WINDOW
				fdp.PushMatrix();
				fdp.BeginLayer(map_selector_cam, sh, true);
					fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
					if (selected_map_id != 0)
					{
						fdp.RotateX(FT::PI / 4.0);
						fdp.RotateY(rot_offset);
						xsize = FLOOR_WIDTH * (maps[selected_map_id]->GetXSize() - 1.0) / 2.0;
						ysize = FLOOR_WIDTH * (maps[selected_map_id]->GetYSize() - 1.0) / 2.0;
						scale_factor = target_size / xsize;
						fdp.Scale(FT::vec3(scale_factor));
						fdp.Translate(FT::vec3(xsize, 0.0, -ysize));
						runner.DrawMapPortion(maps[selected_map_id], fdp, FT::ivec3(0));
					}
					else
					{
						fdp.RotateX(FT::HALF_PI);
						fdp.RotateY(1.5 * rot_offset);
						fdp.Draw(q_mark, Transform(FT::vec3(0.0, FT::sin(2.0 * rot_offset), 0.0), FT::vec3(2.0)));
					}
				map_selector_window = fdp.EndLayer();
				fdp.PopMatrix();
				// DRAW MENU
				fdp.PushMatrix();
				fdp.BeginLayer(sh);
					fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
					fdp.Scale(FT::vec3(2.0));
					fdp.Rect(Material(menu_tex));
					fdp.Scale(FT::vec3(0.25));
					fdp.Rect(Material(map_selector_window));
				fdp.EndLayer();
				fdp.PopMatrix();
			post_pro = fdp.EndLayer();
			// POST-PROCESSING LAYER
			fdp.BeginLayer(sh);
				fdp.ClearBuffer(0.0, 0.0, 0.0, 1.0f);
				fdp.Rect(Transform(FT::vec3(0.0), FT::vec3(2.0, -2.0, 1.0)), Material(post_pro));
			fdp.EndLayer();
			fdp.EndRenderPass();

			/* -------------------------------*/
			break;
/* ---------------------- GAME SCREEN ---------------------- */
		case Screen::GAME:
			/* ----------- UPDATE -------------*/
			//fdp.DefaultCameraMovement(cam, last_frame_time);
			if (fdp.GetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS && key_flag && pause && !runner.GetCollision())
			{
				current_screen = Screen::MENU;
				selected_map_id = 0;
			}
			if (fdp.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS && key_flag && !runner.GetCollision())
			{
				pause = !pause;
				key_flag = false;
			}
			if (fdp.GetKey(GLFW_KEY_ESCAPE) == GLFW_RELEASE && !runner.GetCollision())
				key_flag = true;
			if (!pause)
			{
				if (runner.GetCollision())
				{
					if (lost_timer == 0)
						lost_timer = program_time;
					if ((program_time - lost_timer) >= lost_screen_time)
					{
						selected_map_id = 0;
						lost_timer = 0;
						current_screen = MENU;
					}
					else if ((program_time - lost_timer) < 0.05)
					{
						player.Update(fdp, last_frame_time);
						runner.Update(fdp, player, last_frame_time);
					}
				}
				else
				{
					player.Update(fdp, last_frame_time);
					runner.Update(fdp, player, last_frame_time);
				}
				if (runner.GetScore() != score)
					score = runner.GetScore();
			}
			/* -------------------------------*/
			/* ----------- RENDER ------------*/
			fdp.BeginRenderPass();
			// POST-PROCESSING LAYER
			fdp.BeginLayer(FT::ivec2(rend_w, rend_h));

				fdp.ClearBuffer(255.0f / 255.0f, 23.0f / 255.0f, 62.0f / 255.0f, 1.0f);
				fdp.BeginLayer(cam, sh, false);
					player.Draw(fdp, !runner.GetCollision() * last_frame_time);
				fdp.EndLayer();
				fdp.BeginLayer(cam, sh, false);
					runner.Draw(fdp);
				fdp.EndLayer();
				fdp.BeginLayer(sh, false); // TEXT LAYER
					fdp.PushMatrix();
					fdp.Translate(FT::vec3(1.0, 0.75, 0.0));
					txt.Draw(fdp, std::to_string(score), 0.5);
					fdp.PopMatrix();
				fdp.EndLayer();
				if (pause)
				{
					fdp.BeginLayer(sh, false);
						fdp.Rect(pause_tex);
					fdp.EndLayer();
				}
				if (runner.GetCollision())
				{
					fdp.BeginLayer(sh, false);
					fdp.Rect(explosion_tex);
					fdp.EndLayer();
				}
			post_pro = fdp.EndLayer();
			// POST-PROCESSING LAYER
			fdp.BeginLayer(sh);
				fdp.ClearBuffer(0.0, 0.0, 0.0, 1.0f);
				fdp.Rect(Transform(FT::vec3(0.0), FT::vec3(2.0, -2.0, 1.0)), Material(post_pro));
				fdp.EndLayer();
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
