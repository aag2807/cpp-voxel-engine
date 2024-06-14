#include "Chunk.h"

Chunk::Chunk() : needsUpdate(true)
{
    voxels.resize(CHUNK_SIZE, std::vector<std::vector<Voxel>>(CHUNK_SIZE, std::vector<Voxel>(CHUNK_SIZE)));
}

Voxel Chunk::getVoxel(int x, int y, int z) const
{
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
    {
        return voxels[x][y][z];
    }
    return Voxel{AIR};
}

void Chunk::setVoxel(int x, int y, int z, VoxelType type)
{
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
    {
        voxels[x][y][z] = Voxel{type};
        needsUpdate = true; // Mark the chunk as needing an update
    }
}

void Chunk::update()
{
    if (needsUpdate)
    {
        // Update logic for the chunk if necessary
        needsUpdate = false;
    }
}
