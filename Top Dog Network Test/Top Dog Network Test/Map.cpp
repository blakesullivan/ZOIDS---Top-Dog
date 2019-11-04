//Blake Sullivan - Map.cpp
#include "Map.h"

Map::Map()
{
	m_pMap = NULL;
}
Map::~Map()
{
	for (int i = m_vTiles.size() - 1; i > 0; i--)
	{
		delete m_vTiles[i];
	}
	SDL_FreeSurface(GetMap());
}

void Map::SetupMap(int iWidth, int iHeight, string sMapName, vector<Object*>& vObj)
{
	string sInputName = "", sPicName = "", sTemp = "";
	int iTemp = 0;
	fstream fMap;
	sInputName = sMapName + ".txt";
	sPicName = sMapName + ".bmp";
	SetMap(sPicName);
	fMap.open(sInputName.c_str());
	if (fMap.good())
	{
		int iLoopNum = (iWidth / Tile::GetSize()) * (iHeight / Tile::GetSize());
		//cout << "iLoopNum = " << iLoopNum << " Square::GetSize(): " << Square::GetSize() << endl;
		int iRow = 0, iCol = 0, iX = 0, iY = 0;
		fMap >> sTemp;
		//cout << sTemp << endl;
		for (int i = 0; i < iLoopNum; i++)
		{
			iX = iCol * Tile::GetSize();
			iY = iRow * Tile::GetSize();

			iTemp = atoi(sTemp.substr(0, sTemp.find(",")).c_str());
			sTemp = sTemp.substr(sTemp.find(",") + 1, sTemp.length());
			
			//cout << "iCol: " << iCol << " iRow: " << iRow << " iX: " << iX << " iY: " << iY << endl;
			AddTile(iRow, iCol, iX, iY, iTemp, vObj);
			
			iCol++;
			if (iCol * Tile::GetSize() >= iWidth)
			{
				iRow++; 
				iCol = 0;
				sTemp = "";
				fMap >> sTemp;
				//cout << sTemp << endl;
			}
		}
	}
}

void Map::DrawMap(SDL_Surface* screen, float winX, float winY)
{
	//int r = 0, g = 0, b = 0;
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 240, 152, 32) ); 
	SDL_Rect sclip, dclip;
	for (m_vTilesIT = m_vTiles.begin(); m_vTilesIT != m_vTiles.end(); m_vTilesIT++)
	{
		//cout << "In DrawMap. GetColour: " << m_vTilesIT->GetColour() << endl;
		//if (m_vTilesIT->GetColour() == 9)
		//{
		//	//cout << "In DrawMap, colour = 9" << endl;
		//	r = 200; g = 200; b = 200;
		//}
		//else
		//{
		//	//cout << "In DrawMap, colour = 0" << endl;
		//	r = 50; g = 220; b = 50;
		//}

		//boxRGBA(screen, m_vTilesIT->GetX(), m_vTilesIT->GetY(), m_vTilesIT->GetX()+Square::GetSize(), m_vTilesIT->GetY()+Square::GetSize(), r, g, b, 255);
		//rectangleRGBA(screen, m_vTilesIT->GetX(), m_vTilesIT->GetY(), m_vTilesIT->GetX()+Square::GetSize(), m_vTilesIT->GetY()+Square::GetSize(), 0, 0, 0, 255);

		sclip.x = (*m_vTilesIT)->GetPicPos() * Tile::GetSize();
		sclip.y = 0; sclip.w = Tile::GetSize(); sclip.h = Tile::GetSize();
		dclip.x = (*m_vTilesIT)->GetX() - winX; dclip.y = (*m_vTilesIT)->GetY() - winY;
		dclip.w = Tile::GetSize(); dclip.h = Tile::GetSize();
		SDL_BlitSurface(GetMap(), &sclip, screen, &dclip);
		//rectangleRGBA(screen, (*m_vTilesIT)->GetX() - winX, (*m_vTilesIT)->GetY() - winY, (*m_vTilesIT)->GetX()+Tile::GetSize() - winX, (*m_vTilesIT)->GetY()+Tile::GetSize() - winY, 0, 0, 0, 255);
	}
	
}

void Map::AddTile(int r, int c, int x, int y, int pp, vector<Object*>& vObj)
{
	Tile *tempTile;
	tempTile = new Tile;
	tempTile->Init(r, c, x, y, 32, pp);
	m_vTiles.push_back(tempTile);
	vObj.push_back(tempTile);
}

Tile* Map::GetTile(int x, int y)
{
	for (m_vTilesIT = m_vTiles.begin(); m_vTilesIT != m_vTiles.end(); m_vTilesIT++)
	{
		if (((*m_vTilesIT)->GetCol() == static_cast<int>(x / Tile::GetSize())) && (*m_vTilesIT)->GetRow() == static_cast<int>((y / Tile::GetSize())))
		{
			return (*m_vTilesIT);
		}
	}

	return (*m_vTiles.begin());
}

Tile* Map::GetTileFromRC(int x, int y)
{
	for (m_vTilesIT = m_vTiles.begin(); m_vTilesIT != m_vTiles.end(); m_vTilesIT++)
	{
		if ((*m_vTilesIT)->GetCol() == x && (*m_vTilesIT)->GetRow() == y)
		{
			return (*m_vTilesIT);
		}
	}

	return (*m_vTiles.begin());
}

void Map::SetMap(string sMapLoc)
{
	m_pMap = SDL_LoadBMP(sMapLoc.c_str());
	SDL_SetColorKey(m_pMap, SDL_SRCCOLORKEY, SDL_MapRGB(m_pMap->format, 255, 0, 255));
}
SDL_Surface* Map::GetMap()
{
	return m_pMap;
}

Tile* Map::FindEmptyPickupPoint(int iPickupType)
{
	for (m_vTilesIT = m_vTiles.begin(); m_vTilesIT != m_vTiles.end(); m_vTilesIT++)
	{
		if ((*m_vTilesIT)->GetID() == iPickupType)
		{
			if ((*m_vTilesIT)->GetHasPickup() == false)
			{
				Tile* temp = (*m_vTilesIT);
				//std::cout << "Found Empty Pickup Point!\n";
				//std::cout << "R: " << temp->GetRow() " C: " << temp->GetCol() << " x: " << temp->GetX() << " y: " << temp->GetY() << endl;
				return temp;
			}
		}
	}

	return NULL;
}