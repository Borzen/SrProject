////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
	m_Texture = 0;
	m_model = 0;
	m_TextureArray = 0;
	isInstance = false;
	fromFile = false;
	m_instanceCount = 0;
	m_instancePos = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, char* file, bool isI, D3DXVECTOR3 pos)
{
	bool result;
	isInstance = isI;
	fromFile = true;
	result = LoadModel(file);
	if(!result)
	{
		return false;
	}
	result = InitializeBuffers(device,pos);
	if(!result)
	{
		return false;
	}

	return true;

}

bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFilename, bool isI, D3DXVECTOR3 pos)
{
	bool result;

	isInstance = isI;
	// Initialize the vertex and instance buffers.
	result = InitializeBuffers(device, pos);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename, bool isI, D3DXVECTOR3 pos)
{
	bool result;

	isInstance = isI;
	fromFile = true;

	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device, pos);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2, bool isI, D3DXVECTOR3 pos)
{
	bool result;

	fromFile = true;
	isInstance = isI;

	// Load in the model data,
	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device, pos);
	if(!result)
	{
		return false;
	}

	// Load the textures for this model.
	result = LoadTextures(device, textureFilename1, textureFilename2);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{

	ReleaseTextures();

	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	ReleaseModel();
	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}

int ModelClass::GetInstanceCount()
{
	return m_instanceCount;
}

void ModelClass::SetInstance(int num, vector<D3DXVECTOR3> pos){
	m_instanceCount = num;
	instancePos = pos;
}

ID3D11ShaderResourceView** ModelClass::GetTextureArray()
{
	return m_TextureArray->GetTextureArray();
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device, D3DXVECTOR3 pos)
{
	VertexType* vertices;
	InstanceType* instances;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, instanceData, indexData;
	HRESULT result;
	int i;
		
		if(isInstance){
			
			vertices = new VertexType[m_vertexCount];
			if(!vertices)
			{
				return false;
			}

			for(i=0; i<m_vertexCount; i++)
			{
				vertices[i].position = D3DXVECTOR3(m_model[i].x + pos.x, m_model[i].y + pos.y, m_model[i].z + pos.z);
				vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
				vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
			}

			// Set up the description of the static vertex buffer.
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the vertex data.
			vertexData.pSysMem = vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			// Now create the vertex buffer.
			result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
			if(FAILED(result))
			{
				return false;
			}

			// Release the vertex array now that the vertex buffer has been created and loaded.
			delete [] vertices;
			vertices = 0;


			instances = new InstanceType[m_instanceCount];
			if(!instances){
				return false;
			}

			// Load the instance array with data.
			for(i = 0; i < m_instanceCount; i++)
			{
				instances[i].position = instancePos[i];
			}

			// Set up the description of the instance buffer.
			instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
			instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			instanceBufferDesc.CPUAccessFlags = 0;
			instanceBufferDesc.MiscFlags = 0;
			instanceBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the instance data.
			instanceData.pSysMem = instances;
			instanceData.SysMemPitch = 0;
			instanceData.SysMemSlicePitch = 0;

			// Create the instance buffer.
			result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
			if(FAILED(result))
			{
				return false;
			}

			// Release the instance array now that the instance buffer has been created and loaded.
			delete [] instances;
			instances = 0;
		}
		else{
			vertices = new VertexType[m_vertexCount];
			if(!vertices)
			{
				return false;
			}

			// Create the index array.
			indices = new unsigned long[m_indexCount];
			if(!indices)
			{
				return false;
			}
			// Load the vertex array and index array with data.
			for(i=0; i<m_vertexCount; i++)
			{
				vertices[i].position = D3DXVECTOR3(m_model[i].x + pos.x, m_model[i].y + pos.y, m_model[i].z + pos.z);
				vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
				vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

				indices[i] = i;
			}

			// Set up the description of the static vertex buffer.
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the vertex data.
			vertexData.pSysMem = vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			// Now create the vertex buffer.
			result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
			if(FAILED(result))
			{
				return false;
			}

			// Set up the description of the static index buffer.
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;
			indexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the index data.
			indexData.pSysMem = indices;
			indexData.SysMemPitch = 0;
			indexData.SysMemSlicePitch = 0;

			// Create the index buffer.
			result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
			if(FAILED(result))
			{
				return false;
			}

			// Release the arrays now that the vertex and index buffers have been created and loaded.
			delete [] vertices;
			vertices = 0;

			delete [] indices;
			indices = 0;
		}
		return true;
}

bool ModelClass::updateBuffers(ID3D11Device* device, D3DXVECTOR3 pos)
{
	ShutdownBuffers();

	InitializeBuffers(device,pos);

	return true;
}

void ModelClass::ShutdownBuffers()
{

	if(m_instanceBuffer)
	{
		m_indexBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	if(isInstance){
		unsigned int strides[2];
		unsigned int offsets[2];
		ID3D11Buffer* bufferPointers[2];

		strides[0] = sizeof(VertexType);
		strides[1] = sizeof(InstanceType);

		offsets[0] = 0;
		offsets[1] = 0;

		bufferPointers[0] = m_vertexBuffer;
		bufferPointers[1] = m_instanceBuffer;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return;
	}
	else{
		unsigned int stride;
		unsigned int offset;

		// Set vertex buffer stride and offset.
		stride = sizeof(VertexType); 
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return;
	}
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ModelClass::LoadTextures(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2)
{
	bool result;


	// Create the texture array object.
	m_TextureArray = new TextureArrayClass;
	if(!m_TextureArray)
	{
		return false;
	}

	// Initialize the texture array object.
	result = m_TextureArray->Initialize(device, filename1, filename2);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTextures()
{
	// Release the texture array object.
	if(m_TextureArray)
	{
		m_TextureArray->Shutdown();
		delete m_TextureArray;
		m_TextureArray = 0;
	}

	return;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if(fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

void ModelClass::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}

bool ModelClass::instanceRender(){
	return isInstance;
}