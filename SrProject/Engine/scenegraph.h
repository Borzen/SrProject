#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include "ModelClass.h"
#include "textureclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "D3DClass.h"
#include "Cameraclass.h"
#include <vector>
#include <d3d11.h>
#include <d3dx10math.h>
#include "terrainclass.h"
#include "Colorshaderclass.h"
#include "Terrainshaderclass.h"
#include "textclass.h"
#include "fontshaderclass.h"
using namespace std;

class SceneGraph
{
	public: 
		SceneGraph();
		SceneGraph(const SceneGraph&);
		~SceneGraph();
		bool Render(D3DClass*,TextureShaderClass*,LightShaderClass*,CameraClass*, LightClass*, ColorShaderClass*, TerrainShaderClass*, TextClass*, FontShaderClass*, ID3D11Buffer*);
		void Destroy();
		bool IsLoaded();
		void ComputeInFrustumFlags(const D3DXMATRIX);
		int Add(ID3D11Device*, char*, WCHAR*, D3DXVECTOR3);
		int Add(ID3D11Device*, char*, WCHAR*);
		int Add(ID3D11Device*, char*, WCHAR*, float,float,float,float);
		int Add(ID3D11Device*, char*, WCHAR*, float, float, float, float, float, float);

		int AddTerrain(ID3D11Device*, char*, WCHAR*);

		void TranslateMesh(int, D3DXMATRIX&);
		void SetMeshPosition(int, D3DXMATRIX&);
		void SetMeshPosition(int,int,float,float,float);
		void StartScene(D3DXMATRIX,float);

		void updatePos(int, ID3D11Device*,float,float,float);
		void updatePos(int, ID3D11Device*,D3DXVECTOR3);

		void AddInstancePos(int, float,float,float);
		void AddInstancePos(int, D3DXVECTOR3);
		int AddInstance(ID3D11Device*, char*, WCHAR*, vector<D3DXVECTOR3>);
		int AddInstance(char*,WCHAR*);
		bool InitInstance(int,ID3D11Device*,D3DXVECTOR3);
		int AddInstance(int, float, float, float, float);
		int AddInstance(int);

private:
	vector<ModelClass*> meshList;
	TerrainClass* terrain;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> instancePos;
	vector<char*> instanceFN;
	vector<WCHAR*> instanceTX;
	float _sceneScaling;
	D3DXMATRIX _worldMatrix;
};

#endif