#include "Utils.h"

void drawText(const std::string &text, float x, float y, float r, float g, float b)
{
    glColor3f(r, g, b); // Set the text color
    glRasterPos2f(x, y);
    for (char c: text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
