#include "BeachScene.h"

BeachScene::BeachScene() :
	dmapDepth(1.5f), isFogEnabled(true), isDisplacementEnabled(true),
	wireframe(false), paused(false), totalTime(0) {}


void BeachScene::LoadShaders() {
	s_sandVertex.LoadFrom("beachSandVertex.shader", VERTEX);
	s_sandFrag.LoadFrom("beachSandFragment.shader", FRAGMENT);
	s_sandTessControl.LoadFrom("beachSandTessControl.shader", TESSELLATION_CONTROL);
	s_sandTessEval.LoadFrom("beachSandTessEvaluation.shader", TESSELLATION_EVALUATION);
	
	s_seaVertex.LoadFrom("beachSeaVertex.shader", VERTEX);
	s_seaFrag.LoadFrom("beachSeaFragment.shader", FRAGMENT);
	s_seaTessControl.LoadFrom("beachSeaTessControl.shader", TESSELLATION_CONTROL);
	s_seaTessEval.LoadFrom("beachSeaTessEvaluation.shader", TESSELLATION_EVALUATION);
}

void BeachScene::CreateShaderPrograms() {
	sp_sand.Compose(
		vector<Shader*>{
		&s_sandVertex,
			& s_sandFrag,
			& s_sandTessControl,
			& s_sandTessEval
	});
	
	sp_sea.Compose(
		vector<Shader*>{
		&s_seaVertex,
			& s_seaFrag,
			& s_seaTessControl,
			& s_seaTessEval
	});
}

void BeachScene::SetupScene() {
	LoadShaders();
	CreateShaderPrograms();

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glPatchParameteri(GL_PATCH_VERTICES, 4);

	glEnable(GL_CULL_FACE);
	//TEXTURES
	glActiveTexture(GL_TEXTURE1);
	Assets::loadTexture("./Textures/sandDP.jpg", "terragen1");
	texDisplacement = Assets::getTexture("terragen1").id;
	glBindTexture(GL_TEXTURE_2D, texDisplacement);

	glActiveTexture(GL_TEXTURE2);
	Assets::loadTexture("./Textures/sandColor.jpg", "terragen_color");
	sandColor = Assets::getTexture("terragen_color").id;
	glBindTexture(GL_TEXTURE_2D, sandColor);

	glActiveTexture(GL_TEXTURE3);
	Assets::loadTexture("./Textures/SeaTexture.jpg", "water_color");
	seaColor = Assets::getTexture("water_color").id;
	glBindTexture(GL_TEXTURE_2D, seaColor);

	glActiveTexture(GL_TEXTURE4);
	Assets::loadTexture("./Textures/voronoise.png", "water_dp");
	seaDP = Assets::getTexture("water_dp").id;
	glBindTexture(GL_TEXTURE_2D, seaDP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void BeachScene::UpdateScene() {
	totalTime = (float)SDL_GetTicks() / 1000;
	t = totalTime * 0.3f;
	r = 70.0F;
	h = 50.F;
	static const GLfloat bgColor[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, bgColor);
	glClearBufferfv(GL_DEPTH, 0, &one);

	view = Matrix4::createLookAt(Vector3(sinf(t) * r, h, cosf(t) * r), Vector3(0.0f, 20.0f, 20.0f), Vector3(0.0f, 1.0f, 0.0f));
	proj = Matrix4::createPerspectiveFOV(45.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);

	sp_sand.Use();
	sp_sand.setMatrix4("mv_matrix", view);
	sp_sand.setMatrix4("proj_matrix", proj);
	sp_sand.setMatrix4("mvp_matrix", proj * view);
	sp_sand.setFloat("dmap_depth", isDisplacementEnabled ? dmapDepth : 0.0f);
	sp_sand.setFloat("enable_fog", isFogEnabled ? 1.0f : 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);

	float sinAnim = sin(t * 17) * 2;
	float sinDisVal = sin(t * 10) * 2;
	
	sp_sea.Use();
	sp_sea.setMatrix4("mv_matrix", view);
	sp_sea.setMatrix4("proj_matrix", proj);
	sp_sea.setMatrix4("mvp_matrix", proj * view);
	sp_sea.setFloat("dmap_depth", isDisplacementEnabled ? dmapDepth : 0.0f);
	sp_sea.setFloat("enable_fog", isFogEnabled ? 1.0f : 0.0f);
	sp_sea.setFloat("time", totalTime);
	sp_sea.setFloat("sin", sinAnim);
	sp_sea.setFloat("sinDisplacement", sinDisVal);

	float minHeight = 5;
	float maxHeight = dmapDepth;

	sp_sea.setFloat("minHeight", minHeight);
	sp_sea.setFloat("maxHeight", maxHeight);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}

void BeachScene::HandleInputs(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_w)
		{
			//press W to switch with wireframe view
			wireframe = !wireframe;
		}
	}
}



