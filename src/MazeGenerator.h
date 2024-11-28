#pragma once
#include <raylib/raylib.h>
#include <string>
#include <vector>
#include <fstream>

enum class ObjectType : char
{
	Invalid = 0,
	PlayerStart = 1,
	ExitNode = 2
}; 

struct RuntimeObjectInfo
{
	Vector2 position;
	ObjectType type;
};

enum class CollisionType :  char
{
	None = 0,
	Wall = 1,
	Exit = 2
};

struct MazeRuntimeInfo
{
	std::vector<char> collisionMask;
	short width;
	short height;
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

	struct ObjectInfo
	{
		std::string name;
		int32_t x;
		int32_t y;
		ObjectType type;
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
};