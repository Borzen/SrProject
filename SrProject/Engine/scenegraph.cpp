#include "scenegraph.h"

SceneGraph::SceneGraph()
{
	c2d = 0;
}

SceneGraph::SceneGraph(const SceneGraph& sg)
{
}

SceneGraph::~SceneGraph()
{
}

bool SceneGraph::Initilize()
{
	c2d = new Collider2D;
	if(!c2d)
	{
		return false;
	}
	return true;
}

void SceneGraph::Shutdown()
{
	delete c2d;
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
	m_instanceFN.push_back(fn);
	m_instanceTX.push_back(texture);
	return m_instanceFN.size();
}

bool SceneGraph::InitInstance(int id, ID3D11Device* device, D3DXVECTOR3 pos)
{
	ModelClass* newModel = new ModelClass;
	vector<D3DXVECTOR3> temp;
	int i;
	for(i = 0; i < m_InstancePos.size();i++)
	{
		if(id = m_InstancePos[i].x)
		{
			temp.push_back(D3DXVECTOR3(m_InstancePos[i].y,m_InstancePos[i].z,m_InstancePos[i].w));
		}
	}
	newModel->SetInstance(temp.size(),temp);
	bool result = newModel->Initialize(device,m_instanceFN[id-1],m_instanceTX[id-1],true, pos);
	if(!result)
	{
		return false;
	}
	meshList.push_back(newModel);
	positions.push_back(pos);
	return true;
}

void SceneGraph::AddInstancePos(int id, float x, float y, float z)
{
	AddInstancePos(id,D3DXVECTOR3(x,y,z));
}

void SceneGraph::AddInstancePos(int id, D3DXVECTOR3 pos)
{
	m_InstancePos.push_back(D3DXVECTOR4(id,pos.x,pos.y,pos.z));
}

int SceneGraph::Add(ID3D11Device* device, char* modelFile, WCHAR* textureFile, float x, float y, float z, float xScale, float yScale, float zScale)
{

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
	bool result;
	ModelClass* newModel = new ModelClass;
	result = newModel->Initialize(device,modelFile,textureFile,false, position);
	if(!result)
	{
		return -1;
	}
	meshList.push_back(newModel);
	positions.push_back(position);
	AddCollidorSquare(device,"../Engine/Models/square.txt",position);
	return meshList.size();
}

bool SceneGraph::Render(D3DClass* m_D3D,TextureShaderClass* m_TSC,LightShaderClass* m_LSC,CameraClass* m_Camera, LightClass* m_L, ColorShaderClass* m_CSC, TerrainShaderClass* m_TS, TextClass* m_TC, FontShaderClass* m_FS, FrustumClass* m_F, QuadTreeClass* m_QT, float SD, ID3D11Buffer*)
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

	m_F->ConstructFrustum(SD,projectionMatrix,viewMatrix);

		// Set the terrain shader parameters that it will use for rendering.
	result = m_TS->SetShaderParameters(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_L->GetAmbientColor(), 
						      m_L->GetDiffuseColor(), m_L->GetDirection(), terrain->GetTexture());
	if(!result)
	{
		return false;
	}

	m_QT->Render(m_F,m_D3D->GetDeviceContext(),m_TS);

	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	result = m_TC->SetRenderCount(m_QT->GetDrawCount(), m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

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

bool SceneGraph::updatePos(int id, ID3D11Device* device, float x, float y, float z)
{
	return updatePos(id,device, D3DXVECTOR3(x,y,z));
}

bool SceneGraph::updatePos(int id, ID3D11Device* device, D3DXVECTOR3 pos)
{
	bool result;
	c2d->SetPos(colliderPos);
	result = UpdateCollider(id,pos);
	if(result)
	{
		meshList[id-1]->updateBuffers(device,pos);
		colliderList[id-1]->updateBuffers(device,pos);
		return true;
	}
	return false;
}

TerrainClass* SceneGraph::GetTerrain()
{
	return terrain;
}

D3DXVECTOR3 SceneGraph::GetPosition(int id)
{
	return positions[id-1];
}

int SceneGraph::AddCollidorSquare(ID3D11Device* device, char* file,float x,float y,float z)
{
	return AddCollidorSquare(device, file,D3DXVECTOR3(x,y,z));
}

int SceneGraph::AddCollidorSquare(ID3D11Device* device, char* file, D3DXVECTOR3 pos)
{
	ModelClass* newCollidor = new ModelClass;
	bool r = newCollidor->Initialize(device,file,false,pos);
	if(!r)
	{
		return -1;
	}
	colliderList.push_back(newCollidor);
	colliderPos.push_back(pos);
	return colliderList.size();
}

bool SceneGraph::UpdateCollider(int id, float x, float y, float z)
{
	return UpdateCollider(id, D3DXVECTOR3(x,y,z));
}

bool SceneGraph::UpdateCollider(int id, D3DXVECTOR3 pos)
{
	return c2d->CheckCollide(id,pos);
}

bool SceneGraph::ShouldFall(int id, float x, float y, float z)
{
	bool result;
	result = c2d->CheckCollide(id,D3DXVECTOR3(x,y,z));
	if(!result)
	{
		return false;
	}
	return true;
}