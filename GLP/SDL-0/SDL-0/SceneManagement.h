#pragma once
#include "BaseScene.h"
#include "ScreensaverScene.h"
#include "CubeScene.h"
#include "TessellationModesScene.h"
#include "TerrainTessellationScene.h"
#include "TextureScene.h"
#include "TesselationQuad.h"
#include "CubeTessellationScene.h"
#include "BeachScene.h"

enum SceneID {
	BASE_SCENE,
	DEMO_SCENE,
	TESSELLATION,
	TESSELLATION_MODES,
	TERRAIN_TESSELLATION,
	MIP_MAP,
	CUBES,
	TESSELLATION_QUAD,
	TESSELLATION_CUBE,
	BEACH
};

Scene* SceneSelector(SceneID id) {
	switch (id) {
	case BASE_SCENE: {
		return new BaseScene();
		break;
	}	
	case DEMO_SCENE: {
		return new ScreensaverScene();
		break;
	}
	case TESSELLATION: {
		return new TessellationScene();
		break;
	}
	case TESSELLATION_MODES: {
		return new TessellationModesScene();
		break;
	}
	case TERRAIN_TESSELLATION: {
		return new TerrainTessellationScene();
		break;
	}
	case MIP_MAP: {
			return new TextureScene();
		break;
	}
	case CUBES: {
		return new CubeScene();
	break;
	}
	case TESSELLATION_QUAD: {
		return new TessellationQuadScene();
		break;
	}
	case TESSELLATION_CUBE: {
		return new CubeTessellationScene();
		break;
	}
	case BEACH: {
		return new BeachScene();
		break;
	}
	default: {
		return nullptr;
	}
	}
}