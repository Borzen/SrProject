////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_




///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "terrainclass.h"
#include "colorshaderclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();

private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain;
	ColorShaderClass* m_ColorShader;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
};

#endif