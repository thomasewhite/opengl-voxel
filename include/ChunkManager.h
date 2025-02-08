#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>
#include <utility>
#include <iostream>
#include <vector>
#include <cmath>

#include "../include/ThreadPool.h"
#include "../include/Chunk.h"
#include "../include/Camera.h"

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

class ChunkManager
{
public:
    ChunkManager();
    ~ChunkManager();

    void updateChunks(const Camera &camera);
    void renderChunks();

private:
    std::unordered_map<std::pair<int, int>, Chunk, pair_hash> chunkMap;
    const int chunkSize = 32;
    const int renderDistance = 4;
    int playerChunkX, playerChunkZ;

    void generateChunk(int x, int z);
    void unloadDistantChunks(int playerChunkX, int playerChunkZ);
};

#endif
