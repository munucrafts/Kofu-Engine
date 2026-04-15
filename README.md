<p align="center">
  <h1 align="center">KOFU ENGINE</h1>
</p>

<p align="center">
  <img src="KofuEngine/assets/others/Logo.png" width="260" alt="Kofu Engine Logo">
</p>

<h3 align="center">
  A 3D Hobby Graphics Engine built with C++ and OpenGL 4.6.
</h3>

## Features 🤖

* **Core Framework:** GLFW-based windowing and Glad-based OpenGL 4.6 loading.
* **Rendering Architecture:** Custom abstractions for Vertex Buffers (VBO), Index Buffers (EBO), Vertex Arrays (VAO), and Framebuffers (FBO).
* **Scene Management:** Supports Static Meshes, Instanced Static Meshes, Quads, Lights, Skyboxes, and Shadow Maps.
* **View Modes:** Toggle between LIT, UNLIT, DEPTH, and NORMAL visualization modes.
* **Anti-aliasing:** Multi-Sample Anti-Aliasing (MSAA) support for improved visual fidelity.
* **Asset Pipeline:** Custom GLTF mesh parser using **tinygltf** and texture loading via **stb_image**.
* **Lighting & Shadows:** Directional, Point, and Spot light support with integrated Shadow Mapping.
* **Skybox:** Environment implementation using Cubemap textures.
* **Axes Grid:** Quad-based infinite grid with X/Z axis visualization.
* **Shaders:** Dedicated Shader class for managing Vertex, Fragment, and Geometry GLSL shaders.
* **Camera System:** Perspective camera featuring smooth mouse-look and standard WASDQE movement controls.
* **Audio Engine:** OpenAL-based spatial audio with Source and Listener component architecture.
* **User Interface:** Comprehensive editor suite built with **Dear ImGui**:
    * **Primary Panels:** Viewport, Scene Outliner, Engine Statistics (FPS, Draw calls, Triangle count), and Settings.
    * **Detail Panels:** Transform, Mesh, Light, and Camera property editors.
* **Gizmos:** Integrated world-direction gizmo for intuitive viewport navigation.

## Axis Convention 🧭

* **X** → Left to Right
* **Y** → Bottom to Top
* **Z** → Screen to Eye

## Tech Stack 🛠️

* **Language:** C++ 20
* **Graphics API:** OpenGL 4.6 (Core Profile)
* **Libraries:** Glad, GLFW, GLM, ImGui, TinyGltf, JsonParser, OpenAL, StbImage

## Screenshots 🖼️

<p align="center">
  <img src="KofuEngine/assets/others/Medieval.png" width="48%" />
  <img src="KofuEngine/assets/others/Ruel.png" width="48%" />
  <img src="KofuEngine/assets/others/Normal.png" width="48%" />
  <img src="KofuEngine/assets/others/Selection.png" width="48%" />
</p>

## Prerequisites ⚙️

Ensure the following tools are installed before building:

### 1. Visual Studio 2022

- Install the **Desktop development with C++** workload

### 2. Premake5 (v5.0.0-beta7)

- Download from: `https://premake.github.io/download/`
- Extract the archive
- Place `premake5.exe` in: `Kofu-Engine/vendor/premake/`

## How to Build 🔨

- Clone the Repo: `git clone https://github.com/munucrafts/Kofu-Engine.git`
- Navigate to: `Kofu-Engine` → `Scripts`
- Run: `Setup.bat`
- `Setup.bat` runs `vendor/premake/premake5.exe vs2022`
- `KofuEngine.sln` gets created
