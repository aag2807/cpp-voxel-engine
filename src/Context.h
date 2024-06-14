#ifndef VOXELENGINE_CONTEXT_H
#define VOXELENGINE_CONTEXT_H

#include "Chunk.h"
#include "Camera.h"

struct Context
{
    Chunk chunk;
    Camera camera;
    VoxelType currentBlockType;

    Context() : currentBlockType(DIRT)
    {}
};

#endif //VOXELENGINE_CONTEXT_H
