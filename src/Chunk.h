#ifndef VOXELENGINE_CHUNK_H
#define VOXELENGINE_CHUNK_H

#include <iostream>
#include <vector>
#include "Voxel.h"

using VoxelCollection = std::vector<std::vector<std::vector<Voxel>>>;

const int CHUNK_SIZE = 16;

class Chunk
{
public:
    Chunk();

    Voxel getVoxel(int x, int y, int z) const;

    void setVoxel(int x, int y, int z, VoxelType type);

private:
    VoxelCollection voxels;
};


#endif //VOXELENGINE_CHUNK_H
