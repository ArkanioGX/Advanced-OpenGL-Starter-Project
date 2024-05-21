#pragma once
#include "TessellationScene.h"
#include <Matrix4.h>
#include "Assets.h"

class BeachScene : public TessellationScene
{
public:
    BeachScene();
    ~BeachScene() {}
    void SetupScene() override;
    void UpdateScene() override;
    void HandleInputs(SDL_Event& e) override;
    

private:
    void LoadShaders();
    void CreateShaderPrograms() override;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;
    float dmapDepth;
    bool isFogEnabled;

    GLuint texDisplacement;
    GLuint sandColor;
    GLuint seaColor;
    GLuint seaDP;
    bool isDisplacementEnabled;
    bool wireframe;
    bool paused;

    float totalTime;
    float t, r, h;

    Shader s_sandVertex, s_sandFrag, s_sandTessControl, s_sandTessEval;
    ShaderProgram sp_sand;

    Shader s_seaVertex, s_seaFrag, s_seaTessControl, s_seaTessEval;
    ShaderProgram sp_sea;
};

