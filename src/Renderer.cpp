#include "Renderer.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void Renderer::renderChunk(const Chunk &chunk)
{
    for (int x = 0; x < CHUNK_SIZE; ++x)
    {
        for (int y = 0; y < CHUNK_SIZE; ++y)
        {
            for (int z = 0; z < CHUNK_SIZE; ++z)
            {
                Voxel voxel = chunk.getVoxel(x, y, z);
                if (voxel.type != AIR)
                {
                    renderVoxel(x, y, z, voxel);
                }
            }
        }
    }
}

void Renderer::renderVoxel(int x, int y, int z, const Voxel &voxel)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    switch (voxel.type)
    {
        case DIRT:
            glColor3f(0.59f, 0.29f, 0.0f); // Brown color for dirt
            break;
        case STONE:
            glColor3f(0.5f, 0.5f, 0.5f); // Grey color for stone
            break;
        case GRASS:
            glColor3f(0.0f, 1.0f, 0.0f); // Green color for grass
            break;
        case SAND:
            glColor3f(0.94f, 0.87f, 0.70f); // Sand color
            break;
        case WATER:
            glColor3f(0.0f, 0.0f, 1.0f); // Blue color for water
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f); // White color for default
            break;
    }

    glutSolidCube(1.0f);
    glPopMatrix();
}
