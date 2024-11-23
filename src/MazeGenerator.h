#pragma once
#include <raylib/raylib.h>
#include <string>
#include <vector>
#include <fstream>

class MazeGenerator
{
public:
	static void GenerateMazeMap(const std::string& name, Mesh& maze, std::vector<char>& collisionMask);
private:
	enum LayerType : char
	{
		Invalid = 0,
		Tile = 1,
		Object = 2
	};

	struct ObjectInfo
	{
		char* name;
		int32_t x;
		int32_t y;
	};

	struct LayerInfo
	{
		std::string name;
		LayerType type;
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
	static bool CheckLayerData(void* data, size_t idx, char value);
};