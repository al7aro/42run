#include "Feldespato.hpp"

namespace FT {
    Feldespato::Feldespato()
    {
        m_window = std::make_shared<Window>("Feldespato Renderer", WINDOW_WIDTH, WINDOW_HEIGHT);
        m_rm = std::make_shared<ResourceManager>(DEFAULT_ASSETS_DIRECTORY"/shaders/410/basic.glsl", DEFAULT_ASSETS_DIRECTORY"/textures/error.png");
        m_data.default_shader = m_rm->GetDefaultShader();
        m_data.default_camera = Camera(Camera::ORTHOGRAPHIC);
        m_data.framebuffer = std::make_shared<FrameBuffer>(WINDOW_WIDTH, WINDOW_HEIGHT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
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
        m_data.tr.push(glm::mat4(1.0));
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
    void Feldespato::BeginLayer(const Camera & cam, std::shared_ptr<Shader> sh, bool tex_mode)
    {
        // TODO: FIX THIS VIEWPORT THING
        if (tex_mode)
        {
            glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            m_data.framebuffer->Enable();
        }
        else
            glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        std::shared_ptr<Layer> layer = std::make_shared<Layer>();
        layer->SetCamera(cam);
        layer->SetShader(sh);
        m_data.ly.push(layer);
    }
    void Feldespato::BeginLayer(bool tex_mode)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), m_data.ly.top()->GetShader(), tex_mode);
    }
    void Feldespato::BeginLayer(std::shared_ptr<Shader> shader, bool tex_mode)
    {
        BeginLayer(m_data.ly.top()->GetCamera(), shader, tex_mode);
    }
    void Feldespato::BeginLayer(const Camera & camera, bool tex_mode)
    {
        BeginLayer(camera, m_data.ly.top()->GetShader(), tex_mode);
    }
    std::shared_ptr<Texture2D> Feldespato::EndLayer()
    {
        if (m_data.ly.size() >= 1)
        {
            m_data.ly.top()->Render();
            m_data.ly.pop();
        }
        m_data.framebuffer->Disable();
        return (m_data.framebuffer->GetFrameColor());
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
    void Feldespato::Translate(glm::vec3 v)
    {
        glm::mat4 tr = glm::translate(glm::mat4(1.0), v);
        m_data.tr.top() *= tr;
    }
    void Feldespato::Scale(glm::vec3 v)
    {
        glm::mat4 sc = glm::scale(glm::mat4(1.0), v);
        m_data.tr.top() *= sc;
    }
    void Feldespato::RotateX(float a)
    {
        glm::mat4 rt = glm::rotate(glm::mat4(1.0), a, glm::vec3(1.0, 0.0, 0.0));
        m_data.tr.top() *= rt;
    }
    void Feldespato::RotateY(float a)
    {
        glm::mat4 rt = glm::rotate(glm::mat4(1.0), a, glm::vec3(0.0, 1.0, 0.0));
        m_data.tr.top() *= rt;
    }
    void Feldespato::RotateZ(float a)
    {
        glm::mat4 rt = glm::rotate(glm::mat4(1.0), a, glm::vec3(0.0, 0.0, 1.0));
        m_data.tr.top() *= rt;
    }
    glm::mat4 Feldespato::GetTransform() const
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
    Mesh Feldespato::LoadMeshCustom(const std::string& path)
    {
        return (m_rm->LoadMesh(path));
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
    glm::vec2 Feldespato::GetMousePosPrev()
    {
        return (m_window->GetMousePosPrev());
    }
    glm::vec2 Feldespato::GetMousePos()
    {
        return (m_window->GetMousePos());
    }
    int Feldespato::GetMouseButton(int button)
    {
        return (m_window->GetMouseButton(button));
    }
}