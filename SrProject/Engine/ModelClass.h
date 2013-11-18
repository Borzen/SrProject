////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>
#include <fstream>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "texturearrayclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x,y,z;
		float tu,tv;
		float nx,ny,nz;

	};

	struct InstancePos
	{
		float x,y,z;
	};

	struct InstanceType
	{
		D3DXVECTOR3 position;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*,WCHAR*,bool, D3DXVECTOR3);
	bool Initialize(ID3D11Device*, char*, WCHAR*,bool, D3DXVECTOR3);
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*,bool, D3DXVECTOR3);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	void SetInstance(int, vector<D3DXVECTOR3>);
	bool instanceRender();

	bool updateBuffers(ID3D11Device*, D3DXVECTOR3);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView** GetTextureArray();


private:
	bool InitializeBuffers(ID3D11Device*, D3DXVECTOR3);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;
	TextureClass* m_Texture;
	TextureArrayClass* m_TextureArray;
	ModelType* m_model;
	InstancePos* m_instancePos;
	bool isInstance, fromFile;
	vector<D3DXVECTOR3> instancePos;
};

#endif