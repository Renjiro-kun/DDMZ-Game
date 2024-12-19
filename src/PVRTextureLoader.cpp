#include <PVRTextureLoader.h>
#include <kos.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glkos.h>

#define PVR_HDR_SIZE 0x20
#define MAX(x, y) ((x > y) ? x : y)

static GLuint _glGetMipmapLevelCount(GLuint width, GLuint height) {
    return 1 + floor(log2(MAX(width, height)));
}

static GLuint _glGetMipmapDataSize(GLuint width, GLuint height) {
    GLuint size = 0;

    GLuint i = 0;

    for(; i < _glGetMipmapLevelCount(width, height); ++i) {
        size += (width * height * 2);

        if(width > 1) {
            width /= 2;
        }

        if(height > 1) {
            height /= 2;
        }
    }

    return size;
}

Texture2D PVRTextureLoader::LoadTexture(const char* filename, unsigned char isMipMapped, unsigned char glMipMap)
{
    FILE *tex = NULL;
    uint16_t *TEX0 = NULL;
    uint8_t HDR[PVR_HDR_SIZE];
    GLuint texID, texSize, texW, texH, texFormat;

    /* Open the PVR texture file, and get its file size */
    tex = fopen(filename, "rb");

    if(tex == NULL) {
        printf("FILE READ ERROR: %s\n", filename);

        while(1);
    }

    fseek(tex, 0, SEEK_END);
    texSize = ftell(tex) - PVR_HDR_SIZE;
    fseek(tex, 0, SEEK_SET);

    /* Read in the PVR texture file header */
    fread(HDR, 1, PVR_HDR_SIZE, tex);

    /* Extract some information from the PVR texture file header */
    texW = GetTextureWidth(HDR);
    texH = GetTextureHeight(HDR);
    texFormat = GetTextureFormat(HDR);

    /* Allocate Some Memory for the texture. If we are using Open GL to build the MipMap,
       we need to allocate enough space to hold the MipMap texture levels. */
    if(!isMipMapped && glMipMap)
        TEX0 = (uint16_t*)malloc(_glGetMipmapDataSize(texW, texH));
    else
        TEX0 = (uint16_t*)malloc(texSize);

    fread(TEX0, 1, texSize, tex); /* Read in the PVR texture data */

    /* Generate and bind a texture as normal for Open GL */
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    if(glMipMap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    if(texFormat != GL_UNSIGNED_SHORT_5_6_5)
        glCompressedTexImage2DARB(GL_TEXTURE_2D,
                           0,
                           texFormat,
                           texW,
                           texH,
                           0,
                           texSize,
                           TEX0);
    else {
        fprintf(stderr, "%x\n", texFormat);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB,
                     texW, texH,
                     0,
                     GL_RGB,
                     texFormat,
                     TEX0);
        if(!isMipMapped && glMipMap)
            glGenerateMipmapEXT(GL_TEXTURE_2D);
    }

    free(TEX0);

    Texture2D returnTexture {0};
    returnTexture.id = texID;
    returnTexture.width = texW;
    returnTexture.height = texH;
    returnTexture.format = texFormat;
    returnTexture.mipmaps = 1;

    return returnTexture;
}

GLuint PVRTextureLoader::GetTextureWidth(unsigned char* hdr)
{
    return (GLuint)hdr[PVR_HDR_SIZE - 4] | hdr[PVR_HDR_SIZE - 3] << 8;
}

GLuint PVRTextureLoader::GetTextureHeight(unsigned char* hdr)
{
    return (GLuint)hdr[PVR_HDR_SIZE - 2] | hdr[PVR_HDR_SIZE - 1] << 8;
}

GLuint PVRTextureLoader::GetTextureFormat(unsigned char* hdr)
{
    GLuint color = (GLuint)hdr[PVR_HDR_SIZE - 8];
    GLuint format = (GLuint)hdr[PVR_HDR_SIZE - 7];

    GLboolean twiddled = (format == 0x01 || format == 0x02 || format == 0x12);
    GLboolean compressed = (format == 0x10 || format == 0x03 || format == 0x04 || format == 0x11);

    if(compressed) {
        if(twiddled) {
            switch(color) {
                case 0x0: {
                    return GL_COMPRESSED_ARGB_1555_VQ_TWID_KOS;
                } break;
                case 0x01: {
                    return GL_COMPRESSED_RGB_565_VQ_TWID_KOS;
                } break;
                case 0x02: {
                    return GL_COMPRESSED_ARGB_4444_VQ_TWID_KOS;
                }
                break;
                default:
                    fprintf(stderr, "Invalid texture format");
                    return 0;
            }
        } else {
            switch(color) {
                case 0: {
                    return GL_COMPRESSED_ARGB_1555_VQ_KOS;
                } break;
                case 1: {
                    return GL_COMPRESSED_RGB_565_VQ_KOS;
                } break;
                case 2: {
                    return GL_COMPRESSED_ARGB_4444_VQ_KOS;
                }
                break;
                default:
                    fprintf(stderr, "Invalid texture format");
                    return 0;
            }
        }
    } else {
        if(color == 1) {
            return GL_UNSIGNED_SHORT_5_6_5;
        }
        return 0;
    }
}