#include "stdafx.h"
#include "Plg.h"

bool Plg::Load(const char * fileName)
{
	std::ifstream pFin(fileName);
	if (!pFin) {
		std::cerr << "File could not be opened:" << fileName << std::endl;
		return false;
	}
	PolygonList.clear();
	while (!pFin.eof())
	{
		std::vector<vertex> VertexList;
		char objName[30];
		int Vertexes = 0;
		int Polygons = 0;
		pFin >> objName >> Vertexes >> Polygons;
		if (pFin.fail())
			break;
		std::cout << objName << std::endl;
		while (pFin.get() != '\n')
			continue;
		vertex vertexLine;
		for (int i = 0; i < Vertexes; i++)
		{
			pFin >> vertexLine.x >> vertexLine.y >> vertexLine.z;
			VertexList.push_back(vertexLine);
			while (pFin.get() != '\n')
				continue;
		}
		std::string line;
		int PolygonCnt = 0;
		while (getline(pFin, line))
		{
			if (line == "") continue;
			std::istringstream ss(line);
			char dummy[20];
			int num, cnt;
			std::vector<vertex> vrt;
			//dummy id
			ss >> dummy;
			// count of points in polygon
			ss >> cnt;
			for (int j = 0; j < cnt; j++)
			{ 
				if (ss >> num)
				{
					if (num < VertexList.size())
						vrt.push_back(VertexList[num]);
					else
					{
						std::cerr << "Error in range\n";
						return false;
					}
				}
			}
			PolygonList.push_back(vrt);
			PolygonCnt++;
			if (PolygonCnt == Polygons)
				break;
		}
	}
	pFin.close();
	return true;
}
