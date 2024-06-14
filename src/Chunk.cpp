#include "Chunk.h"

Chunk::Chunk()
{
    voxels.resize(CHUNK_SIZE, std::vector<std::vector<Voxel>>(CHUNK_SIZE, std::vector<Voxel>(CHUNK_SIZE)));
}

Voxel Chunk::getVoxel(int x, int y, int z) const
{
    return voxels[x][y][z];
}

void Chunk::setVoxel(int x, int y, int z, VoxelType type)
{
    voxels[x][y][z] = Voxel(type);
}
