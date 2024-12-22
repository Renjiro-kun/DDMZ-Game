#pragma once
#define WIDTH 640
#define HEIGHT 480
#define TARGET_FPS 60

#include <cstdint>
#include <cmath>

#define CD_DIR "/cd/DDMZ/"
#define RD_DIR "/rd/"
#define DC_SH4

#define GET_ASSET_FROM_CD(path) TextFormat(CD_DIR "%s", path)
#define GET_ASSET_FROM_RD(path) TextFormat(RD_DIR "%s", path)