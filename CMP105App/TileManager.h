#pragma once
#include "Framework/TileMap.h"
#include "Framework/Collision.h"
class TileManager : public TileMap
{
public:
	TileManager();
	~TileManager();

	void setTileSet();
	void setTileMap();
	void render(sf::RenderWindow* window);
	bool collision(GameObject go);
protected:
	TileMap tile_map;

	GameObject tile;
};