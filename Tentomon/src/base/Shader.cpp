#include "Shader.h"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


Shader::Shader(const char * vertex_file_path, const char * fragment_file_path)
{
	Shader::programID = LoadShaders(vertex_file_path, fragment_file_path);
}


Shader::~Shader()
{
}

void Shader::setUniform(const GLchar* name, int value)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformLocation(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniform1i(temp_prog_id, value);
}

void Shader::setUniform(const GLchar* name, float value)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformLocation(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniform1f(temp_prog_id, value);
}

void Shader::setUniform(const GLchar* name, glm::vec2 value)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformLocation(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniform2fv(temp_prog_id, 1, &value[0]);
}

void Shader::setUniform(const GLchar *name, glm::vec3 value)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformLocation(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniform3fv(temp_prog_id, 1, &value[0]);
}

void Shader::setUniform(const GLchar *name, glm::mat4 value, GLboolean transpose)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformLocation(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniformMatrix4fv(temp_prog_id, 1, transpose, &value[0][0]);
}

void Shader::useShader()
{
	glUseProgram(Shader::programID);
}

void Shader::stopShader()
{
	glUseProgram(0);
}
