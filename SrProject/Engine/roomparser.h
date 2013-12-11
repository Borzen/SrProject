#ifndef _ROOMPARSER_H_
#define _ROOMPARSER_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>
#include <fstream>
#include <string>
#include "scenegraph.h"
using namespace std;

class RoomParse
{
	public:
		
		bool Initalize(char*,SceneGraph*);
		vector<int> GetIDs();

	private:
		int ParsePlayerModel(char*, WCHAR*, float,float,float,float);
		int ParseModel(char*, WCHAR*, float,float,float,float);
		int ParseTerrain(char*,WCHAR*);
		int ParseInstance(char*,WCHAR*);
		void ParseInstanceInt(float,float,float);
		void ParseForInstancePos(char,float,float,int);
		void ParseForInstancePos(float,char,float,int);
		void ParseForInstancePos(float,float,char,int);
		void ParseForInstancePos(char,char,float,int);
		void ParseForInstancePos(char,float,char,int);
		void ParseForInstancePos(float,char,char,int);
		void ParseForInstancePos(char,char,char,int);
		void ParseInstancePos(float,float,float);

		vector<int> ids;
		SceneGraph* m_sg;
		int currentID;
};


#endif