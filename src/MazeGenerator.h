#pragma once
#include <raylib/raylib.h>
#include <string>
#include <vector>
#include <fstream>

class MazeGenerator
{
public:
	static void GenerateMazeMap(const std::string& name, Mesh& maze);
private:
	enum LayerType : char
	{
		Data = 0
	};

	struct LayerInfo
	{
		std::string name;
		LayerType type;
		void* data;
		size_t dataSize;
	};

	struct MazeInfo
	{
		char width = 0;
		char height = 0;
		std::vector<LayerInfo> layers;
	};
private:
	static void ParseFile(std::ifstream& file, MazeGenerator::MazeInfo& maze);

	static void GenerateMesh(MazeGenerator::MazeInfo& info, Mesh& outMesh);

	static bool CheckLayerData(void* data, size_t idx, char value);
};