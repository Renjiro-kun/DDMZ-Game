#pragma once
#include <raylib/raylib.h>
#include <string>
#include <vector>
#include <fstream>

enum class ObjectType : char
{
	Invalid = 0,
	PlayerStart = 1,
	ExitNode = 2,
	SavePoint = 3
}; 

struct RuntimeObjectInfo
{
	Vector2 position;
	ObjectType type;
};

enum class CollisionType :   char
{
	None = 0,
	Wall = 1,
	Exit = 2,
	Object = 3
};

struct MazeRuntimeInfo
{
	std::vector<char> collisionMask;
	short width;
	short height;
	Texture2D atlas;
	std::vector<RuntimeObjectInfo> objects;
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
		char width = 0;
		char height = 0;
		int tileSize;
		int imageSize;
		RectangleF DefalutTileUVs;
		std::string atlasName;
		std::vector<TileInfo> tiles;
		std::vector<LayerInfo> layers;
	};
	
private:
	static void ParseFile(std::ifstream& file, MazeGenerator::MazeInfo& maze);

	static void ReadTileData(char* dataLocation, size_t size, std::ifstream& stream);
	static void ReadObjectData(ObjectInfo& objectToRead, std::ifstream& stream);

	static void GenerateMesh(MazeGenerator::MazeInfo& info, Mesh& outMesh);
	static void GenerateCollisionMask(MazeGenerator::MazeInfo& info, std::vector<char>& collisionMask);
	static void FillRuntimeInfo(MazeGenerator::MazeInfo& info, MazeRuntimeInfo& runtimeInfo);
	static bool CheckLayerData(void* data, size_t idx, char value);
	static bool CellIsWall(void* data, size_t idx);
	static RectangleF& GetTileUV(MazeGenerator::MazeInfo& info, char id);
	static void SetTileUVs(RectangleF& uvRects, Vector2* texCoordsArray, int& texCounter, UVType type);
};