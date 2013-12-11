#ifndef _2DCOLLIDERCLASS_H_
#define _2DCOLLIDERCLASS_H_

#include <vector>
#include <d3d11.h>
#include <d3dx10math.h>

using namespace std;

class Collider2D
{
	public:
		Collider2D();
		Collider2D(const Collider2D&);
		~Collider2D();

		bool CheckCollide(int, D3DXVECTOR3);
		bool Under(int,D3DXVECTOR3);
		void SetPos(float,float,float);
		void SetPos(D3DXVECTOR3);
		void SetPos(vector<D3DXVECTOR3>);
		void SetIDs(int);
		void SetIDs(vector<int>);
		void AddPos(vector<D3DXVECTOR3>);
		void AddPos(D3DXVECTOR3);

	private:
		vector<D3DXVECTOR3> cPos;
		vector<int> ids;

};

#endif