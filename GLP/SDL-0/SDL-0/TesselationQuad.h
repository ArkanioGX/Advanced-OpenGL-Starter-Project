#pragma once
#include "TessellationScene.h"
class TessellationQuadScene : public TessellationScene
{
	void LoadShaders() override;
	void UpdateScene() override;
public:
	TessellationQuadScene();
	~TessellationQuadScene() {}
};

