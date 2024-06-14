#ifndef VOXELENGINE_RENDERER_H
#define VOXELENGINE_RENDERER_H

#include "Chunk.h"

class Renderer
{
public:
    void renderChunk(const Chunk &chunk);

private:
    void renderVoxel(int x, int y, int z, const Voxel &voxel);
};


#endif //VOXELENGINE_RENDERER_H
