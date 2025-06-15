#pragma once

#include <iostream>
#include <memory>
#include <stack>

#include "buffers/FrameBuffer.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Layer.hpp"
#include "Timer.hpp"
#include "Transform.hpp"
#include "math/Math.hpp"
#include "resources/Texture2D.hpp"
#include "Renderable.hpp"
#include "resource_manager/ResourceManager.hpp"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 800;

namespace FT {
	struct RenderData
	{
        // TODO: CREATE FRAMEBUFFER STACK
        std::shared_ptr<Shader>                         default_shader;
        Camera                                          default_camera;
        std::stack<std::shared_ptr<FrameBuffer>>        framebuffer;
        std::stack<std::shared_ptr<Layer> >             ly;
		std::stack<FT::mat4>                            tr;
	};

    class Feldespato
    {
    private:
        std::shared_ptr<Window>             m_window;
        std::shared_ptr<ResourceManager>    m_rm;
		RenderData                          m_data;

    public:
        Feldespato(int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT);
        ~Feldespato();
        bool                        WindowShouldClose();
        void                        SetWindowSuffix(const std::string& suffix);
        void                        ResetRenderData();
        /* RENDER MODE */
        void                        BeginRenderPass();
        void                        EndRenderPass();
        void                        BeginLayer(FT::ivec2 size = FT::ivec2(0));
        void                        BeginLayer(bool tex_mode);
        void                        BeginLayer(std::shared_ptr<Shader> sh, FT::ivec2 size = FT::ivec2(0));
        void                        BeginLayer(std::shared_ptr<Shader> sh, bool tex_mode);
        void                        BeginLayer(const Camera& cam, FT::ivec2 size = FT::ivec2(0));
        void                        BeginLayer(const Camera & cam, bool tex_mode);
        void                        BeginLayer(const Camera& cam, std::shared_ptr<Shader> sh, FT::ivec2 size = FT::ivec2(0));
        void                        BeginLayer(const Camera & cam, std::shared_ptr<Shader> sh, bool tex_mode);
        std::shared_ptr<Texture2D>  EndLayer();

        /* DRAW FUNCTIONS */
        void                        ClearBuffer(float r, float g, float b, float a);
        void                        Rect();
        void                        Rect(Material mat);
        void                        Rect(Transform transform);
        void                        Rect(Transform transform, Material mat);
        void                        Cube();
        void                        Cube(Material mat);
        void                        Cube(Transform transform);
        void                        Cube(Transform transform, Material mat);
        void                        Draw(Mesh & mesh);
        void                        Draw(Mesh & mesh, Transform transform, Material mat);
        void                        Draw(Model & model);
        void                        Draw(Model & model, Transform transform);

        /* TRANSFORMATION STACK */
        void                        Translate(FT::vec3 v);
        void                        Scale(FT::vec3 v);
        void                        RotateX(float a);
        void                        RotateY(float a);
        void                        RotateZ(float a);
        void                        PushMatrix();
        void                        PopMatrix();
        FT::mat4                   GetTransform() const;

        /* RESOURCE LOADING */
        Model                       LoadModel(const std::string& path);
        Mesh                        LoadMeshRect();
        Mesh                        LoadMeshCube();
        std::shared_ptr<Shader>     LoadShader(const std::string& path);
        std::shared_ptr<Texture2D>  LoadTexture(const std::string& path);
        
        /* INPUT */
        int                         GetKey(int key);
        FT::vec2                   GetMousePosPrev();
        FT::vec2                   GetMousePos();
        int                         GetMouseButton(int button);

        /* MISCELLANEOUS */
        void                        DefaultCameraMovement(Camera & cam, float delta_time);
    };
}