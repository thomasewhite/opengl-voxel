#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/FastNoise.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <map>

class Chunk
{
public:
    Chunk();
    Chunk(int x, int z, int size);
    void initializeNeighbors(std::map<std::pair<int, int>, Chunk> &chunkMap);
    void render();
    bool isBlockAt(int x, int y, int z) const;
    ~Chunk();

    int chunkX, chunkZ;
    std::vector<Chunk*> neighbors;
    unsigned int size = 10;
    unsigned int height = 128;

private:
    void initialize();
    void generateTerrain();
    void addFaceToBuffer(std::vector<float> &vertices, const float *faces, const glm::vec3 blockPosition);
    glm::vec3 generateRandomColor(int colour);

    const std::map<std::pair<int, int>, Chunk> *chunkMap;
    std::vector<float> batchVertices;
    unsigned int VBO, VAO;
    std::vector<std::vector<std::vector<int>>> blocks;
    std::vector<std::vector<float>> noiseCache;
    std::vector<std::vector<float>> detailNoiseCache;
    unsigned int verticesSize = 0;
};

#endif