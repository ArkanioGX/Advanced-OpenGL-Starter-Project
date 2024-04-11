#include "CubeTessellationScene.h"

#include "MeshObject.h"
#include "Window.h"


CubeTessellationScene::CubeTessellationScene()
{

}


void CubeTessellationScene::LoadShaders() {
	m_vertexShader.LoadFrom("cube.vert", VERTEX);
	m_fragmentShader.LoadFrom("cube.frag", FRAGMENT);
	m_tessEvalShader.LoadFrom("cubeTesselEval.shader", TESSELLATION_EVALUATION);
	m_tessControlShader.LoadFrom("cubeTesselControl.shader", TESSELLATION_CONTROL);
}

void CubeTessellationScene::CreateShaderPrograms()
{
	m_Program.Compose({ &m_vertexShader, &m_fragmentShader, &m_tessControlShader, &m_tessEvalShader});
}

void CubeTessellationScene::VerticeInformationSlicer()
{
	float* verticeArray = new float[m_vertices.size()]();
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), verticeArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	delete[] verticeArray;
}

void CubeTessellationScene::SetupScene()
{
	m_vertices = { 
		0.25f,	-0.25f,	-0.25f,
		-0.25f, -0.25f, -0.25f,
		0.25f,	0.25f,	-0.25f,
		-0.25f, 0.25f,	-0.25f,
		0.25f,	0.25f,	-0.25f,
		-0.25f, -0.25f, -0.25f,
	};

	m_vertices = { -0.25f,  0.25f, -0.25f,
			  -0.25f, -0.25f, -0.25f,
				0.25f, -0.25f, -0.25f,

				0.25f, -0.25f, -0.25f,
				0.25f,  0.25f, -0.25f,
			  -0.25f,  0.25f, -0.25f,

				0.25f, -0.25f, -0.25f,
				0.25f, -0.25f,  0.25f,
				0.25f,  0.25f, -0.25f,

				0.25f, -0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,
				0.25f,  0.25f, -0.25f,

				0.25f, -0.25f,  0.25f,
			  -0.25f, -0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
			  -0.25f,  0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
			  -0.25f, -0.25f, -0.25f,
			  -0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f, -0.25f,
			  -0.25f,  0.25f, -0.25f,
			  -0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
				0.25f, -0.25f,  0.25f,
				0.25f, -0.25f, -0.25f,

				0.25f, -0.25f, -0.25f,
			  -0.25f, -0.25f, -0.25f,
			  -0.25f, -0.25f,  0.25f,

			  -0.25f,  0.25f, -0.25f,
				0.25f,  0.25f, -0.25f,
				0.25f,  0.25f,  0.25f,

				0.25f,  0.25f,  0.25f,
			  -0.25f,  0.25f,  0.25f,
			  -0.25f,  0.25f, -0.25f
	};
	/*
				0.25f, -0.25f, -0.25f,
				0.25f,  0.25f, -0.25f,
			  -0.25f,  0.25f, -0.25f,

				0.25f, -0.25f, -0.25f,
				0.25f, -0.25f,  0.25f,
				0.25f,  0.25f, -0.25f,

				0.25f, -0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,
				0.25f,  0.25f, -0.25f,

				0.25f, -0.25f,  0.25f,
			  -0.25f, -0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
			  -0.25f,  0.25f,  0.25f,
				0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
			  -0.25f, -0.25f, -0.25f,
			  -0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f, -0.25f,
			  -0.25f,  0.25f, -0.25f,
			  -0.25f,  0.25f,  0.25f,

			  -0.25f, -0.25f,  0.25f,
				0.25f, -0.25f,  0.25f,
				0.25f, -0.25f, -0.25f,

				0.25f, -0.25f, -0.25f,
			  -0.25f, -0.25f, -0.25f,
			  -0.25f, -0.25f,  0.25f,

			  -0.25f,  0.25f, -0.25f,
				0.25f,  0.25f, -0.25f,
				0.25f,  0.25f,  0.25f,

				0.25f,  0.25f,  0.25f,
			  -0.25f,  0.25f,  0.25f,
			  -0.25f,  0.25f, -0.25f
	};*/
	LoadShaders();
	CreateShaderPrograms();
	projection = Matrix4::createPerspectiveFOV(70.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);
	position = Vector3(0, 0, -4.0f);
	mv = Matrix4::createTranslation(position);

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	VerticeInformationSlicer();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Creating and loading the simple texture
	Texture2D m_WallTexture = Texture2D();
	m_WallTexture.load("Textures/wall.png");
	m_WallTexture.generate();
	m_WallTexture.use();
	glGenerateTextureMipmap(m_WallTexture.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

}

void CubeTessellationScene::UpdateScene() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue)) / 2.0f;

	position.y = sinusoidValue;
	m_Program.Use();
	mv = Matrix4::createTranslation(position - Vector3(0.5f, 0, 0));
	Matrix4 rotationX = Matrix4::createRotationX(0.01f);
	Matrix4 rotationY = Matrix4::createRotationY(0.005f);
	Matrix4 rotationZ = Matrix4::createRotationY(0.01f);
	rotation *= rotationX;
	rotation *= rotationY;
	rotation *= rotationZ;
	mv = mv * rotation;

	float sin2 = (sin(timeValue) / 2.0f) + 0.7f;

	int itessLevelLocation = glGetUniformLocation(m_Program.GetID(), "inTessLevel");
	int otessLevelLocation = glGetUniformLocation(m_Program.GetID(), "outTessLevel");
	glUniform1f(itessLevelLocation, fmaxf(sin2 * 10, 1));
	glUniform1f(otessLevelLocation, fmaxf(sin2 * 20, 1));


	m_Program.setMatrix4("mv_matrix", mv);
	m_Program.setMatrix4("projection", projection);
	glDrawArrays(GL_PATCHES, 0, 36);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mv = Matrix4::createTranslation(position + Vector3(0.5f, 0, 0));
	mv = mv * rotation;
	m_Program.setMatrix4("mv_matrix", mv);

	glDrawArrays(GL_PATCHES, 0, 36);
}



