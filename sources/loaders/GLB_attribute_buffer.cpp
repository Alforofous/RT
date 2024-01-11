#include "loaders/GLB_attribute_buffer.hpp"
#include "loaders/GLB_utilities.hpp"
#include <cstddef>
#include <iostream>

GLB_attribute_buffer::GLB_attribute_buffer(GLvoid *glb_buffer, GLsizeiptr byte_offset, GLsizeiptr vertex_count, std::string name, GLsizeiptr component_count, GLenum gl_data_type)
{
	this->name = name;
	this->component_count = component_count;
	this->gl_data_type = gl_data_type;
	this->vertex_count = vertex_count;
	this->byte_size = vertex_count * component_count * GLB_utilities::gl_data_type_size(gl_data_type);
	if (this->byte_size == 0)
		throw std::runtime_error("GLB_attribute_buffer::GLB_attribute_buffer(): size == 0 for attribute: " + name);

	if (gl_data_type == GL_BYTE)
		this->data = (GLvoid *)new GLbyte[byte_size];
	else if (gl_data_type == GL_UNSIGNED_BYTE)
		this->data = (GLvoid *)new GLubyte[byte_size];
	else if (gl_data_type == GL_SHORT)
		this->data = (GLvoid *)new GLshort[byte_size];
	else if (gl_data_type == GL_UNSIGNED_SHORT)
		this->data = (GLvoid *)new GLushort[byte_size];
	else if (gl_data_type == GL_INT)
		this->data = (GLvoid *)new GLint[byte_size];
	else if (gl_data_type == GL_UNSIGNED_INT)
		this->data = (GLvoid *)new GLuint[byte_size];
	else if (gl_data_type == GL_FLOAT)
		this->data = (GLvoid *)new GLfloat[byte_size];
	else if (gl_data_type == GL_DOUBLE)
		this->data = (GLvoid *)new GLdouble[byte_size];
	else
		throw std::runtime_error("GLB_attribute_buffer::GLB_attribute_buffer(): unknown gl_data_type for attribute: " + name);

	memcpy(this->data, (GLubyte *)glb_buffer + byte_offset, this->byte_size);
}

std::string GLB_attribute_buffer::get_data_string()
{
	GLsizeiptr data_type_size = GLB_utilities::gl_data_type_size(this->gl_data_type);
	if (data_type_size == 0)
		return ("");

	int component_count = 0;
	std::string buffer_data = this->name + " ATTRIBUTE [" + std::to_string(this->byte_size) + " bytes] of type [" + GLB_utilities::gl_data_type_to_string(this->gl_data_type) + "] with [" + std::to_string(this->component_count) + "] components and [" + std::to_string(this->vertex_count) + "] vertices:\n";
	for (uint8_t *ptr = (uint8_t *)this->data; ptr < (uint8_t *)this->data + this->byte_size; ptr += data_type_size)
	{
		if (this->gl_data_type == GL_BYTE)
			buffer_data += std::to_string((int)*(int8_t *)ptr);
		else if (this->gl_data_type == GL_UNSIGNED_BYTE)
			buffer_data += std::to_string((int)*(uint8_t *)ptr);
		else if (this->gl_data_type == GL_SHORT)
			buffer_data += std::to_string(*(int16_t *)ptr);
		else if (this->gl_data_type == GL_UNSIGNED_SHORT)
			buffer_data += std::to_string(*(uint16_t *)ptr);
		else if (this->gl_data_type == GL_INT)
			buffer_data += std::to_string(*(int32_t *)ptr);
		else if (this->gl_data_type == GL_UNSIGNED_INT)
			buffer_data += std::to_string(*(uint32_t *)ptr);
		else if (this->gl_data_type == GL_HALF_FLOAT)
			buffer_data += std::to_string(*(uint16_t *)ptr);
		else if (this->gl_data_type == GL_FLOAT)
			buffer_data += std::to_string(*(float *)ptr);
		else if (this->gl_data_type == GL_DOUBLE)
			buffer_data += std::to_string(*(double *)ptr);
		else
			buffer_data += "GL_NONE: [" + std::to_string((int)*(uint8_t *)ptr) + "]";
		if (component_count % this->component_count == this->component_count - 1)
			buffer_data += "\n";
		else
			buffer_data += " ";
		component_count += 1;
	}
	buffer_data += "\n";
	return (buffer_data);
}

std::string GLB_attribute_buffer::get_name()
{
	return (name);
}

GLsizeiptr GLB_attribute_buffer::get_component_count()
{
	return (component_count);
}

GLsizeiptr GLB_attribute_buffer::get_vertex_count()
{
	return (vertex_count);
}

GLsizeiptr GLB_attribute_buffer::get_element_count()
{
	return (vertex_count * component_count);
}

GLenum GLB_attribute_buffer::get_gl_data_type()
{
	return (gl_data_type);
}

GLvoid *GLB_attribute_buffer::get_data()
{
	return (data);
}

GLsizeiptr GLB_attribute_buffer::get_byte_size()
{
	return (byte_size);
}

GLB_attribute_buffer::~GLB_attribute_buffer()
{
	delete[] static_cast<uint8_t *>(this->data);
}