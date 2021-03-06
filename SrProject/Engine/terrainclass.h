#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>
#include <vector>
#include "textureclass.h"

using namespace std;

const int TEXTURE_REPEAT = 8;

class TerrainClass
{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
		};

		struct HeightMapType
		{
			float x,y,z;
			float tu, tv;
			float nx,ny,nz;
		};
		struct VectorType
		{
			float x,y,z;
		};
	public:
		TerrainClass();
		TerrainClass(const TerrainClass&);
		~TerrainClass();

		bool Initialize(ID3D11Device*, char*, WCHAR*);
		void Shutdown();
		void Render(ID3D11DeviceContext*);

		int GetIndexCount();
		int GetVertexCount();
		void CopyVertexArray(void*);

		vector<D3DXVECTOR3> GetHM();

		int GetWidth();
		int GetHeight();

		ID3D11ShaderResourceView* GetTexture();

	private:

		bool LoadHeightMap(char*);
		void NormalizeHeightMap();
		void ShutdownHeightMap();

		bool CalculateNormals();

		void CalculateTextureCoordinates();
		bool LoadTexture(ID3D11Device*, WCHAR*);
		void ReleaseTexture();

		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);
		
	private:
		int m_terrainWidth, m_terrainHeight;
		int m_vertexCount, m_indexCount;
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

		vector<D3DXVECTOR3> hm;

		HeightMapType* m_heightMap;
		TextureClass* m_Texture;
		VertexType* m_vertices;
};
#endif