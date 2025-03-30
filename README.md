<img src="https://www.wolframcloud.com/obj/resourcesystem/images/f2d/f2dcb501-fd59-4986-b598-2f30ac56d0ac/6009562e6fbfd7a5.png" align="right" width=150 style="margin:20px"/>

# <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=150 style="margin:0px"/></a> Template


<em>Simple <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a> template using <a href=""><img src="https://premake.github.io/img/premake-logo.png" align="center" width=25/> **premake5**</a>.</em>

---

# Dependencies 📦

- <a href="https://github.com/assimp/assimp"><img src="https://camo.githubusercontent.com/42e0ad409257f3532d48a9ba1c251fe486854891850f8d5b6b82e3cbf16c1336/687474703a2f2f692e696d6775722e636f6d2f757765686f64722e706e67" align="center" width=25/> **ASSIMP**</a>
- <a href="https://www.glfw.org/"><img src="https://www.glfw.org/img/favicon/favicon-196x196.png" width=30 align="center"/> **GLFW**</a>
- <a href="https://github.com/g-truc/glm"><img src="https://upload.wikimedia.org/wikipedia/commons/5/5b/GLM_logo.png" align="center" width=50/> **GLM**</a>
- <a href="https://github.com/ocornut/imgui"><img src="https://png.pngtree.com/png-vector/20220917/ourmid/pngtree-word-dear-vector-decorative-zentangle-object-vector-illustration-hand-vector-png-image_39275940.png" align="center" width=50/> **ImGui**</a>
- <a href="https://github.com/nothings/stb">**STB**</a>
- <a href="https://glad.dav1d.de/"> **GLAD**</a>

# How To Use 🧠

- Create a repo from this template 🪧
- Clone the repo on your machine 🖨️
```sh
git clone [repo-url]
```
- Init the submodules 🎬
```sh
git submodule init
git submodule update
```
- Build the project using <a href=""><img src="https://premake.github.io/img/premake-logo.png" align="center" width=25/> **premake5**</a>
   - Windows 🪟
```sh
.\scripts\premake5.exe vs2022
```

- <a href=""><img src="https://cdn-icons-png.flaticon.com/256/8819/8819105.png" align="center" width=200/></a>

# QILTBA (Questions I'd like to be asked) 🤙😞

- Why `premake5`?
  - Simple: `CMake` is ugly 🤮
- Why `in-source` build?
  - I don't really thing this is `in-source` building 🤬

---

# TODO 🤯
- [ ] In general, work on the `premake5` script to make it **better**
- [ ] Create `premake5` configurations
- [ ] Assimp config depends on the system (maybe)
- [ ] Glad version should change depending on the system