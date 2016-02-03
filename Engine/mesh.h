#pragma once

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "obj_loader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
	{
		this->pos = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	inline glm::vec3*  GetPos() { return &pos; }
	inline glm::vec2*  GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

protected:

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	


};


class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	void Draw();

	virtual ~Mesh();

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,			//da ordinea desenarii vertexurilor
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	void InitMesh(const IndexedModel& model);



};

