# opengl-voxel

This is a **voxel engine** written in **C++** with **OpenGL**. It's not a finished product but rather a personal project to explore **graphics programming**, **efficient rendering**, and **game engine architecture**.

## Why I Started This Project
I wanted to challenge myself to build a voxel-based world from scratch to:
- Improve my **C++ skills** and code organization.
- Learn more about **OpenGL**, shaders, and rendering optimizations.
- Experiment with **chunk-based terrain generation** and dynamic loading.
- Face and solve **real-world performance problems** in game development.

## Current Features
- Basic chunk-based rendering  
- Infinite terrain generation (in theory)  
- Simple camera movement

## Challenges & Problems Encountered
- **Chunk Face Culling Issue:** The check to only draw visible faces doesn’t work between chunks, so the chunk borders have invisible faces rendered.
- **Randomly Missing Chunks:** Only half the chunks are drawn in a seemingly random pattern. I suspect this is due to an issue with generating and binding the VBO and VAO for each chunk.
  
### **Planned Fixes:**
- Debugging with `glGetError()` and verifying correct VBO updates.
- Ensuring VAOs are bound properly before updating buffers.

## Next Steps
### **Short-Term Goals** (Immediate Fixes)
- Fix chunk generation bug (random missing chunks)  
- Implement proper face culling between chunks  

### **Long-Term Goals** (Bigger Features)
- **Physics & Gravity** – Implement proper player movement  
- **Ray Tracing Experimentation** – Try rendering smaller, more detailed voxels with better performance  
- **Basic Interactions** – Allow adding/removing voxels  

## Installation and Running
1. Clone the repository:
   ```sh
   git clone https://github.com/thomasewhite/opengl-voxel.git
2. Install dependencies e.g. for Arch Linux this is:
    ```sh
    sudo pacman -S glfw glm
3. Compile it:
    ```sh
    mkdir build && cd build
    cmake ..
    make
4. Run the executable:
    ```sh
    ./Voxel

## Notes
- Linux: This has only been compiled and tested on Arch Linux.
- Windows: You might run into issues compiling—support coming soon.
- MacOS: Requires extra glfw initialization lines, which I will add later.