#include"ShaderSystemDDEngine.h"

using namespace std;

string GetFile(const char* _FileName) 
{
	ifstream in(_FileName, ios::binary);
	
	

	if (in)
	{
		string _Contents;
		in.seekg(0, ios::end);
		_Contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&_Contents[0], _Contents.size());
		in.close();
		return(_Contents);
	}
	throw(errno);
	
	
	
	
}

MainShaderSystem::MainShaderSystem(const char* _VertFile, const char* _FragFile) 
{
	string _VertCode = GetFile(_VertFile);
	string _FragCode = GetFile(_FragFile);

	const char* _VertSource = _VertCode.c_str();
	const char* _FragSource = _FragCode.c_str();

	//Добавление шейдеров
	//Добавление вертекс шейдера
	GLuint _VertexShader = glCreateShader(GL_VERTEX_SHADER); 
	//добавление вертекс шейдера к Верткс Шейдер Объекту
	glShaderSource(_VertexShader, 1, &_VertSource, NULL);
	//Компиляция шейдеров
	glCompileShader(_VertexShader); 

	//Добавление фрагментого шейдера
	GLuint _FragShader = glCreateShader(GL_FRAGMENT_SHADER); 
	//добавление фрагментова шейдера к Фрагменто Шейдер Объекту
	glShaderSource(_FragShader, 1, &_FragSource, NULL);
	//Компиляция шейдеров
	glCompileShader(_FragShader); 
	 
	_ID = glCreateProgram(); 
	glAttachShader(_ID, _VertexShader); 
	glAttachShader(_ID, _FragShader); 
	glLinkProgram(_ID); 

	glDeleteShader(_VertexShader); 
	glDeleteShader(_FragShader); 

}

void MainShaderSystem::Online() 
{
	glUseProgram(_ID);
}

void MainShaderSystem::Offline()
{
	glDeleteProgram(_ID);
}