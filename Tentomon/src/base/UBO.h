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
	unsigned int ID;
	GLint OFFSET_ALIGNMENT;

	UBO();
	~UBO();

	struct data_location
	{
		int offset;
		int size;
	};

	std::map< int, std::map< std::string, data_location> > uniform_variables;
	std::map< int, int> uniform_size;
	std::map< int, data_location> uniform_real_size;
	std::vector<int> range_order;

	template<typename T>
	void addUniform(const char* name, int index)
	{
		int variable_size = sizeof(T);

		if (uniform_size.find(index) == uniform_size.end()) {
			uniform_size[index] = 0;
			range_order.push_back(index);
		}

		data_location temp_dl;
		temp_dl.size = variable_size;
		temp_dl.offset = uniform_size[index];
		uniform_variables[index][name] = temp_dl;

		uniform_size[index] += variable_size;
	}

	int calculateRealSize();

	void createUBO();

	void setUniform(const char* name, int index, const void* data);




};

