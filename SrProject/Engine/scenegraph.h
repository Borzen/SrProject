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
#include "frustumclass.h"
#include "quadtreeclass.h"
#include "2dcolliderclass.h"

using namespace std;

class SceneGraph
{
	public: 
		SceneGraph();
		SceneGraph(const SceneGraph&);
		~SceneGraph();
		bool Initilize(void);
		void Shutdown(void);

		bool Render(D3DClass*,TextureShaderClass*,LightShaderClass*,CameraClass*, LightClass*, ColorShaderClass*, TerrainShaderClass*, TextClass*, FontShaderClass*, FrustumClass*, QuadTreeClass*, float, ID3D11Buffer*);
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

		bool updatePos(int, ID3D11Device*,float,float,float);
		bool updatePos(int, ID3D11Device*,D3DXVECTOR3);

		void AddInstancePos(int, float,float,float);
		void AddInstancePos(int, D3DXVECTOR3);
		int AddInstance(ID3D11Device*, char*, WCHAR*, vector<D3DXVECTOR3>);
		int AddInstance(char*,WCHAR*);
		bool InitInstance(int,ID3D11Device*,D3DXVECTOR3);
		int AddInstance(int, float, float, float, float);
		int AddInstance(int);

		int AddCollidorSquare(ID3D11Device*, char*,float,float,float);
		int AddCollidorSquare(ID3D11Device*, char*,D3DXVECTOR3);
		bool UpdateCollider(int,float,float,float);
		bool UpdateCollider(int,D3DXVECTOR3);

		void AddColliderHeight();

		bool ShouldFall(int,float,float,float);

		D3DXVECTOR3 GetPosition(int);

		TerrainClass* GetTerrain();

private:
	vector<ModelClass*> colliderList;
	vector<ModelClass*> meshList;
	TerrainClass* terrain;
	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> colliderPos;
	vector<D3DXVECTOR4> m_InstancePos;
	vector<char*> m_instanceFN;
	vector<WCHAR*> m_instanceTX;
	Collider2D* c2d;
};

#endif