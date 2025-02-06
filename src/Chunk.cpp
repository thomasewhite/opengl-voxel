#include "../include/Chunk.h"

float topVertices[] = {
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom left
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // Bottom right
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Top left

    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Bottom right
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Top left
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f   // Top right
};

float bottomVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // Bottom left
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,  // Bottom right
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  // Top left

    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, // Bottom right
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // Top left
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f   // Top right
};

float leftVertices[] = {
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // Bottom left
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,  // Bottom right
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  // Top left

    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, // Bottom right
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // Top left
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f   // Top right
};

float rightVertices[] = {
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Bottom left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // Bottom right
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // Top left

    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Bottom right
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Top left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f   // Top right
};

float backVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f};

float frontVertices[] = {
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

Chunk::Chunk() : chunkX(0), chunkZ(0) {}

Chunk::Chunk(int x, int z, int size)
    : chunkX(x), chunkZ(z), size(size)
{
    initialize();
}

void Chunk::initializeNeighbors(std::map<std::pair<int, int>, Chunk> &chunkMap)
{
    // Now that chunkMap is populated, initialize neighbors
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dz = -1; dz <= 1; dz++)
        {
            if (dx == 0 && dz == 0)
                continue;

            int neighborX = chunkX + dx * 32;
            int neighborZ = chunkZ + dz * 32;

            auto it = chunkMap.find({neighborX, neighborZ});
            if (it != chunkMap.end())
            {
                // Initialize neighbor
                neighbors.push_back(&it->second);
            }
        }
    }

    std::cout << "Neighbors for Chunk (" << chunkX << ", " << chunkZ << "):\n";
    for (const auto &neighbor : neighbors)
    {
        std::cout << "\tNeighbor Chunk (" << neighbor->chunkX << ", " << neighbor->chunkZ << ")\n";
    }
}

glm::vec3 Chunk::generateRandomColor(int colour)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if (colour == 0)
    {
        std::uniform_real_distribution<> greenDis(0.6f, 0.9f);
        std::uniform_real_distribution<> redDis(0.2f, 0.4f);
        std::uniform_real_distribution<> blueDis(0.2f, 0.4f);
        float r = redDis(gen);
        float g = greenDis(gen);
        float b = blueDis(gen);

        return glm::vec3(r, g, b);
    }
    else if (colour == 1)
    {
        std::uniform_real_distribution<> greenDis(0.3f, 0.35f);
        std::uniform_real_distribution<> redDis(0.3f, 0.3f);
        std::uniform_real_distribution<> blueDis(0.3f, 0.4f);
        float r = redDis(gen);
        float g = greenDis(gen);
        float b = blueDis(gen);

        return glm::vec3(r, g, b);
    }

    return glm::vec3(0.f, 0.f, 0.f);
}

bool Chunk::isBlockAt(int x, int y, int z) const
{
    // Check if the coordinates are within the bounds of the current chunk
    if (x >= 0 && x < size &&
        y >= 0 && y < height &&
        z >= 0 && z < size)
    {
        // Block is within the current chunk
        return blocks[x][y][z] != 0;
    }

    // Coordinates are outside the current chunk, check neighbors
    int checkX = x, checkZ = z;

    // If x is out of bounds (negative), check the previous chunk (left)
    if (x < 0)
    {
        checkX = size - 1; // Last block in the previous chunk
    }
    // If x is out of bounds (greater than size), check the next chunk (right)
    else if (x >= size)
    {
        checkX = 0; // First block in the next chunk
    }

    // If z is out of bounds (negative), check the chunk behind (bottom)
    if (z < 0)
    {
        checkZ = size - 1; // Last block in the previous chunk
    }
    // If z is out of bounds (greater than size), check the chunk ahead (top)
    else if (z >= size)
    {
        checkZ = 0; // First block in the next chunk
    }

    // Now look at neighbors in the correct direction
    for (const auto &neighbor : neighbors)
    {
        // Calculate the offset to move the coordinates into the neighbor's chunk space
        int neighborX = checkX - (chunkX * size); // Adjust for chunkX offset
        int neighborZ = checkZ - (chunkZ * size); // Adjust for chunkZ offset

        // Check if the neighboring chunk contains a block at the calculated coordinates
        if (neighbor->isBlockAt(neighborX, y, neighborZ))
        {
            return true; // Block found in a neighboring chunk
        }
    }

    // If the block was not found in the current chunk or any neighboring chunk
    return false;
}

void Chunk::addFaceToBuffer(std::vector<float> &vertices, const float *faces, const glm::vec3 blockPosition)
{
    float heightThreshold = 64.0f;

    glm::vec3 randomColor;
    if (blockPosition.y < heightThreshold)
    {
        randomColor = generateRandomColor(1);
    }
    else
    {
        randomColor = generateRandomColor(0);
    }

    for (int k = 0; k < 6; k++)
    {
        vertices.push_back(faces[k * 6] + blockPosition.x + chunkX);
        vertices.push_back(faces[k * 6 + 1] + blockPosition.y);
        vertices.push_back(faces[k * 6 + 2] + blockPosition.z + chunkZ);

        vertices.push_back(faces[k * 6 + 3]);
        vertices.push_back(faces[k * 6 + 4]);
        vertices.push_back(faces[k * 6 + 5]);

        vertices.push_back(randomColor.r);
        vertices.push_back(randomColor.g);
        vertices.push_back(randomColor.b);

        verticesSize += 9;
    }
}

void Chunk::generateTerrain()
{
    FastNoise noise;
    noise.SetNoiseType(FastNoise::Simplex); // Use Simplex noise for overall terrain
    noise.SetFrequency(0.003f);             // Base frequency
    noise.SetSeed(41);                      // Seed for reproducibility

    FastNoise detailNoise;
    detailNoise.SetNoiseType(FastNoise::Perlin); // Use Perlin noise for small details
    detailNoise.SetFrequency(0.02f);             // Higher frequency for details
    detailNoise.SetSeed(41);

    for (int x = 0; x < size; ++x)
    {
        for (int z = 0; z < size; ++z)
        {
            if (noiseCache[x][z] == 0.0f)
            {
                noiseCache[x][z] = noise.GetNoise(x + chunkX, z + chunkZ);
            }
            if (detailNoiseCache[x][z] == 0.0f)
            {
                detailNoiseCache[x][z] = detailNoise.GetNoise(x + chunkX, z + chunkZ);
            }

            float baseNoiseValue = noiseCache[x][z];

            float detailNoiseValue = pow(detailNoiseCache[x][z], 3);

            float finalHeight = baseNoiseValue + detailNoiseValue;
            int maxHeight = static_cast<int>((finalHeight + 1.0f) * 0.5f * height);

            for (int y = 0; y < height; ++y)
            {
                if (y < maxHeight || y == 0)
                {
                    blocks[x][y][z] = 1;
                }
                else
                {
                    blocks[x][y][z] = 0;
                }
            }
        }
    }
}

void Chunk::initialize()
{
    blocks = std::vector<std::vector<std::vector<int>>>(
        size, std::vector<std::vector<int>>(
                  height, std::vector<int>(size, 0)));

    noiseCache = std::vector<std::vector<float>>(size, std::vector<float>(size, 0.0f));
    detailNoiseCache = std::vector<std::vector<float>>(size, std::vector<float>(size, 0.0f));

    generateTerrain();

    batchVertices.reserve(size * height * size * 6 * 6); // Reserve space for faces

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int z = 0; z < size; z++)
            {
                if (blocks[x][y][z] != 0) // Only process solid blocks
                {
                    // Check each face only if it's exposed
                    if (!isBlockAt(x, y, z + 1)) // Front face
                        addFaceToBuffer(batchVertices, frontVertices, glm::vec3(x, y, z));
                    if (!isBlockAt(x, y, z - 1)) // Back face
                        addFaceToBuffer(batchVertices, backVertices, glm::vec3(x, y, z));
                    if (!isBlockAt(x - 1, y, z)) // Left face
                        addFaceToBuffer(batchVertices, leftVertices, glm::vec3(x, y, z));
                    if (!isBlockAt(x + 1, y, z)) // Right face
                        addFaceToBuffer(batchVertices, rightVertices, glm::vec3(x, y, z));
                    if (!isBlockAt(x, y + 1, z)) // Top face
                        addFaceToBuffer(batchVertices, topVertices, glm::vec3(x, y, z));
                    if (!isBlockAt(x, y - 1, z)) // Bottom face
                        addFaceToBuffer(batchVertices, bottomVertices, glm::vec3(x, y, z));
                }
            }
        }
    }
}

void Chunk::render()
{
    if (VBO == 0) // If VBO hasn't been initialized yet
    {
        // Ensure this is on the main thread
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Ensure vertex data is available
        if (!batchVertices.empty()) {
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * batchVertices.size(), batchVertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
        }

        glBindVertexArray(0);
    }
    // Only render if VBO is initialized
    if (VBO != 0)
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, verticesSize);
        glBindVertexArray(0);
    }
}


Chunk::~Chunk()
{
}