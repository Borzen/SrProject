////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "frustumclass.h"
#include "modellistclass.h"
#include "multitextureshaderclass.h"
#include "lightmapshaderclass.h"
#include "textureshaderclass.h"
#include "scenegraph.h"
#include "InputClass.h"
#include "timerclass.h"
#include "cpuclass.h"
#include "fpsclass.h"
#include "positionclass.h"
#include "Colorshaderclass.h"
#include "Terrainshaderclass.h"
#include "fontshaderclass.h"
#include <vector>

using namespace std;

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, HINSTANCE);
	void Shutdown();
	bool Frame();
	bool Render();
	bool HandleInput(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;
	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;
	MultiTextureShaderClass* m_MultiTextureShader;
	LightMapShaderClass* m_LightMapShader;
	TextureShaderClass* m_TextureShader;
	SceneGraph* m_SceneGraph;
	InputClass* m_Input;
	TimerClass* m_Timer;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	ColorShaderClass* m_ColorShader;
	PositionClass* m_Position;
	TerrainShaderClass* m_TerrainShader;

	FontShaderClass* m_FontShader;

	vector<int> ids;
};

#endif