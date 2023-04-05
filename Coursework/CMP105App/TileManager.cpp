#include "TileManager.h"

TileManager::TileManager()
{
	tile_map.loadTexture("gfx/tilesheet.png");
	setTileSet();
	setTileMap();
}

TileManager::~TileManager()
{

}

void TileManager::setTileSet()
{

	for (int i = 0; i < 3; i++)
	{
		tile.setSize(sf::Vector2f(32, 32 ));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tileSet.push_back(tile);
	}
	tileSet[0].setCollider(false);
	tileSet[0].setTextureRect(sf::IntRect(0, 0, 32, 32));
	tileSet[1].setTextureRect(sf::IntRect(33, 0, 32, 32));
	tileSet[2].setTextureRect(sf::IntRect(66, 0, 32, 32));
	tile_map.setTileSet(tileSet);
}

void TileManager::setTileMap()
{
	mapDimensions = sf::Vector2u(20, 20);
	tileMap = load_file("map.txt");
	tile_map.setTileMap(tileMap, mapDimensions);
	tile_map.setPosition(sf::Vector2f(0, 0));
	tile_map.buildLevel();
}

void TileManager::render(sf::RenderWindow* window)
{
	tile_map.render(window);
}

bool TileManager::collision(GameObject go)
{
	std::vector<GameObject>* world = tile_map.getLevel();
	for (int i = 0; i < (int)world->size(); i++)
	{
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(&go, &(*world)[i]))
			{
				return true;
			}
		}
	}
}