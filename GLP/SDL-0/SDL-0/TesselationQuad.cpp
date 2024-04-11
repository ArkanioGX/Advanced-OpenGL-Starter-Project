#include "TesselationQuad.h"

const bool ENABLE_GEOMETRY_SHADER = false;

void TessellationQuadScene::LoadShaders()
{
	m_vertexShader.LoadFrom("tessQuadVertex.shader", VERTEX);
	m_fragmentShader.LoadFrom("tessellationFragment.shader", FRAGMENT);
	m_tessControlShader.LoadFrom("tessQuadControl.shader", TESSELLATION_CONTROL);
	m_tessEvalShader.LoadFrom("tessQuadEval.shader", TESSELLATION_EVALUATION);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TessellationQuadScene::UpdateScene()
{
	m_shaderProgram.Use();

	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue) / 2.0f);

	int itessLevelLocation = glGetUniformLocation(m_shaderProgram.GetID(), "inTessLevel");
	int otessLevelLocation = glGetUniformLocation(m_shaderProgram.GetID(), "outTessLevel");
	glUniform1f(itessLevelLocation, fmaxf(sinusoidValue * 6,1));
	glUniform1f(otessLevelLocation, fmaxf(sinusoidValue * 10,1));


	glPointSize(5.0f);
	glDrawArrays(GL_PATCHES, 0, 4);
}

TessellationQuadScene::TessellationQuadScene()
{
}
