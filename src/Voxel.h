#ifndef VOXELENGINE_VOXEL_H
#define VOXELENGINE_VOXEL_H

enum VoxelType
{
    AIR,
    DIRT,
    STONE,
    GRASS,
    SAND,
    WATER,
};

struct Voxel
{
    VoxelType type;
    explicit Voxel(VoxelType t = AIR) : type(t)
    {}
};

#endif //VOXELENGINE_VOXEL_H
