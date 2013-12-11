#include "2dcolliderclass.h"

Collider2D::Collider2D()
{

}

Collider2D::~Collider2D()
{

}

bool Collider2D::CheckCollide(int id, D3DXVECTOR3 upPos)
{
	int i;
	for(i = 0; i < cPos.size();i++)
	{
		if(i != id-1)
		{
			if(upPos.x-cPos[i].x <= 1.9f && upPos.x-cPos[i].x >= -1.9f)
			{
				if(upPos.y - cPos[i].y <= 1.9f && upPos.y-cPos[i].y >= -1.9f)
					return false;
			}
			if(upPos.y-cPos[i].y <= 1.9f && upPos.y-cPos[i].y >= -1.9f)
			{
				if(upPos.x - cPos[i].x <= 1.9f && upPos.x-cPos[i].x >= -1.9f)
					return false;
			}
		}
	}
	return true;
}


void Collider2D::SetPos(vector<D3DXVECTOR3> pos)
{
	cPos = pos;
}

void Collider2D::AddPos(vector<D3DXVECTOR3> pos)
{
	int i;
	for(i = 0; i < pos.size();i++)
	{
		cPos.push_back(pos[i]);
	}
}