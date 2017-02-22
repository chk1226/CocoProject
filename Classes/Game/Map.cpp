#include "Map.h"
#include "Game\Resource.h"
#include "Game\Logger.h"
#include "Framework\Utility.h"
#include <math.h>


namespace MyGame
{
	USING_NS_CC;
	
	const float terrainGroupSpeed = -150.0f;
	const float backgroundTilesSpeed = -30.0f;
	const float backgroundHillSpeed = -60.0f;
	const float texOffset = 1;
	const Vec2 obstacleHeightRange = Vec2(2, 8);	
	const Vec2 obstacleAppearRange = Vec2(400.f, 400.f);
	const int obstaclePassRange = 3;

	Map::~Map() 
	{
		if (floorTmx)
		{
			delete floorTmx;
		}

		m_TerrainGroup.clear();
		m_RegTerrainGroup.clear();
		m_BackgroundTilesGroup.clear();
		m_BackgroundHillGroup.clear();
		m_ObstacleList.clear();
		m_ObstacleEndList.clear();
		m_PassList.clear();

		m_Obstacle->release();
		for (auto it = m_ObstacleList.begin(); it != m_ObstacleList.end(); ++it)
		{
			(*it)->release();
		}
		m_ObstacleList.clear();

		m_ObstacleEnd->release();
		for (auto it = m_ObstacleEndList.begin(); it != m_ObstacleEndList.end(); ++it)
		{
			(*it)->release();
		}
		m_ObstacleEndList.clear();

		m_Pass->release();
		for (auto it = m_PassList.begin(); it != m_PassList.end(); ++it)
		{
			(*it)->release();
		}
		m_PassList.clear();
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
		if (m_state == State::Run)
		{
			terrainMove(delta);
			backgroundMove(delta);
			if (ObstacleEnable)
			{
				obstacleMove(delta);
			}

		}

	}

	void Map::SetUp()
	{
		// state setup
		m_state = State::Run;
		ObstacleEnable = true;

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		char buff[50];

		floorTmx = new TMXLoader();
		floorTmx->loadMap("floor", ResourceInstance->FloorBlueTMX);

		auto map = floorTmx->getMap("floor");

		// terrain
		auto terrainGroup = Node::create();
		for (int i = 0; i < map->getHeight(); ++i)
		{
			for (int j = 0; j < map->getWidth(); ++j)
			{
				
				// get the tile at current position
				auto tileID = map->getTileLayer("layer_1")->getTileVector()[i][j];
				//MyLog("tileID %d", tileID);
				
				// only render if it is an actual tile (tileID = 0 means no tile / don't render anything here)
				if (tileID > 0)
				{
					auto tileSet = map->getTileSet("core");
					//MyLog("getTileCount %d, getLastGID %d", tileSet->getTileCount(), tileSet->getLastGID());

					auto terrain = tileSet->getTile(tileID - 1);
					if (terrain)
					{
						auto tileName = terrain->getProperty("tile_name");
						snprintf(buff, sizeof(buff), tileName.c_str(), ResourceInstance->GetTerrainSetName().c_str());
						auto collision = MyFramework::ToBool(terrain->getProperty("collision"));
						auto image = Sprite::createWithSpriteFrame(ResourceInstance->GetCoreSpriteFrame(buff));
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
		//MyLog("groupW %f, groupH %f", size.width, size.height);
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

		// obstacle set up
		{
			auto r = ResourceInstance;
			snprintf(buff, sizeof(buff), r->ObstacleName, r->GetObstacleSetName().c_str());
			m_Obstacle = Sprite::createWithSpriteFrame(r->GetCoreSpriteFrame(buff));
			if (m_Obstacle)
			{
				m_Obstacle->retain();
				auto physicsBody = PhysicsBody::createBox(m_Obstacle->getContentSize(), PhysicsMaterial(0, 0, 0));
				physicsBody->setContactTestBitmask(ObstacleBitmask);
				physicsBody->setDynamic(false);
				m_Obstacle->setPhysicsBody(physicsBody);
			}

			snprintf(buff, sizeof(buff), r->ObstacleEndName, r->GetObstacleSetName().c_str());
			m_ObstacleEnd = Sprite::createWithSpriteFrame(r->GetCoreSpriteFrame(buff));
			if (m_ObstacleEnd)
			{
				m_ObstacleEnd->retain();
				auto physicsBody = PhysicsBody::createBox(m_ObstacleEnd->getContentSize(), PhysicsMaterial(0, 0, 0));
				physicsBody->setContactTestBitmask(ObstacleBitmask);
				physicsBody->setDynamic(false);
				m_ObstacleEnd->setPhysicsBody(physicsBody);
			}
			
			passFlowNumber = 0;
			m_Pass = Sprite::createWithSpriteFrame(r->GetCoreSpriteFrame(r->PassName));
			if (m_Pass)
			{
				m_Pass->retain();
				auto physicsBody = PhysicsBody::createBox(m_Pass->getContentSize(), PhysicsMaterial(0, 0, 0));
				physicsBody->setContactTestBitmask(PassBitmask);
				physicsBody->setDynamic(false);
				m_Pass->setPhysicsBody(physicsBody);
				m_Pass->setVisible(false);
			}
			
			CacheObstacleLayer->setPositionY(terrainGroup->getContentSize().height);
			appearDistance = RandomHelper::random_int<int>(obstacleAppearRange.x, obstacleAppearRange.y);
		}

		// background set up
		auto image = Sprite::create();
		image->setColor(ResourceInstance->GetBackgroundColor());
		image->setAnchorPoint(Vec2(0.5f, 0.5f));
		image->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
		image->setPosition(origin + visibleSize / 2);
		CacheBackgroundLayer->addChild(image);

		auto offset = origin + visibleSize / 2;

		for (int i = 0; i < 3; i++)
		{
			// tiles
			snprintf(buff, sizeof(buff), ResourceInstance->BackgroundSetTiles, static_cast<int>(ResourceInstance->BackgroundSet));
			auto bkImage = Sprite::createWithSpriteFrame(ResourceInstance->GetBackgroundFrame(buff));
			if (bkImage)
			{
				bkImage->setPosition(i * (bkImage->getContentSize().width - texOffset), offset.y + 50);
				m_BackgroundTilesGroup.push_back(bkImage);
				CacheBackgroundLayer->addChild(bkImage, 0);

			}

			// hill
			snprintf(buff, sizeof(buff), ResourceInstance->BackgroundSetHill, static_cast<int>(ResourceInstance->BackgroundSet));
			bkImage = Sprite::createWithSpriteFrame(ResourceInstance->GetBackgroundFrame(buff));
			if (bkImage)
			{
				bkImage->setPosition(i * (bkImage->getContentSize().width - texOffset), offset.y - 50);
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
				//MyLog("worldPosW %f, worldPosH %f", worldPos.x, worldPos.y);
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

	const int obstacleTag = 1;
	const int obstacleEndListTag = 2;
	const int passTag = 3;
	const int viewOutBuffer = 50;

	void Map::obstacleMove(float delta)
	{
		auto child = CacheObstacleLayer->getChildren();
		auto offset = terrainGroupSpeed * delta;
		for (auto i = 0; i < child.size(); ++i)
		{
			auto node = child.at(i);
			node->setPositionX(node->getPositionX() + offset);
		
			// recycle obstacle
			if (node->getPositionX() < -viewOutBuffer)
			{
				auto subChild = node->getChildren();
				for (auto subIt = subChild.begin(); subIt != subChild.end(); ++subIt)
				{
					switch ((*subIt)->getTag())
					{
					case obstacleTag:
						m_ObstacleList.push_back((*subIt));
						break;

					case obstacleEndListTag:
						(*subIt)->setRotationQuat(Quaternion::identity());
						m_ObstacleEndList.push_back((*subIt));
						break;

					case passTag:
						m_PassList.push_back((*subIt));
						break;
					}

				}
				
				CacheObstacleLayer->removeChild(node);
				child = CacheObstacleLayer->getChildren();
				i--;

			}

		}
		
		//MyLog("appearDistance %d", appearDistance);

		if (appearDistance <= 0)
		{
			auto fillUpFunc = [](std::vector<Node*>& list, cocos2d::Node* source, int num)
			{
				for (int i = 0; i < num; ++i)
				{
					auto clone = MyFramework::CloneSingleCCNode(source);
					if (clone)
					{
						clone->retain();
						list.push_back(clone);
					}
				}
			};

			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto origin = Director::getInstance()->getVisibleOrigin();
			auto node = Node::create();
			node->setPositionX(visibleSize.width + viewOutBuffer);

			// set pass obstacle
			int passHeight = 4;
			int startPass = RandomHelper::random_int<int>(obstacleHeightRange.x, obstacleHeightRange.y);
			passFlowNumber++;

			for (int i = 0; i < passHeight; i++)
			{
				if (m_PassList.size() == 0)
				{
					fillUpFunc(m_PassList, m_Pass, 1);
				}

				auto clone = m_PassList[0];
				m_PassList.erase(m_PassList.begin());
				clone->setPositionY((startPass + i) * clone->getContentSize().height);
				clone->setName(MyFramework::Convert(passFlowNumber));
				node->addChild(clone, 0, passTag);
			}

			// set obstacle end
			if (m_ObstacleEndList.size() < 2)
			{
				fillUpFunc(m_ObstacleEndList, m_ObstacleEnd, 2);
			}
			{
				auto up = m_ObstacleEndList[0];
				m_ObstacleEndList.erase(m_ObstacleEndList.begin());
				up->setRotation(180);
				auto end = m_ObstacleEndList[0];
				m_ObstacleEndList.erase(m_ObstacleEndList.begin());

				up->setPositionY((startPass + passHeight) * up->getContentSize().height);
				node->addChild(up, 0, obstacleEndListTag);
				end->setPositionY((startPass - 1) * end->getContentSize().height);
				node->addChild(end, 0, obstacleEndListTag);
			}

			//set obstacle 
			for (int i = 0; i < startPass - 1; i++)
			{
				if (m_ObstacleList.size() == 0)
				{
					fillUpFunc(m_ObstacleList, m_Obstacle, 1);
				}

				auto clone = m_ObstacleList[0];
				m_ObstacleList.erase(m_ObstacleList.begin());

				clone->setPositionY(i* clone->getContentSize().height);
				node->addChild(clone, 0, obstacleTag);
			}
			for (int i = startPass + passHeight + 1; i < 14; i++)
			{
				if (m_ObstacleList.size() == 0)
				{
					fillUpFunc(m_ObstacleList, m_Obstacle, 1);
				}

				auto clone = m_ObstacleList[0];
				m_ObstacleList.erase(m_ObstacleList.begin());

				clone->setPositionY(i* clone->getContentSize().height);
				node->addChild(clone, 0, obstacleTag);
			}

			CacheObstacleLayer->addChild(node);

			appearDistance = RandomHelper::random_int<int>(obstacleAppearRange.x, obstacleAppearRange.y);

		}
		else
		{
			appearDistance += offset;
		}


	}



}

