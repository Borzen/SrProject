#include "scenegraph.h"
struct PerFrameConstants
{
	D3DXMATRIX m_CameraWorldViewProj;
	D3DXMATRIX m_CameraWorldView;
	D3DXMATRIX m_CameraProj;
	D3DXVECTOR4 m_CameraNearFar;

	unsigned int m_FrameBufferDimensionX;
	unsigned int m_FrameBufferDimensionY;
	unsigned int m_FrameBufferDimensionZ;
	unsigned int m_FrameBufferDimensionW;
};

SceneGraph::SceneGraph()
{
}

SceneGraph::SceneGraph(const SceneGraph& sg)
{
}

SceneGraph::~SceneGraph()
{
}

bool SceneGraph::IsLoaded()
{
	if(meshList.empty())
	{
		return false;
	}
	return true;
}

int SceneGraph::AddTerrain(ID3D11Device* device, char* heightMap, WCHAR* texture)
{
	terrain = new TerrainClass;
	bool result;
	result = terrain->Initialize(device, heightMap,texture);
	if(!result)
	{
		return -1;
	}
	return 1;
}

int SceneGraph::AddInstance(char* fn,WCHAR* texture)
{
	instanceFN.push_back(fn);
	instanceTX.push_back(texture);

	return instanceFN.size();
}

bool SceneGraph::InitInstance(int id, ID3D11Device* device, D3DXVECTOR3 pos)
{
	ModelClass* newModel = new ModelClass;
	newModel->SetInstance(instancePos.size(),instancePos);
	bool result = newModel->Initialize(device,instanceFN[id-1],instanceTX[id-1],true, pos);
	if(!result)
	{
		return false;
	}
	return true;
}

void SceneGraph::AddInstancePos(int id, float x, float y, float z)
{
	AddInstancePos(id,D3DXVECTOR3(x,y,z));
}

void SceneGraph::AddInstancePos(int id, D3DXVECTOR3 pos)
{
	instancePos.push_back(pos);
}

int SceneGraph::Add(ID3D11Device* device, char* modelFile, WCHAR* textureFile, float x, float y, float z, float xScale, float yScale, float zScale)
{

	//D3DXMATRIX t, s, f;
	//D3DXMatrixScaling(&s,xScale,yScale,zScale);
	//D3DXMatrixTranslation(&t,x,y,z);
	//f = s*t;
	return Add(device,modelFile,textureFile,D3DXVECTOR3(x,y,z));
}

int SceneGraph::Add(ID3D11Device* device, char* modelFile, WCHAR* textureFile, float x, float y, float z, float scale)
{
	return Add(device,modelFile,textureFile,x,y,z,scale,scale,scale);
}

int SceneGraph::Add(ID3D11Device* device, char* modelFile, WCHAR* textureFile)
{
	D3DXMATRIX t;
	D3DXMatrixTranslation(&t,0,0,0);
	return Add(device,modelFile, textureFile,D3DXVECTOR3(0,0,0));
}

int SceneGraph::Add(ID3D11Device* device, char* modelFile, WCHAR* textureFile, D3DXVECTOR3 position)
{
	ModelClass* newModel = new ModelClass;
	newModel->Initialize(device,modelFile,textureFile,false, position);
	meshList.push_back(newModel);
	positions.push_back(position);
	return meshList.size();
}

bool SceneGraph::Render(D3DClass* m_D3D,TextureShaderClass* m_TSC,LightShaderClass* m_LSC,CameraClass* m_Camera, LightClass* m_L, ColorShaderClass* m_CSC, TerrainShaderClass* m_TS, TextClass* m_TC, FontShaderClass* m_FS, ID3D11Buffer*)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_TC->Render(m_D3D->GetDeviceContext(), m_FS, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	terrain->Render(m_D3D->GetDeviceContext());

	result = m_TS->Render(m_D3D->GetDeviceContext(),terrain->GetIndexCount(),worldMatrix,viewMatrix,projectionMatrix,
		m_L->GetAmbientColor(),m_L->GetDiffuseColor(),
		m_L->GetDirection(), terrain->GetTexture());
	if(!result)
	{
		return false;
	}

	for(int i = 0; i < meshList.size();i++)
	{
		meshList[i]->Render(m_D3D->GetDeviceContext());
		if(meshList[i]->instanceRender())
		{
			result = m_TSC->Render(m_D3D->GetDeviceContext(),meshList[i]->GetVertexCount(),meshList[i]->GetInstanceCount(), worldMatrix, viewMatrix,
				projectionMatrix, meshList[i]->GetTexture());
		}
		else
		{
			result = m_LSC->Render(m_D3D->GetDeviceContext(), meshList[i]->GetIndexCount(),worldMatrix, viewMatrix, projectionMatrix,
				meshList[i]->GetTexture(), m_L->GetDirection(), m_L->GetDiffuseColor());
		}
		if(!result)
		{
			return false;
		}
	}

	m_D3D->EndScene();

	return true;

}

void SceneGraph::updatePos(int id, ID3D11Device* device, float x, float y, float z)
{
	updatePos(id,device, D3DXVECTOR3(x,y,z));
}

void SceneGraph::updatePos(int id, ID3D11Device* device, D3DXVECTOR3 pos)
{
	meshList[id]->updateBuffers(device,pos);
}