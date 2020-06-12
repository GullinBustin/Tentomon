#include "UBO.h"



UBO::UBO()
{
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &OFFSET_ALIGNMENT);
}

UBO::~UBO()
{
}

int UBO::calculateRealSize()
{
	int total_real_size = 0;
	for (unsigned int i = 0; i < range_order.size(); i++) {
		int index = range_order[i];
		int real_size = (int((uniform_size[index] - 1) / OFFSET_ALIGNMENT) + 1) * OFFSET_ALIGNMENT;

		data_location temp_dl;
		temp_dl.size = real_size;
		temp_dl.offset = total_real_size;

		uniform_real_size[index] = temp_dl;
		total_real_size += real_size;
	}

	return total_real_size;
}

void UBO::createUBO()
{
	int ubo_size = calculateRealSize();

	glGenBuffers(1, &ID);
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
	glBufferData(GL_UNIFORM_BUFFER, ubo_size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	for (unsigned int i = 0; i < range_order.size(); i++) {
		int index = range_order[i];
		int temp_size = uniform_size[index];
		glBindBufferRange(GL_UNIFORM_BUFFER, index, ID, uniform_real_size[index].offset, temp_size);
	}
}

void UBO::setUniform(const char* name, int index, const void* data)
{
	data_location temp_var = uniform_variables[index][name];
	data_location temp_uniform = uniform_real_size[index];

	glBindBuffer(GL_UNIFORM_BUFFER, ID);
	glBufferSubData(GL_UNIFORM_BUFFER, temp_var.offset + temp_uniform.offset, temp_var.size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
