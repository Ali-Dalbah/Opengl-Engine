yis: main.cpp Model.o Text.o SoundObject.o SoundDevice.o SoundBuffer.o Mesh.o Window.o Rect.o Camera.o Component.o Shader.o Scene.o SkyBox.o VAO.o VBO.o EBO.o Texture.o Button2D.o glad.o
	g++ main.cpp Model.o Mesh.o SoundObject.o SoundDevice.o SoundBuffer.o Text.o Rect.o Camera.o Window.o Component.o Shader.o Scene.o VAO.o SkyBox.o VBO.o EBO.o Texture.o Button2D.o glad.o -o main -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lsndfile -lopenal -lassimp -lfreetype
	@echo "Cleaning..."
	rm *.o

SoundObject.o:
	g++ -c src/SoundObject.cpp -o SoundObject.o

SoundDevice.o:
	g++ -c src/SoundDevice.cpp -o SoundDevice.o

SoundBuffer.o:
	g++ -c src/SoundBuffer.cpp -o SoundBuffer.o

Text.o: src/Text.cpp
	g++ -c src/Text.cpp -I/usr/include/freetype2 -o Text.o

Rect.o: src/Rect.cpp
	g++ -c src/Rect.cpp -o Rect.o

Component.o: src/Component.cpp
	g++ -c src/Component.cpp -o Component.o

Window.o: src/Window.cpp
	g++ -c src/Window.cpp -o Window.o

Scene.o: src/Scene.cpp
	g++ -c src/Scene.cpp -o Scene.o

Button2D.o: src/Button2D.cpp
	g++ -c src/Button2D.cpp -o Button2D.o

SkyBox.o: src/SkyBox.cpp
	g++ -c src/SkyBox.cpp -o SkyBox.o

Model.o: src/Model.cpp
	g++ -c src/Model.cpp -o Model.o

Mesh.o: src/Mesh.cpp
	g++ -c src/Mesh.cpp -o Mesh.o

Camera.o: src/Camera.cpp
	g++ -c src/Camera.cpp -o Camera.o

Texture.o: src/Texture.cpp
	g++ -c src/Texture.cpp -o Texture.o

Shader.o: src/Shader.cpp
	g++ -c src/Shader.cpp -o Shader.o

VAO.o: src/VAO.cpp
	g++ -c src/VAO.cpp -o VAO.o

VBO.o: src/VBO.cpp
	g++ -c src/VBO.cpp -o VBO.o

EBO.o: src/EBO.cpp
	g++ -c src/EBO.cpp -o EBO.o

glad.o: src/glad.c
	g++ -c src/glad.c -o glad.o
