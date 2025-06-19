#include "Feldespato.hpp"

namespace FT {
    Feldespato::Feldespato(int w, int h)
    {
        m_window = std::make_shared<Window>("Feldespato Renderer", w, h);
        m_rm = std::make_shared<ResourceManager>(DEFAULT_ASSETS_DIRECTORY"/shaders/410/basic.glsl", DEFAULT_ASSETS_DIRECTORY"/textures/error.png");
        m_data.default_shader = m_rm->GetDefaultShader();
        m_data.default_camera = Camera(Camera::ORTHOGRAPHIC);
        //m_data.framebuffer = std::make_shared<FrameBuffer>(m_window->GetWidth(), m_window->GetHeight());
        m_data.framebuffer.push(0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    Feldespato::~Feldespato()
    {
    }
    bool Feldespato::WindowShouldClose()
    {
        return (m_window->ShouldClose());
    }
    void Feldespato::SetWindowSuffix(const std::string& suffix)
    {
        m_window->SetWindowSuffix(suffix);
    }
    void Feldespato::ResetRenderData()
    {
        while (!m_data.tr.empty())
            m_data.tr.pop();
        while (!m_data.ly.empty())
            m_data.ly.pop();
        m_data.tr.push(FT::mat4(1.0));
        std::shared_ptr<Layer> layer = std::make_shared<Layer>();
        layer->SetCamera(m_data.default_camera);
        layer->SetShader(m_data.default_shader);
        m_data.ly.push(layer);
    }

    /* RENDER MODE */
    void Feldespato::ClearBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    void Feldespato::BeginRenderPass()
    {
        ResetRenderData();
    }
    void Feldespato::EndRenderPass()
    {
        if (m_data.ly.size() >= 1)
        {
            m_data.ly.top()->Render();
            m_data.ly.pop();
        }
        m_window->PollEvents();
        m_window->SwapBuffers();
    }
    void Feldespato::BeginLayer(const Camera & cam, std::shared_ptr<Shader> sh, FT::ivec2 size)
    {
        std::shared_ptr<FrameBuffer> fb = 0;
        // TODO: FIX THIS VIEWPORT THING
        if (size.x != 0 && size.y != 0)
        {
            fb = std::make_shared<FrameBuffer>(size.x, size.y);
            fb->Enable();
        }
        else
        {
            size = FT::ivec2(m_window->GetWidth(), m_window->GetHeight());
            fb = m_data.framebuffer.top();
            if (fb)
            {
                size.x = fb->GetWidth();
                size.y = fb->GetHeight();
            }
        }

        glViewport(0, 0, size.x, size.y);
        std::shared_ptr<Layer> layer = std::make_shared<Layer>();
        layer->SetCamera(cam);
        layer->SetShader(sh);
        m_data.framebuffer.push(fb);
        m_data.ly.push(layer);
    }
    void Feldespato::BeginLayer(const Camera& cam, std::shared_ptr<Shader> sh, bool tex_mode)
    {
        FT::ivec2 size(0);
        std::shared_ptr<FrameBuffer> fb = m_data.framebuffer.top();
        if (tex_mode)
        {
            size.x = m_window->GetWidth();
            size.y = m_window->GetHeight();
            if (fb)
            {
                size.x = fb->GetWidth();
                size.y = fb->GetHeight();
            }
        }
        BeginLayer(cam, sh, size);
    }
    void Feldespato::BeginLayer(FT::ivec2 size)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), m_data.ly.top()->GetShader(), size);
    }
    void Feldespato::BeginLayer(bool tex_mode)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), m_data.ly.top()->GetShader(), tex_mode);
    }
    void Feldespato::BeginLayer(std::shared_ptr<Shader> shader, FT::ivec2 size)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), shader, size);
    }
    void Feldespato::BeginLayer(std::shared_ptr<Shader> shader, bool tex_mode)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), shader, tex_mode);
    }
    void Feldespato::BeginLayer(const Camera & camera, FT::ivec2 size)
    {
        BeginLayer(camera, m_data.ly.top()->GetShader(), size);
    }
    void Feldespato::BeginLayer(const Camera& camera, bool tex_mode)
    {
        BeginLayer(camera, m_data.ly.top()->GetShader(), tex_mode);
    }
    std::shared_ptr<Texture2D> Feldespato::EndLayer()
    {
        std::shared_ptr<Texture2D> tex;
        if (m_data.ly.size() >= 1)
        {
            m_data.ly.top()->Render();
            m_data.ly.pop();
        }
        if (m_data.framebuffer.size() >= 1)
        {
            std::shared_ptr<FrameBuffer> fb = m_data.framebuffer.top();
            if (fb)
            {
                fb->Disable();
                tex = fb->GetFrameColor();
            }
            m_data.framebuffer.pop();
            fb = m_data.framebuffer.top();
            if (fb)
                fb->Enable();
        }
        // ENABLE NEXT FB IN STACK
        return (tex);
    }

    /* DRAW FUNCTIONS */
    void Feldespato::Rect(Transform transform, Material mat)
    {
        Mesh mesh = m_rm->LoadMesh(Mesh::MeshType::RECT);
        mesh.SetMaterial(mat);
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(mesh, transform);
        m_data.ly.top()->Add(renderable);
    }
    void Feldespato::Rect()
    {
        Transform transform = Transform();
        Material mat = Material();
        Rect(transform, mat);
    }
    void Feldespato::Rect(Transform transform)
    {
        Material mat;
        Rect(transform, mat);
    }
    void Feldespato::Rect(Material mat)
    {
        Transform transform = Transform();
        Rect(transform, mat);
    }

    void Feldespato::Cube(Transform transform, Material mat)
    {
        Mesh mesh = m_rm->LoadMesh(Mesh::MeshType::CUBE);
        mesh.SetMaterial(mat);
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(mesh, transform);
        m_data.ly.top()->Add(renderable);
    }
    void Feldespato::Cube()
    {
        Transform transform;
        Material material;
        Cube(transform, material);
    }
    void Feldespato::Cube(Transform transform)
    {
        Material mat;
        Cube(transform, mat);
    }
    void Feldespato::Cube(Material mat)
    {
        Transform transform;
        Cube(transform, mat);
    }
    void Feldespato::Draw(Mesh& mesh)
    {
        Transform transform;
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(mesh, transform);
        m_data.ly.top()->Add(renderable);
    }
    void Feldespato::Draw(Mesh & mesh, Transform transform, Material mat)
    {
        mesh.SetMaterial(mat);
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(mesh, transform);
        m_data.ly.top()->Add(renderable);
    }
    void Feldespato::Draw(Model & model)
    {
        Transform transform;
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(model, transform);
        m_data.ly.top()->Add(renderable);
    }
    void Feldespato::Draw(Model & model, Transform transform)
    {
        transform.parent *= m_data.tr.top();
        std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(model, transform);
        m_data.ly.top()->Add(renderable);
    }

    /* TRANSFORMATION STACK */
    void Feldespato::Translate(FT::vec3 v)
    {
        FT::mat4 tr = FT::translate(v);
        m_data.tr.top() *= tr;
    }
    void Feldespato::Scale(FT::vec3 v)
    {
        FT::mat4 sc = FT::scale(v);
        m_data.tr.top() *= sc;
    }
    void Feldespato::RotateX(float a)
    {
        FT::mat4 rt = FT::rotateX(a);
        m_data.tr.top() *= rt;
    }
    void Feldespato::RotateY(float a)
    {
        FT::mat4 rt = FT::rotateY(a);
        m_data.tr.top() *= rt;
    }
    void Feldespato::RotateZ(float a)
    {
        FT::mat4 rt = FT::rotateZ(a);
        m_data.tr.top() *= rt;
    }
    FT::mat4 Feldespato::GetTransform() const
    {
        return (m_data.tr.top());
    }
    void Feldespato::PushMatrix()
    {
        m_data.tr.push(m_data.tr.top());
    }
    void Feldespato::PopMatrix()
    {
        if (m_data.tr.size() == 1)
            return;
        m_data.tr.pop();
    }

    /* RESOURCE LOADING */
    Model Feldespato::LoadModel(const std::string& path)
    {
        return (m_rm->LoadModel(path));
    }
    Mesh Feldespato::LoadMeshRect()
    {
        return (m_rm->LoadMesh(Mesh::MeshType::RECT));
    }
    Mesh Feldespato::LoadMeshCube()
    {
        return (m_rm->LoadMesh(Mesh::MeshType::CUBE));
    }
    std::shared_ptr<Shader> Feldespato::LoadShader(const std::string& path)
    {
        return (m_rm->LoadShader(path));
    }
    std::shared_ptr<Texture2D> Feldespato::LoadTexture(const std::string& path)
    {
        return (m_rm->LoadImage(path));
    }

    /* INPUT */
    int Feldespato::GetKey(int key)
    {
        return (m_window->GetKey(key));
    }
    FT::vec2 Feldespato::GetMousePosPrev()
    {
        return (m_window->GetMousePosPrev());
    }
    FT::vec2 Feldespato::GetMousePos()
    {
        return (m_window->GetMousePos());
    }
    int Feldespato::GetMouseButton(int button)
    {
        return (m_window->GetMouseButton(button));
    }
}