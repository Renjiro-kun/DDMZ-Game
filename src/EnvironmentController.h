#pragma once
#include <raylib/raylib.h>

class EnvironmentController
{
public:
    void OnActivate();
    void OnDeactivate();

    void Enable();
    void Disable();

    void SetFogColor(Color clr);
    void SetLightColor(Color clr);
};