#include "MazeGenerator.h"

#include <string.h>
#include <vector>
#include <string>
#include <sstream>

void MazeGenerator::ParseFile(std::ifstream& file, MazeGenerator::MazeInfo& mazeInfo)
{
	char layerCount = 0;

	char header[4];
	file.read(header, sizeof(char) * 4);
	file.read(&mazeInfo.width, sizeof(char));
	file.read(&mazeInfo.height, sizeof(char));
	file.read(&layerCount, sizeof(char));
	for (size_t i = 0; i < layerCount; i++)
	{
		LayerInfo& layer = mazeInfo.layers.emplace_back();
		char length = 0;
		file.read(&length, sizeof(char));
		char* name = new char[length];
		file.read(name, sizeof(char) * length);
		layer.name = name;
		file.read((char*)&layer.type, sizeof(char));
		if(layer.type == LayerType::Tile)
		{
			layer.dataSize = mazeInfo.width * mazeInfo.height;
			layer.data = (void*)new char[layer.dataSize];
			ReadTileData((char*)layer.data, (size_t)mazeInfo.width * mazeInfo.height, file);
		} 
		else if (layer.type == LayerType::Object)
		{
			char count = 0;
			file.read(&count, sizeof(char));
			layer.objects.reserve(count);
			for (size_t j = 0; j < count; j++)
			{
				ObjectInfo obj;
				ReadObjectData(obj, file);
				layer.objects.push_back(obj);
			}
		}
		
		delete[] name;
	}
	file.close();
}

void MazeGenerator::ReadTileData(char* dataLocation, size_t size, std::ifstream& stream)
{
	stream.read(dataLocation, sizeof(char) * size);
}

void MazeGenerator::ReadObjectData(ObjectInfo& object, std::ifstream& stream)
{
	char length = 0;
	stream.read(&length, sizeof(length));
	stream.read(object.name, sizeof(char) * length);
	int32_t tempInt = 0;
	stream.read((char*)&tempInt, sizeof(int32_t));
	object.x = tempInt;
	stream.read((char*)&tempInt, sizeof(int32_t));
	object.y = tempInt;
}

bool MazeGenerator::CheckLayerData(void* data, size_t idx, char value)
{
	return ((char*)data)[idx] == value;
}

void MazeGenerator::GenerateMesh(MazeGenerator::MazeInfo& info, Mesh& outMesh)
{
	int maxTriangles = info.width * info.height * 12;

	int vCounter = 0; // Count verticies
	int tcCounter = 0; // Count texcoords
	int nCounter = 0; // Count normals
	int cCounter = 0; // Colors counter

	float w = 1.f;
	float h = 1.f;
	float h2 = 1.f;

	Vector3* mapVerticies = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
	Vector2* mapTexcoord = (Vector2*)RL_MALLOC(maxTriangles * 2 * sizeof(Vector2));
	Vector3* mapNormals = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
	Vector4* mapColors = (Vector4*)RL_MALLOC(maxTriangles * 4 * sizeof(Vector4));

	// Define base normals of the cube
	Vector3 n1 = { 1.f, 0.f, 0.f };
	Vector3 n2 = { -1.f, 0.f, 0.f };
	Vector3 n3 = { 0.f, 1.f, 0.f };
	Vector3 n4 = { 0.f, -1.f, 0.f };
	Vector3 n5 = { 0.f, 0.f, -1.f };
	Vector3 n6 = { 0.f, 0.f, 1.f };

	typedef struct RectangleF
	{
		float x;
		float y;
		float width;
		float height;
	} RectangleF;

	RectangleF rightTexUV	= { 0.f, 0.f, 0.5f, 0.5f };
	RectangleF leftTexUV	= { .5f, 0.f, 0.5f, 0.5f };
	RectangleF frontTexUV	= { 0.f, 0.f, 0.5f, 0.5f };
	RectangleF backTexUV	= { 0.5f, 0.f, 0.5f, 0.5f };
	RectangleF topTexUV		= { 0.f, 0.5f, 0.5f, 0.5f };
	RectangleF bottomTexUV	= { 0.5f, 0.5f, 0.5f, 0.5f };

	LayerInfo* layerInfo;

	for (size_t i = 0; i < 3; i++)
	{
		if (info.layers[i].name.compare("Walls") == 0)
		{
			layerInfo = &info.layers[i];
		}
	}

	const char wallID = 1;
	const char emptyID = 0;

	for (size_t z = 0; z < info.height; ++z)
	{
		for (size_t x = 0; x < info.width; ++x)
		{
			// Define 8 verts of the cube
			Vector3 v1 = { w * (x - 0.5f), h2, h * (z - 0.5f) };
			Vector3 v2 = { w * (x - 0.5f), h2, h * (z + 0.5f) };
			Vector3 v3 = { w * (x + 0.5f), h2, h * (z + 0.5f) };
			Vector3 v4 = { w * (x + 0.5f), h2, h * (z - 0.5f) };
			Vector3 v5 = { w * (x + 0.5f), 0, h * (z - 0.5f) };
			Vector3 v6 = { w * (x - 0.5f), 0, h * (z - 0.5f) };
			Vector3 v7 = { w * (x - 0.5f), 0, h * (z + 0.5f) };
			Vector3 v8 = { w * (x + 0.5f), 0, h * (z + 0.5f) };

			if (CheckLayerData (layerInfo->data, z * info.width + x,wallID))
			{
				// Define triangles and checking collateral cubes
				//----------------------------------------------
				// Define top triangles (2 tris, 6 verts --> v1-v2-v3, v1-v3-v4)
				mapVerticies[vCounter] 		= v1;
				mapVerticies[vCounter + 1] 	= v2;
				mapVerticies[vCounter + 2] 	= v3;
				mapVerticies[vCounter + 3] 	= v1;
				mapVerticies[vCounter + 4] 	= v3;
				mapVerticies[vCounter + 5] 	= v4;
				vCounter += 6;

				mapNormals[nCounter]		= n3;
				mapNormals[nCounter + 1]	= n3;
				mapNormals[nCounter + 2]	= n3;
				mapNormals[nCounter + 3]	= n3;
				mapNormals[nCounter + 4]	= n3;
				mapNormals[nCounter + 5]	= n3;
				nCounter += 6;

				mapTexcoord[tcCounter]		= Vector2{ topTexUV.x, topTexUV.y };
				mapTexcoord[tcCounter + 1]	= Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
				mapTexcoord[tcCounter + 2]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
				mapTexcoord[tcCounter + 3]	= Vector2{ topTexUV.x, topTexUV.y };
				mapTexcoord[tcCounter + 4]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
				mapTexcoord[tcCounter + 5]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
				tcCounter += 6;

				mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

				cCounter += 6;

				// Define botton triangles (2 tris, 6 verts --> v6-v8-v7, v6-v5-v8)
				mapVerticies[vCounter]		= v6;
				mapVerticies[vCounter + 1]	= v8;
				mapVerticies[vCounter + 2]	= v7;
				mapVerticies[vCounter + 3]	= v6;
				mapVerticies[vCounter + 4]	= v5;
				mapVerticies[vCounter + 5]	= v8;
				vCounter += 6;

				mapNormals[nCounter]		= n4;
				mapNormals[nCounter + 1]	= n4;
				mapNormals[nCounter + 2]	= n4;
				mapNormals[nCounter + 3]	= n4;
				mapNormals[nCounter + 4]	= n4;
				mapNormals[nCounter + 5]	= n4;
				nCounter += 6;

				mapTexcoord[tcCounter]		= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
				mapTexcoord[tcCounter + 1]	= Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
				mapTexcoord[tcCounter + 2]	= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
				mapTexcoord[tcCounter + 3]	= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
				mapTexcoord[tcCounter + 4]	= Vector2{ bottomTexUV.x, bottomTexUV.y };
				mapTexcoord[tcCounter + 5]	= Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
				tcCounter += 6;

				mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

				cCounter += 6;

				// Checking cube on the botton of current cube
				if (((z < info.height - 1) && CheckLayerData(layerInfo->data, (z+1)*info.width+x, emptyID)) || (z == info.height - 1))
				{
					// Define front triangles (2 tris, 6 verts --> v2-v7-v3, v3-v7-v8)
					// NOTE: Collateral occluded faces are not generated
					mapVerticies[vCounter]		= v2;
					mapVerticies[vCounter + 1]	= v7;
					mapVerticies[vCounter + 2]	= v3;
					mapVerticies[vCounter + 3]	= v3;
					mapVerticies[vCounter + 4]	= v7;
					mapVerticies[vCounter + 5]	= v8;
					vCounter += 6;

					mapNormals[nCounter]		= n6;
					mapNormals[nCounter + 1]	= n6;
					mapNormals[nCounter + 2]	= n6;
					mapNormals[nCounter + 3]	= n6;
					mapNormals[nCounter + 4]	= n6;
					mapNormals[nCounter + 5]	= n6;
					nCounter += 6;

					mapTexcoord[tcCounter]		= Vector2{ frontTexUV.x, frontTexUV.y };
					mapTexcoord[tcCounter + 1]	= Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
					mapTexcoord[tcCounter + 2]	= Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
					mapTexcoord[tcCounter + 3]	= Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y };
					mapTexcoord[tcCounter + 4]	= Vector2{ frontTexUV.x, frontTexUV.y + frontTexUV.height };
					mapTexcoord[tcCounter + 5]	= Vector2{ frontTexUV.x + frontTexUV.width, frontTexUV.y + frontTexUV.height };
					tcCounter += 6;

					mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

					cCounter += 6;
				}

				// Checking cube on top of the current cube
				if (((z > 0) && CheckLayerData(layerInfo->data, (z-1) * info.width + x, emptyID)) || (z==0))
				{
					// Define back triangles (2 tris, 6 verts --> v1-v5-v6, v1-v4-v5)
					mapVerticies[vCounter]		= v1;
					mapVerticies[vCounter + 1]	= v5;
					mapVerticies[vCounter + 2]	= v6;
					mapVerticies[vCounter + 3]	= v1;
					mapVerticies[vCounter + 4]	= v4;
					mapVerticies[vCounter + 5]	= v5;
					vCounter += 6;

					mapNormals[nCounter]		= n5;
					mapNormals[nCounter + 1]	= n5;
					mapNormals[nCounter + 2]	= n5;
					mapNormals[nCounter + 3]	= n5;
					mapNormals[nCounter + 4]	= n5;
					mapNormals[nCounter + 5]	= n5;
					nCounter += 6;

					mapTexcoord[tcCounter]		= Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
					mapTexcoord[tcCounter + 1]	= Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
					mapTexcoord[tcCounter + 2]	= Vector2{ backTexUV.x + backTexUV.width, backTexUV.y + backTexUV.height };
					mapTexcoord[tcCounter + 3]	= Vector2{ backTexUV.x + backTexUV.width, backTexUV.y };
					mapTexcoord[tcCounter + 4]	= Vector2{ backTexUV.x, backTexUV.y };
					mapTexcoord[tcCounter + 5]	= Vector2{ backTexUV.x, backTexUV.y + backTexUV.height };
					tcCounter += 6;

					mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

					cCounter += 6;
				}

				// Checking cube on right of the current cube
				if (((x < info.width - 1) && CheckLayerData(layerInfo->data, z*info.width+(x+1), emptyID)) || (x == info.width - 1))
				{
					// Define right triangles (2 tris, 6 verts --> v3-v8-v4, v4-v8-v5)
					mapVerticies[vCounter]		= v3;
					mapVerticies[vCounter + 1]	= v8;
					mapVerticies[vCounter + 2]	= v4;
					mapVerticies[vCounter + 3]	= v4;
					mapVerticies[vCounter + 4]	= v8;
					mapVerticies[vCounter + 5]	= v5;
					vCounter += 6;

					mapNormals[nCounter]		= n1;
					mapNormals[nCounter + 1]	= n1;
					mapNormals[nCounter + 2]	= n1;
					mapNormals[nCounter + 3]	= n1;
					mapNormals[nCounter + 4]	= n1;
					mapNormals[nCounter + 5]	= n1;
					nCounter += 6;

					mapTexcoord[tcCounter]		= Vector2{ rightTexUV.x, rightTexUV.y };
					mapTexcoord[tcCounter + 1]	= Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
					mapTexcoord[tcCounter + 2]	= Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
					mapTexcoord[tcCounter + 3]	= Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y };
					mapTexcoord[tcCounter + 4]	= Vector2{ rightTexUV.x, rightTexUV.y + rightTexUV.height };
					mapTexcoord[tcCounter + 5]	= Vector2{ rightTexUV.x + rightTexUV.width, rightTexUV.y + rightTexUV.height };
					tcCounter += 6;

					mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

					cCounter += 6;
				}

				// Checking cube on the left of the current cube
				if (((x > 0) && CheckLayerData(layerInfo->data, z * info.width + (x - 1), emptyID)) || (x == 0))
				{
					// Define left triangles (2 tris, 6 verts --> v1-v7-v2, v1-v6-v7)
					mapVerticies[vCounter]		= v1;
					mapVerticies[vCounter + 1]	= v7;
					mapVerticies[vCounter + 2]	= v2;
					mapVerticies[vCounter + 3]	= v1;
					mapVerticies[vCounter + 4]	= v6;
					mapVerticies[vCounter + 5]	= v7;
					vCounter += 6;

					mapNormals[nCounter]	 = n2;
					mapNormals[nCounter + 1] = n2;
					mapNormals[nCounter + 2] = n2;
					mapNormals[nCounter + 3] = n2;
					mapNormals[nCounter + 4] = n2;
					mapNormals[nCounter + 5] = n2;
					nCounter += 6;

					mapTexcoord[tcCounter]		= Vector2{ leftTexUV.x, leftTexUV.y };
					mapTexcoord[tcCounter + 1]	= Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
					mapTexcoord[tcCounter + 2]	= Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y };
					mapTexcoord[tcCounter + 3]	= Vector2{ leftTexUV.x, leftTexUV.y };
					mapTexcoord[tcCounter + 4]	= Vector2{ leftTexUV.x, leftTexUV.y + leftTexUV.height };
					mapTexcoord[tcCounter + 5]	= Vector2{ leftTexUV.x + leftTexUV.width, leftTexUV.y + leftTexUV.height };
					tcCounter += 6;

					mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
					mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

					cCounter += 6;
				}
			}
			else if (CheckLayerData(layerInfo->data, z * info.width + x, emptyID))
			{
				// Define top triangles (2 tris, 6 verts --> v1-v2-v3, v1-v3-v4)
				mapVerticies[vCounter]		= v1;
				mapVerticies[vCounter + 1]	= v3;
				mapVerticies[vCounter + 2]	= v2;
				mapVerticies[vCounter + 3]	= v1;
				mapVerticies[vCounter + 4]	= v4;
				mapVerticies[vCounter + 5]	= v3;
				vCounter += 6;

				mapNormals[nCounter]		= n4;
				mapNormals[nCounter + 1]	= n4;
				mapNormals[nCounter + 2]	= n4;
				mapNormals[nCounter + 3]	= n4;
				mapNormals[nCounter + 4]	= n4;
				mapNormals[nCounter + 5]	= n4;
				nCounter += 6;

				mapTexcoord[tcCounter]		= Vector2{ topTexUV.x, topTexUV.y };
				mapTexcoord[tcCounter + 1]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
				mapTexcoord[tcCounter + 2]	= Vector2{ topTexUV.x, topTexUV.y + topTexUV.height };
				mapTexcoord[tcCounter + 3]	= Vector2{ topTexUV.x, topTexUV.y };
				mapTexcoord[tcCounter + 4]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y };
				mapTexcoord[tcCounter + 5]	= Vector2{ topTexUV.x + topTexUV.width, topTexUV.y + topTexUV.height };
				tcCounter += 6;

				mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

				cCounter += 6;

				// Define botton triangles (2 tris, 6 verts --> v6-v8-v7, v6-v5-v8)
				mapVerticies[vCounter]		= v6;
				mapVerticies[vCounter + 1]	= v7;
				mapVerticies[vCounter + 2]	= v8;
				mapVerticies[vCounter + 3]	= v6;
				mapVerticies[vCounter + 4]	= v8;
				mapVerticies[vCounter + 5]	= v5;
				vCounter += 6;

				mapNormals[nCounter]		= n3;
				mapNormals[nCounter + 1]	= n3;
				mapNormals[nCounter + 2]	= n3;
				mapNormals[nCounter + 3]	= n3;
				mapNormals[nCounter + 4]	= n3;
				mapNormals[nCounter + 5]	= n3;
				nCounter += 6;

				mapTexcoord[tcCounter]		= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
				mapTexcoord[tcCounter + 1]	= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y + bottomTexUV.height };
				mapTexcoord[tcCounter + 2]	= Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
				mapTexcoord[tcCounter + 3]	= Vector2{ bottomTexUV.x + bottomTexUV.width, bottomTexUV.y };
				mapTexcoord[tcCounter + 4]	= Vector2{ bottomTexUV.x, bottomTexUV.y + bottomTexUV.height };
				mapTexcoord[tcCounter + 5]	= Vector2{ bottomTexUV.x, bottomTexUV.y };
				tcCounter += 6;

				mapColors[cCounter]		= Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 1] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 2] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 3] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 4] = Vector4{ 255, 255, 255, 255 };
				mapColors[cCounter + 5] = Vector4{ 255, 255, 255, 255 };

				cCounter += 6;
			}
		}
	}

	outMesh.vertexCount = vCounter;
	outMesh.triangleCount = vCounter / 3;

	outMesh.vertices = (float*)RL_MALLOC(outMesh.vertexCount * 3 * sizeof(float));
	outMesh.normals = (float*)RL_MALLOC(outMesh.vertexCount * 3 * sizeof(float));
	outMesh.texcoords = (float*)RL_MALLOC(outMesh.vertexCount * 2 * sizeof(float));
	outMesh.colors = NULL;
	//outMesh.colors = (unsigned char*)RL_MALLOC(outMesh.vertexCount*4*sizeof(unsigned char));

	int fCounter = 0;
	// Move vertecies data
	for (size_t i = 0; i < vCounter; i++)
	{
		outMesh.vertices[fCounter]		= mapVerticies[i].x;
		outMesh.vertices[fCounter + 1]	= mapVerticies[i].y;
		outMesh.vertices[fCounter + 2]	= mapVerticies[i].z;
		fCounter += 3;
	}

	fCounter = 0;
	// Move normals data
	for (size_t i = 0; i < nCounter; i++)
	{
		outMesh.normals[fCounter]		= mapNormals[i].x;
		outMesh.normals[fCounter + 1]	= mapNormals[i].y;
		outMesh.normals[fCounter + 2]	= mapNormals[i].z;
		fCounter += 3;
	}

	fCounter = 0;
	// Move texcoord data
	for (size_t i = 0; i < tcCounter; i++)
	{
		outMesh.texcoords[fCounter]		= mapTexcoord[i].x;
		outMesh.texcoords[fCounter + 1] = mapTexcoord[i].y;
		fCounter += 2;
	}

	// fCounter = 0;
	// // Move colors data
	// for (size_t i = 0; i < cCounter; i++)
	// {
	// 	outMesh.colors[fCounter] 	 = 255;
	// 	outMesh.colors[fCounter + 1] = 255;
	// 	outMesh.colors[fCounter + 2] = 255;
	// 	outMesh.colors[fCounter + 3] = 255;
	// 	fCounter += 4;
	// }

	RL_FREE(mapVerticies);
	RL_FREE(mapNormals);
	RL_FREE(mapTexcoord);
	RL_FREE(mapColors);

	UploadMesh(&outMesh, false);
}

void MazeGenerator::GenerateCollisionMask(MazeInfo& info, std::vector<char>& collisionMask)
{
	LayerInfo* layerInfo;

	for (size_t i = 0; i < 3; i++)
	{
		if (info.layers[i].name.compare("Walls") == 0)
		{
			layerInfo = &info.layers[i];
		}
	}

	if(!layerInfo)
	{
		return;
	}

	collisionMask.clear();
	collisionMask.reserve(layerInfo->dataSize);

	const char wallID = 1;

	for (size_t i = 0; i < layerInfo->dataSize; i++)
	{
		char pushValue = 0;
		if(((char*)layerInfo->data)[i] == wallID)
		{
			pushValue = 1;
		}	
		collisionMask.push_back(pushValue);
	}
}

void MazeGenerator::GenerateMazeMap(const std::string& name, Mesh& maze, std::vector<char>& collisionMask)
{
	int size = 0;

	std::ifstream file(name, std::ios::binary);
	if (!file)
	{
		// error handling
	}
	MazeGenerator::MazeInfo info;

	ParseFile(file, info);
	GenerateCollisionMask(info, collisionMask);
	GenerateMesh(info, maze);
}