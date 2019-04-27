#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>
VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
	//Let's print the data.
	//float * raw = (float*)data;
	//for (int i = 0; i < 24; i++) {
	//	std::cout << raw[i] << std::endl;
	//}
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_rendererID));
}
void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}
void VertexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}