# Compiler and flags
CXX = g++
CXXFLAGS = -I/usr/local/include -Iexternal/glad/include
LDFLAGS = -L/usr/local/lib -lglfw -ldl -lpthread -lX11 -lXrandr -lXi -lXxf86vm -lXcursor -lGL -lm

# Source files
SRC = src/main.cpp external/glad/src/glad.c src/Chunk.cpp src/FastNoise.cpp src/ChunkManager.cpp src/WindowManager.cpp
TARGET = Voxel

# Build rules
all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
