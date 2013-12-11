#include "roomparser.h"

bool RoomParse::Initalize(char* manFile, SceneGraph* sg)
{
	return false;
}

int RoomParse::ParsePlayerModel(char* model, WCHAR* texture,float x,float y, float z, float s)
{
	return 0;
}

int RoomParse::ParseInstance(char* model, WCHAR* texture)
{
	return 0;
}

int RoomParse::ParseTerrain(char* hm, WCHAR*  texture)
{
	return 0;
}

void RoomParse::ParseForInstancePos(char x, float y, float z, int size)
{
	int i;
	for(i = 0; i < size;i++)
	{
		m_sg->AddInstancePos(currentID,i,y,z);
	}
}

void RoomParse::ParseForInstancePos(float x, char y, float z, int size)
{
	int i;
	for(i = 0; i < size;i++)
	{
		m_sg->AddInstancePos(currentID,x,i,z);
	}
}

void RoomParse::ParseForInstancePos(float x, float y, char z, int size)
{
	int i;
	for(i = 0; i < size;i++)
	{
		m_sg->AddInstancePos(currentID,x,y,i);
	}
}

void RoomParse::ParseForInstancePos(char x, char y, float z, int size)
{
	int i,j;
	for(i = 0; i < size;i++)
	{
		for(j = 0; j < size;j++)
		{
			m_sg->AddInstancePos(currentID,i,j,z);
		}
	}
}

void RoomParse::ParseForInstancePos(char x, float y, char z, int size)
{
	int i,j;
	for(i = 0; i < size;i++)
	{
		for(j = 0; j < size;j++)
		{
			m_sg->AddInstancePos(currentID,i,y,j);
		}
	}
}

void RoomParse::ParseForInstancePos(char x, char y, char z, int size)
{
	int i,j,k;
	for(i = 0; i < size;i++)
	{
		for(j = 0; j < size;j++)
		{
			for(k = 0; k < size;k++)
			{
				m_sg->AddInstancePos(currentID,i,j,k);
			}
		}
	}
}

void RoomParse::ParseInstancePos(float x, float y, float z)
{
	m_sg->AddInstancePos(currentID,x,y,z);
}

