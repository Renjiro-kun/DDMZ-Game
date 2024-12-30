#pragma once

class EnvironmentController
{
public:
    void OnActivate();
    void OnDeactivate();

    void Enable();
    void Disable();

    void SetFogColor(float* clr);
    void SetLightColor(float* clr);
    void SetFogDepth(float depth);
};