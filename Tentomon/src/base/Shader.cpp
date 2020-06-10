#include "Shader.h"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path,
	const char* tessellation_control_file_path, const char* tessellation_evaluation_file_path,
	const char* geometry_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint TessellationControlShaderID = 0;
	if (tessellation_control_file_path != NULL) TessellationControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
	GLuint TessellationEvaluationShaderID = 0;
	if (tessellation_evaluation_file_path != NULL) TessellationEvaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	GLuint GeometryShaderID = 0;
	if (geometry_file_path != NULL) GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

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

	// Read the Tessellation Control Shader code from the file
	std::string TessellationControlShaderCode;
	if (tessellation_control_file_path != NULL) {
		std::ifstream TessellationControlShaderStream(tessellation_control_file_path, std::ios::in);
		if (TessellationControlShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << TessellationControlShaderStream.rdbuf();
			TessellationControlShaderCode = sstr.str();
			TessellationControlShaderStream.close();
		}
	}

	// Read the Tessellation Evaluation Shader code from the file
	std::string TessellationEvaluationShaderCode;
	if (tessellation_evaluation_file_path != NULL) {
		std::ifstream TessellationEvaluationShaderStream(tessellation_evaluation_file_path, std::ios::in);
		if (TessellationEvaluationShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << TessellationEvaluationShaderStream.rdbuf();
			TessellationEvaluationShaderCode = sstr.str();
			TessellationEvaluationShaderStream.close();
		}
	}

	// Read the Geometry Shader code from the file
	std::string GeometryShaderCode;
	if (geometry_file_path != NULL) {
		std::ifstream GeometryShaderStream(geometry_file_path, std::ios::in);
		if (GeometryShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << GeometryShaderStream.rdbuf();
			GeometryShaderCode = sstr.str();
			GeometryShaderStream.close();
		}
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

	// Compile Tessellation Control Shader
	if (tessellation_control_file_path != NULL) {
		printf("Compiling shader : %s\n", tessellation_control_file_path);
		char const* TessellationControlSourcePointer = TessellationControlShaderCode.c_str();
		glShaderSource(TessellationControlShaderID, 1, &TessellationControlSourcePointer, NULL);
		glCompileShader(TessellationControlShaderID);

		// Check Fragment Shader
		glGetShaderiv(TessellationControlShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(TessellationControlShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> TessellationControlShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(TessellationControlShaderID, InfoLogLength, NULL, &TessellationControlShaderErrorMessage[0]);
			printf("%s\n", &TessellationControlShaderErrorMessage[0]);
		}
	}

	// Compile Tessellation Evaluation Shader
	if (tessellation_evaluation_file_path != NULL) {
		printf("Compiling shader : %s\n", tessellation_evaluation_file_path);
		char const* TessellationEvaluationSourcePointer = TessellationEvaluationShaderCode.c_str();
		glShaderSource(TessellationEvaluationShaderID, 1, &TessellationEvaluationSourcePointer, NULL);
		glCompileShader(TessellationEvaluationShaderID);

		// Check Tessellation Evaluation Shader
		glGetShaderiv(TessellationEvaluationShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(TessellationEvaluationShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> TessellationEvaluationShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(TessellationEvaluationShaderID, InfoLogLength, NULL, &TessellationEvaluationShaderErrorMessage[0]);
			printf("%s\n", &TessellationEvaluationShaderErrorMessage[0]);
		}
	}

	// Compile Geometry Shader
	if (geometry_file_path != NULL) {
		printf("Compiling shader : %s\n", geometry_file_path);
		char const* GeometrySourcePointer = GeometryShaderCode.c_str();
		glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
		glCompileShader(GeometryShaderID);

		// Check Fragment Shader
		glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
			printf("%s\n", &GeometryShaderErrorMessage[0]);
		}
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	if (tessellation_control_file_path != NULL) glAttachShader(ProgramID, TessellationControlShaderID);
	if (tessellation_evaluation_file_path != NULL) glAttachShader(ProgramID, TessellationEvaluationShaderID);
	if (geometry_file_path != NULL) glAttachShader(ProgramID, GeometryShaderID);
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

	if (tessellation_control_file_path != NULL) {
		glDetachShader(ProgramID, TessellationControlShaderID);
		glDeleteShader(TessellationControlShaderID);
	}
	if (tessellation_evaluation_file_path != NULL) {
		glDetachShader(ProgramID, TessellationEvaluationShaderID);
		glDeleteShader(TessellationEvaluationShaderID);
	}
	if (geometry_file_path != NULL) {
		glDetachShader(ProgramID, GeometryShaderID);
		glDeleteShader(GeometryShaderID);
	}

	return ProgramID;
}


Shader::Shader()
{
}

Shader::Shader(const char * vertex_file_path, const char * fragment_file_path,
	const char* tessellation_control_file_path, const char* tessellation_evaluation_file_path,
	const char* geometry_file_path)
{
	Shader::programID = LoadShaders(vertex_file_path, fragment_file_path,
		tessellation_control_file_path, tessellation_evaluation_file_path,
		geometry_file_path);
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

void Shader::setUniformBlock(const GLchar* name, GLuint index)
{
	if (Shader::uniformIds.find(name) == Shader::uniformIds.end()) {
		Shader::uniformIds[name] = glGetUniformBlockIndex(Shader::programID, name);
	}

	GLuint temp_prog_id = Shader::uniformIds[name];

	glUniformBlockBinding(Shader::programID, temp_prog_id, index);
}

void Shader::useShader()
{
	glUseProgram(Shader::programID);
}

void Shader::stopShader()
{
	glUseProgram(0);
}

bool Shader::operator==(const Shader& b) {
	return b.programID == programID;
}

bool Shader::operator!=(const Shader& b) {
	return b.programID != programID;
}