#pragma once
#include <glad/glad.h>
#include <map>
#include <vector>
#include <typeinfo>
#include <string>
#include <glm/glm.hpp>

class UBO
{
public:
	struct data_location
	{
		int offset;
		int size;
	};

	unsigned int ID;
	GLint OFFSET_ALIGNMENT;

	std::map< int, std::map< std::string, data_location> > uniform_variables;

	UBO();
	~UBO();

	void addUniform(const char* name, int index, int var_size);
	void createUBO();
	void setUniform(const char* name, int index, const void* data);

private:
	int calculateRealSize();
	std::map< int, int> uniform_size;
	std::map< int, data_location> uniform_real_size;
	std::vector<int> range_order;
};

