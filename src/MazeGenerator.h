#pragma once
#include <raylib/raylib.h>
#include <string>
#include <vector>
#include <fstream>

enum class ObjectType : unsigned char
{
	Invalid = 0,
	PlayerStart = 1,
	ExitNode = 2,
	SavePoint = 3,
	ItemChest = 4,
	Door = 5
}; 

struct RuntimeObjectInfo
{
	Vector2 position;
	ObjectType type;
	char orientation;
	char itemId;
};

enum class CollisionType : unsigned char
{
	None = 0,
	Wall = 1,
	Exit = 2,
	Object = 3
};

struct MazeRuntimeInfo
{
	std::vector<char> collisionMask;
	int width;
	int height;
	Texture2D atlas;
	std::vector<RuntimeObjectInfo> objects;
	float FogColor[4];
	float LightColor[4];
};

enum class TileLayerType : char
{
	Floor = 0,
	Wall = 1,
	Celling = 2
};

class MazeGenerator
{
public:
	static void GenerateMazeMap(const std::string& name, Mesh& maze, MazeRuntimeInfo& info);
private:
	enum LayerType : char
	{
		Invalid = 0,
		Tile = 1,
		Object = 2
	};

	enum class UVType : char
	{
		LEFT, 
		RIGHT,
		BOTTOM, 
		TOP,
		FRONT,
		BACK
	};

	struct RectangleF
	{
		float x;
		float y;
		float width;
		float height;
	};

	struct ObjectInfo
	{
		std::string name;
		int32_t x;
		int32_t y;
		ObjectType type;
		char orientation;
		char itemId;
	};

	struct TileInfo
	{
		int id;
		RectangleF uvRect;
	};

	struct LayerInfo
	{
		std::string name;
		LayerType type;
		TileLayerType tileType;
		void* data;
		size_t dataSize;
		std::vector<ObjectInfo> objects;
	};

	struct MazeInfo
	{
		int width = 0;
		int height = 0;
		int tileSize;
		int imageSize;
		uint8_t FogColor[4];
		uint8_t LightColor[4];
		RectangleF DefalutTileUVs;
		std::string atlasName;
		std::vector<TileInfo> tiles;
		std::vector<LayerInfo> layers;
	};
	
private:
	static void ParseFile(std::ifstream& file, MazeGenerator::MazeInfo& maze);

	static void ReadTileData(char* dataLocation, size_t size, std::ifstream& stream);
	static void ReadObjectData(ObjectInfo& objectToRead, std::ifstream& stream);
	static bool IsObject(ObjectType type);
	static void GenerateMesh(MazeGenerator::MazeInfo& info, Mesh& outMesh);
	static void GenerateCollisionMask(MazeGenerator::MazeInfo& info, std::vector<char>& collisionMask);
	static void FillRuntimeInfo(MazeGenerator::MazeInfo& info, MazeRuntimeInfo& runtimeInfo);
	static bool CheckLayerData(void* data, size_t idx, char value);
	static bool CellIsWall(void* data, size_t idx);
	static RectangleF& GetTileUV(MazeGenerator::MazeInfo& info, char id);
	static void SetTileUVs(RectangleF& uvRects, Vector2* texCoordsArray, int& texCounter, UVType type);
};