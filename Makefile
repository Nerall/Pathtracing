CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = main.cpp Camera.cpp Color.cpp Image.cpp Light.cpp Object.cpp Point_Light.cpp Ray.cpp Scene.cpp Sphere.cpp Texture_Material.cpp Uniform_Texture.cpp Vector.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	rm -rf $(OBJ) $(EXEC)