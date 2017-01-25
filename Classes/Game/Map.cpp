#include "Map.h"
#include "Game\Resource.h"
#include "Game\Logger.h"
#include "Framework\Utility.h"
#include <math.h>


namespace MyGame
{
	USING_NS_CC;
	
	const float terrainGroupSpeed = -100.0f;
	const float backgroundTilesSpeed = -30.0f;
	const float backgroundHillSpeed = -60.0f;
	const float texOffset = 1;

	Map::~Map() 
	{
		if (floorTmx)
		{
			delete floorTmx;
		}
	}

	Map * Map::CreateMap()
	{
		auto node = Map::create();

		return node;
	}

	bool Map::init()
	{
		if (!Node::init())
		{
			return false;
		}

		this->scheduleUpdate();

		return true;
	}

	void Map::update(float delta)
	{
		terrainMove(delta);
		backgroundMove(delta);
	}

	void Map::SetUp()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		floorTmx = new TMXLoader();
		floorTmx->loadMap("floor", ResourceInstance->FloorBlueTMX);

		auto map = floorTmx->getMap("floor");

		auto terrainGroup = Node::create();
		for (int i = 0; i < map->getHeight(); ++i)
		{
			for (int j = 0; j < map->getWidth(); ++j)
			{
				
				// get the tile at current position
				auto tileID = map->getTileLayer("layer_1")->getTileVector()[i][j];
				MyLog("tileID %d", tileID);
				
				// only render if it is an actual tile (tileID = 0 means no tile / don't render anything here)
				if (tileID > 0)
				{
					auto tileSet = map->getTileSet("core");
					MyLog("getTileCount %d, getLastGID %d", tileSet->getTileCount(), tileSet->getLastGID());

					auto terrain = tileSet->getTile(tileID - 1);
					if (terrain)
					{
						auto tileName = terrain->getProperty("tile_name");
						auto collision = MyFramework::ToBool(terrain->getProperty("collision"));
						auto image = Sprite::createWithSpriteFrame(ResourceInstance->GetCoreSpriteFrame(tileName));
						if (image)
						{
							auto size = image->getContentSize();
							auto tileW = size.width - texOffset;
							auto tileH = size.height - texOffset;
							auto allW = tileW * j;
							auto allH = tileH * i;
							image->setAnchorPoint(Vec2(0, 1));
							image->setPosition(allW, -allH);
							
							if (collision)
							{
								auto physicsBody = PhysicsBody::createBox(image->getContentSize(), PhysicsMaterial(0, 0, 0));
								physicsBody->setContactTestBitmask(TerrainBitmask);
								physicsBody->setDynamic(false);
								image->setPhysicsBody(physicsBody);
							}

							terrainGroup->addChild(image);
							size = terrainGroup->getContentSize();
							if (allW + tileW > size.width)
							{
								size.width = allW + tileW;
							}

							if (allH + tileH > size.height)
							{
								size.height = allH + tileH;
							}

							terrainGroup->setContentSize(size);

						}													
					}				
				}
			}
		}

		auto size = terrainGroup->getContentSize();
		MyLog("groupW %f, groupH %f", size.width, size.height);
		terrainGroup->setPositionY(size.height);

		m_TerrainGroup.push_back(terrainGroup);
		CacheTerrainLayer->addChild(terrainGroup);

		// for clone terrain
		int buffer = 2;
		for (int i = 1; i < static_cast<int>(ceil(visibleSize.width / size.width)) + buffer; i++)
		{
			auto clone = MyFramework::CloneCCNode(terrainGroup);
			clone->setPositionX(i * size.width);
			m_TerrainGroup.push_back(clone);
			CacheTerrainLayer->addChild(clone);
		}

		// background set up
		auto image = Sprite::create();
		image->setColor(ResourceInstance->GetBackgroundColor());
		image->setAnchorPoint(Vec2(0.5f, 0.5f));
		image->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
		image->setPosition(origin + visibleSize / 2);
		CacheBackgroundLayer->addChild(image);

		char buff[100];
		auto offset = origin + visibleSize / 2;

		for (int i = 0; i < 3; i++)
		{
			// tiles
			snprintf(buff, sizeof(buff), ResourceInstance->BackgroundSetTiles, ResourceInstance->BackgroundSet);
			auto bkImage = Sprite::createWithSpriteFrame(ResourceInstance->GetBackgroundFrame(buff));
			if (bkImage)
			{
				bkImage->setPosition(i * (bkImage->getContentSize().width - texOffset), offset.y);
				m_BackgroundTilesGroup.push_back(bkImage);
				CacheBackgroundLayer->addChild(bkImage, 0);

			}

			// hill
			snprintf(buff, sizeof(buff), ResourceInstance->BackgroundSetHill, ResourceInstance->BackgroundSet);
			bkImage = Sprite::createWithSpriteFrame(ResourceInstance->GetBackgroundFrame(buff));
			if (bkImage)
			{
				bkImage->setPosition(i * (bkImage->getContentSize().width - texOffset), offset.y - 100);
				m_BackgroundHillGroup.push_back(bkImage);
				CacheBackgroundLayer->addChild(bkImage, 1);
			}

		}


	}

	void Map::terrainMove(float delta)
	{
		float offsetX = terrainGroupSpeed * delta;
		CacheTerrainLayer->setPositionX(CacheTerrainLayer->getPositionX() + offsetX);

		float tileWidth = (m_TerrainGroup.size() > 0)? m_TerrainGroup[0]->getContentSize().width : 0;

		for (int i = 0; i < m_TerrainGroup.size();)
		{
			auto node = m_TerrainGroup[i];
			auto localPos = node->getPosition();
			localPos.x += tileWidth;
			auto worldPos = (node->getParent()) 
				? node->getParent()->convertToWorldSpace(localPos)
				: localPos;
			if (worldPos.x < 0)
			{
				MyLog("worldPosW %f, worldPosH %f", worldPos.x, worldPos.y);
				m_TerrainGroup.erase(m_TerrainGroup.begin() + i);
				m_RegTerrainGroup.push_back(node);
				continue;
			}

			i++;
		}

		auto oriW = (m_TerrainGroup.size() > 0) 
			? m_TerrainGroup[m_TerrainGroup.size() - 1]->getPositionX() + tileWidth
			: 0;

		for (int i = 0; i < m_RegTerrainGroup.size(); ++i)
		{
			m_RegTerrainGroup[i]->setPositionX(oriW + i * tileWidth);
			m_TerrainGroup.push_back(m_RegTerrainGroup[i]);
		}

		m_RegTerrainGroup.clear();

	}

	void Map::backgroundMove(float delta)
	{
		for (int i = 0; i < 3; i++)
		{
			m_BackgroundTilesGroup[i]->setPositionX(
				m_BackgroundTilesGroup[i]->getPositionX() + backgroundTilesSpeed * delta);
		
			m_BackgroundHillGroup[i]->setPositionX(
				m_BackgroundHillGroup[i]->getPositionX() + backgroundHillSpeed * delta);
		}

		for (int i = 0; i < 3; i++)
		{
			auto image = m_BackgroundTilesGroup[i];
			{
				auto pos = image->getPosition();
				auto size = image->getContentSize();
				if (pos.x < -size.width / 2)
				{
					m_BackgroundTilesGroup.erase(m_BackgroundTilesGroup.begin() + i);
					m_BackgroundTilesGroup.push_back(image);
					image->setPositionX(m_BackgroundTilesGroup[m_BackgroundTilesGroup.size() - 2]->getPositionX() + size.width - texOffset);
				}
			}

			image = m_BackgroundHillGroup[i];
			{
				auto pos = image->getPosition();
				auto size = image->getContentSize();
				if (pos.x < -size.width / 2)
				{
					m_BackgroundHillGroup.erase(m_BackgroundHillGroup.begin() + i);
					m_BackgroundHillGroup.push_back(image);
					image->setPositionX(m_BackgroundHillGroup[m_BackgroundHillGroup.size() - 2]->getPositionX() + size.width - texOffset);
				}
			}



		}

	}



}

