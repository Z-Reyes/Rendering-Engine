#include "ObjectFileReader.h"

ObjectFileReader::ObjectFileReader(std::string path, std::string name)
{
	float * list;
	verticesSize = ParseObjectFile(path, list);
	if (list != nullptr) {
		//verticesSize = sizeof(list) / sizeof(float);
		std::cout << "verticesSize is: " << verticesSize << std::endl;
		SetVertices(list);
		indicesSize = verticesSize / 8;
		std::cout << "indicesSize is: " << indicesSize << std::endl;
		unsigned int* indices = new unsigned int[indicesSize];
		for (int i = 0; i < indicesSize; i++) {
			indices[i] = i;
		}

		SetIndices(indices);
		delete list;
		delete indices;

	}
	else {
		std::cout << "Something went wrong with reading the file" << std::endl;
	}
	SetClassName(name);
}

ObjectFileReader::~ObjectFileReader()
{
}
/*
The code for this function was taken from 
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/
int ObjectFileReader::ParseObjectFile(std::string in, float * &re)
{
	

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file;
	fopen_s(&file, in.c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return -1;
	}
	unsigned int counter = 0;
	while (1) {
		counter++;
		char lineHeader[256];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF) {
			std::cout << "End of file reached" << std::endl;
			break; // EOF = End Of File. Quit the loop.
		}

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0],
				&normalIndex[0], &vertexIndex[1],
				&uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2],
				&normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return -1;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	
		//This is the end of the code I took from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
		// The rest I made myself.

		//First, allocate a float array for the program
	unsigned int vS = vertexIndices.size() * 8;
	re = new float[vS]; //We hard-code the number 7 because that's all our parser does anyway.
	std::cout << "Counter value was: " << counter << std::endl;
	std::cout << "Size of re is " << vertexIndices.size() * 8 << std::endl;
	std::cout << "Size of vertex indices is: " << vertexIndices.size() << std::endl;
	int currNum = 0;
	for (unsigned int index = 0; index < vertexIndices.size(); index++) {
		//std::cout << "currNum is " << currNum << std::endl;
		int vertexLoc = vertexIndices.at(index) - 1;
		int texLoc = uvIndices.at(index) - 1;
		int normalLoc = normalIndices.at(index) - 1;

		re[currNum] = temp_vertices.at(vertexLoc).x;
		currNum++;
		re[currNum] = temp_vertices.at(vertexLoc).y;
		currNum++;
		re[currNum] = temp_vertices.at(vertexLoc).z;
		currNum++;
		re[currNum] = temp_uvs.at(texLoc).x;
		currNum++;
		re[currNum] = temp_uvs.at(texLoc).y;
		currNum++;
		re[currNum] = temp_normals.at(normalLoc).x;
		currNum++;
		re[currNum] = temp_normals.at(normalLoc).y;
		currNum++;
		re[currNum] = temp_normals.at(normalLoc).z;
		currNum++;
	}
	return vS;


}
