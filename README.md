<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/768px-42_Logo.svg.png" align="right" width=150 style="margin:20px"/>

# <a href="https://play.google.com/store/apps/details?id=com.imangi.templerun&hl=en&pli=1"><img src="https://upload.wikimedia.org/wikipedia/it/9/9d/Temple_run_app.png" align="center" width=130 style="margin:0px"/></a> 42run <!-- omit from toc -->


<em>(Basic) Temple run <a href="https://play.google.com/store/apps/details?id=com.imangi.templerun&hl=en&pli=1"><img src="https://upload.wikimedia.org/wikipedia/it/9/9d/Temple_run_app.png" align="center" width=30/></h1></a> clone made from scratch using <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a>.</em>

---

## Table of Contents <!-- omit from toc -->
- [Why ❓](#why-)
- [How was it made 🧠](#how-was-it-made-)
- [The ENGINE ](#the-engine-)
  - [External Libraries](#external-libraries)
- [The GAME](#the-game)
- [TODO 🤯](#todo-)
- [Screenshot](#screenshot)


## Why ❓

42run is a project from <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/768px-42_Logo.svg.png" width=30/> <em>Outter Core</em> curriculm, one of the basis of the **Computer Graphics** <img src="https://www.wolframcloud.com/obj/resourcesystem/images/f2d/f2dcb501-fd59-4986-b598-2f30ac56d0ac/6009562e6fbfd7a5.png" width=30/> branch. The project introduces students to real-time rendering and game development fundamentals using GPU-based techniques.

## How was it made 🧠

It was built from scratch with <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a> on <a href="https://en.wikipedia.org/wiki/C%2B%2B"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1200px-ISO_C%2B%2B_Logo.svg.png" align="center" width=25/></a>
The project consist of two parts:
- A lightweight game engine I called **Feldespato** <img src="https://png.pngtree.com/png-vector/20220603/ourmid/pngtree-one-grey-rock-chemical-illustration-feldspar-vector-png-image_36952800.png" width=30>
- A demo game built on top of **Feldespato** <img src="https://png.pngtree.com/png-vector/20220603/ourmid/pngtree-one-grey-rock-chemical-illustration-feldspar-vector-png-image_36952800.png" width=30> engine

## The ENGINE <img src="https://png.pngtree.com/png-vector/20220603/ourmid/pngtree-one-grey-rock-chemical-illustration-feldspar-vector-png-image_36952800.png" width=40>

**Feldespato** <img src="https://png.pngtree.com/png-vector/20220603/ourmid/pngtree-one-grey-rock-chemical-illustration-feldspar-vector-png-image_36952800.png" width=30> provides a clean abstraction over <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a>, focusing on simplicity and usability. It is designed around the principle of **One DrawCall per Object**, making it easy to manage rendering pipelines.
Example of use:
```c++
Feldespato fdp;

fdp.BeginRenderPass(camera, shader, render_to_texture);
  fdp.Draw(EpicModel, Transform()); // Model loading with ANIMATION support
  fdp.Rect(Transform(0.0, 0.0, 0.0));
  fdp.Cube();
texture = fdp.EndRenderPass();
```

### External Libraries

- <a href="https://www.glfw.org/"><img src="https://www.glfw.org/img/favicon/favicon-196x196.png" width=30 align="center"/> **GLFW**</a> (windows and inputs)
- <a href="https://github.com/nothings/stb">**STB**</a> (image loading)
- <a href="https://glad.dav1d.de/"> **GLAD**</a> (manage <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a> extensions)

## The GAME

**42run** <a href="https://play.google.com/store/apps/details?id=com.imangi.templerun&hl=en&pli=1"><img src="https://upload.wikimedia.org/wikipedia/it/9/9d/Temple_run_app.png" align="center" width=25/></a> uses **Feldespato** <img src="https://png.pngtree.com/png-vector/20220603/ourmid/pngtree-one-grey-rock-chemical-illustration-feldspar-vector-png-image_36952800.png" width=30> to work.
The game is a VERY SIMPLE clone of epic **Temple Run** <a href="https://play.google.com/store/apps/details?id=com.imangi.templerun&hl=en&pli=1"><img src="https://upload.wikimedia.org/wikipedia/it/9/9d/Temple_run_app.png" align="center" width=25/></a> where:
- Auto-forward movement
- Player can jump and turn at intersections
- The map is pregenerated and obstacles are placed randomly.

## TODO 🤯
- [ ] Add props to FORWARD floor
- [ ] Add new models for collectables and obstacles

---

## Screenshot
I'll post some images when it's finished, but for now, here are my dog (FILLO 🐕) and cat (GATO 🐈) chilling after a hard day of work.

<img src="https://i.imgur.com/3N4LOi5.png" width=400>
