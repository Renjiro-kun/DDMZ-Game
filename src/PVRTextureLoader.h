#pragma once
#include <raylib/raylib.h>
#include <GL/gl.h>

class PVRTextureLoader
{
public:
    static Texture2D LoadTexture(const char* filename, unsigned char isMipMapped, unsigned char glMipMap);
private:
    static GLuint GetTextureWidth(unsigned char* hdr);
    static GLuint GetTextureHeight(unsigned char* hdr);
    static GLuint GetTextureFormat(unsigned char* hdr);
};