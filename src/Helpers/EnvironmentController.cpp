#include <Defines.h>
#include <Helpers/EnvironmentController.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>

void EnvironmentController::OnActivate()
{
    
    GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; /* Fog Color */

    glFogi(GL_FOG_MODE, GL_EXP2);               /* Fog Mode */
    glFogfv(GL_FOG_COLOR, fogColor);            /* Set Fog Color */
    glFogf(GL_FOG_DENSITY, 0.35f);              /* How Dense The Fog is */
    glHint(GL_FOG_HINT, GL_DONT_CARE);          /* Fog Hint Value */
    glFogf(GL_FOG_START, 0.0f);                 /* Fog Start Depth */
    glFogf(GL_FOG_END, 5.f);                   /* Fog End Depth */
}

void EnvironmentController::OnDeactivate()
{

}

void EnvironmentController::SetFogColor(float* clr)
{
    glFogfv(GL_FOG_COLOR, clr);
}

void EnvironmentController::SetLightColor(float* clr)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, clr);
}

void EnvironmentController::SetFogDepth(float depth)
{
    glFogf(GL_FOG_DENSITY, 1.f - (depth*0.1f));
}

void EnvironmentController::Enable()
{
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void EnvironmentController::Disable()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}