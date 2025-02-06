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
**Rendering Optimization:**   
Currently, the check to only draw visible faces doesnt work between chunks, so the chunk borders have invisible faces rendered.
**Chunk Generation:**   
My chunk generation has an error of only drawing half the chunks in a random fasion. I think this is to do with the generation of the VBO and VAO for each chunk, but I will fix this next.

## Next Steps
- Implement **greedy meshing** to reduce overdraw  
- Fix **chunk generation**  
- Add **basic physics** and **gravity** for player movement  
- Experiment with **ray tracing** so I can draw smaller and more voxels with a high resolution without a large performance loss  

## Installation and Running
1. Clone the repository:
   ```sh
   git clone https://github.com/thomasewhite/opengl-voxel.git
2. Install extra dependancies (GLFW, GLM)
3. Make the project.

## Note
This has only been compiled for arch linux, so you might run into issues compiling for windows, and apple computers require a few extra lines in the glfw initialization, I will add these at some point in the future.