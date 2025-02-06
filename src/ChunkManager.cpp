#include "../include/ChunkManager.h"
#include <cmath>

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::updateChunks(const Camera &camera)
{
    ThreadPool pool(4);

    int playerChunkX = static_cast<int>(std::floor(camera.Position.x / chunkSize));
    int playerChunkZ = static_cast<int>(std::floor(camera.Position.z / chunkSize));

    // Load chunks in the render distance
    for (int dx = -renderDistance; dx <= renderDistance; ++dx)
    {
        for (int dz = -renderDistance; dz <= renderDistance; ++dz)
        {
            int chunkX = playerChunkX + dx;
            int chunkZ = playerChunkZ + dz;

            std::pair<int, int> chunkPos = {chunkX * chunkSize, chunkZ * chunkSize};

            if (chunkMap.find(chunkPos) == chunkMap.end())
            {
                pool.enqueue([this, chunkX, chunkZ]()
                             {
                                 generateChunk(chunkX, chunkZ);
                             });
            }
        }
    }
    
    unloadDistantChunks(playerChunkX, playerChunkZ);
}


void ChunkManager::generateChunk(int x, int z)
{
    chunkMap[{x * chunkSize, z * chunkSize}] = Chunk(x * chunkSize, z * chunkSize, chunkSize);
}

void ChunkManager::unloadDistantChunks(int playerChunkX, int playerChunkZ)
{
    std::vector<std::pair<int, int>> chunksToRemove;

    for (const auto &[pos, chunk] : chunkMap)
    {
        int chunkX = pos.first / chunkSize;
        int chunkZ = pos.second / chunkSize;

        int distX = abs(chunkX - playerChunkX);
        int distZ = abs(chunkZ - playerChunkZ);

        if (distX > renderDistance || distZ > renderDistance)
        {
            chunksToRemove.push_back(pos);
        }
    }

    for (const auto &pos : chunksToRemove)
    {
        chunkMap.erase(pos);
    }
}

void ChunkManager::renderChunks()
{
    for (auto &[pos, chunk] : chunkMap)
    {
        chunk.render();
    }
}
