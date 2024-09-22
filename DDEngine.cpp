#include <iostream>
#include <glad.h>;
#include <glfw3.h>;
#include <khrplatform.h>
using namespace std;

const char* _VertShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* _FragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\n\0";



int main(){



	//Инцилизация OpenGL
	glfwInit();

	//Подсказки для OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat _Vert[] =
	{
		-0.5f,-0.5f * float(sqrt(3))/3,0.0f,
		0.5f,-0.5f * float(sqrt(3))/3,0.0f,
		0.0f,0.5f * float(sqrt(3))*2/3,0.0f,
	};

	//Создание окна
	//GLFWindow - класс окна openGL, функция: glfwCreateWindow - создаёт окно
	GLFWwindow* _Window = glfwCreateWindow(800,600, "DDEngine", NULL, NULL);
	if (_Window == NULL) 
	{
		cout << "Fail: create window" << endl;
		glfwTerminate();
		return -1;
	}

	//Запуск окна через: glfwMakeContextCurrent 
	glfwMakeContextCurrent(_Window);
	gladLoadGL();
	
	glViewport(0,0,800,800);
	
	//Добавление шейдеров
	//Добавление вертекс шейдера
	GLuint _VertexShader = glCreateShader(GL_VERTEX_SHADER);
	//добавление вертекс шейдера к Верткс Шейдер Объекту
	glShaderSource(_VertexShader,1,&_VertShaderSource, NULL);
	//Компиляция шейдеров
	glCompileShader(_VertexShader);

	//Добавление фрагментого шейдера
	GLuint _FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//добавление фрагментова шейдера к Фрагменто Шейдер Объекту
	glShaderSource(_FragShader, 1, &_FragShaderSource, NULL);
	//Компиляция шейдеров
	glCompileShader(_FragShader);

	GLuint _ShaderProgramm = glCreateProgram();
	glAttachShader(_ShaderProgramm, _VertexShader);
	glAttachShader(_ShaderProgramm, _FragShader);
	glLinkProgram(_ShaderProgramm);

	glDeleteShader(_VertexShader);
	glDeleteShader(_FragShader);

	//Отрисовка
	//Создание VAO и VBO
	GLuint _VBO, _VAO;

	//Генерация буферов для VBO 
	//Генерация массив из векторов для VAO
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1,&_VBO);

	//Сделать VAO текущим массивом из вертексов
	glBindVertexArray(_VAO);

	//За-биндить VBO пот GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	///Представляем вертксы в VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(_Vert), _Vert,GL_STATIC_DRAW);


	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	glClearColor(0.07f,0.13f,0.17f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(_Window);

	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window)) 
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(_ShaderProgramm);
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		glfwSwapBuffers(_Window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1,&_VBO);
	glDeleteBuffers(1, &_VAO);
	glDeleteProgram(_ShaderProgramm);



	glfwTerminate();
	return 0;
}

