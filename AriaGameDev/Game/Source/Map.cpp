#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include"Physics.h"
#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <string.h>
#include <math.h>


Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false)
		return;

    // L03: DONE 6: Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)
	/*
    ListItem<TileSet*>* tileset;
    tileset = mapData.tilesets.start;

    while (tileset != NULL) 
	{
        app->render->DrawTexture(tileset->data->texture,0,0);
        tileset = tileset->next;
    }
	//*/
	
	//int  x = 1, y = 1;
	//
	//
	//int gid = mapData.maplayers.start->data->Get(x, y);
	//
	//LOG("id: ", gid); 
	//SDL_Rect rect = mapData.tilesets.start->data->GetTileRect(gid);
	//iPoint screenPos = MapToWorld(x, y);
	//
	//app->render->DrawTexture(mapData.tilesets.start->data->texture, screenPos.x, screenPos.y, &rect);
	
	// L04: TODO 5: Prepare the loop to draw all tiles in a layer + DrawTexture()
	ListItem<MapLayer*>* mapLayerIterator = mapData.maplayers.start;
	
	for (int x = 0; x < mapData.maplayers.start->data->width; x++)
	{
		for (int y = 0; y < mapData.maplayers.start->data->height; y++)
		{
			int gid = mapData.maplayers.start->data->Get(x, y);

			SDL_Rect rect = mapData.tilesets.start->data->GetTileRect(gid);
			iPoint screenPos = MapToWorld(x, y);

			app->render->DrawTexture(mapData.tilesets.start->data->texture, screenPos.x, screenPos.y, &rect);

		}
	}

	//L04: TODO 9: Complete the draw function (inside the loop from TODO 5)
	//Find which tile id is on x, y coordinates 
	//Find out that Tile?s Rect inside the tileset Image (
	//Find out where in the World(screen) we have to draw
}

// L04: TODO 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * mapData.tileWidth;
	ret.y = y * mapData.tileHeight;

	//ret.x = app->render->camera.x+600;
	//ret.y = app->render->camera.y + 200;

	return ret;
}

iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret;

	ret.x = x / mapData.tileWidth;
	ret.y = y / mapData.tileHeight;

	//ret.x = app->render->camera.x+600;
	//ret.y = app->render->camera.y + 200;

	return ret;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };
	
	int relativeIndex = id - firstgid;
	
	// L04: TODO 7: Get relative Tile rectangle
	rect.w = tile_width;
	rect.h = tile_height;

	rect.x = margin + (tile_width + spacing) * (relativeIndex % columns);
	rect.y = margin + (tile_height + spacing) * (relativeIndex / columns);

	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// L04: TODO 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* layerItem;
	layerItem = mapData.maplayers.start;

	while (layerItem != NULL) 
	{
		RELEASE(layerItem->data);
		layerItem = layerItem->next;
	}

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if(ret == true)
    {
		ret = LoadMap(mapFile);
	}
	
    if (ret == true)
    {
        ret = LoadTileSets(mapFile.child("map"));
    }

	// L04: TODO 4: Iterate all layers and load each of them
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}

    if(ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		// L04: TODO 4: LOG the info for each loaded layer
    }
	
	// Clean up the pugui tree
	if(mapFile) mapFile.reset();

    mapLoaded = ret;

    return ret;
}

// L03: DONE 3: Implement LoadMap to load the map properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 3: Load map general properties
		mapData.height = map.attribute("height").as_int();
        mapData.width = map.attribute("width").as_int();
        mapData.tileHeight = map.attribute("tileheight").as_int();
        mapData.tileWidth = map.attribute("tilewidth").as_int();
	}

	return ret;
}

// L03: DONE 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) 
{
	bool ret = true;

	pugi::xml_node tileset;
	//pugi::xml_node tilesetIterator = tileset = mapFile.child("tileset");

	//while ( strcmp(tilesetIterator.attribute("name").as_string(), "tileset") == 0)
	//{
		for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
		{
			TileSet* set = new TileSet();
			if (ret == true) ret = LoadTilesetDetails(tileset, set);
			if (ret == true) ret = LoadTilesetImage(tileset, set);
			mapData.tilesets.add(set);
		}
		//tilesetIterator = tilesetIterator.next_sibling();
	//}

	return ret;
}

// L03: TODO 4: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// L03: DONE 4: Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	return ret;
}

// L03: DONE 4: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 4: Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		
		//SDL_Surface* surface = IMG_Load(tmp.GetString()); //Need include #include "SDL_image/include/SDL_image.h"
		//set->texture = SDL_CreateTextureFromSurface(app->render->renderer, surface);

		//NOTE: This line simplifies the loading
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// L04: TODO 3: Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;
	
	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	
	//Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);
	memset(layer->data, 0, layer->width * layer->height);
	
	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// L04: TODO 4: Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) 
{
	bool ret = true; 
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode,mapLayer);

		//add the layer to the map
		mapData.maplayers.add(mapLayer);
	}

	return ret;
}

// 1 is the id of the flying enemy

bool Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer, int navLayerId) const
{
	bool ret = false;
	ListItem<MapLayer*>* item;
	item = mapData.maplayers.start;

	for (item = mapData.maplayers.start; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;

		if (layer->properties.GetProperty("Navigation", navLayerId) == 1) // If we have the properties that we want then true
		{
			uchar* mapa = new uchar[layer->width * layer->height]; // Sring that store tiles
			memset(mapa, 1, layer->width * layer->height);

			for (int y = 0; y < mapData.height; ++y)
			{
				for (int x = 0; x < mapData.width; ++x)
				{
					int i = (y * layer->width) + x;

					int tileId = layer->Get(x, y);
					TileSet* tileset = (tileId > 0) ? GetTilesetFromTileId(tileId) : NULL;

					if (tileset != NULL)
					{
						mapa[i] = (tileId - tileset->firstgid) > 0 ? 0 : 1; // Store tiles id's at their position
					}
				}
			}
			*buffer = mapa; // then return the string for the pathfinding
			width = mapData.width;
			height = mapData.height;
			ret = true;
			break;
		}	
		break;
	}

	return ret;
}

int Properties::GetProperty(const char* value, int defaultValue) const
{
	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return defaultValue;
}


bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;
	// TODO 6: Fill in the method to fill the custom properties from 
	// an xml_node

	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}

	return ret;
}

TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}