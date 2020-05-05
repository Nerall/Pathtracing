CXX = g++-9
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = main.cpp Camera.cpp Light.cpp Plane.cpp Point_Light.cpp Ray.cpp Scene.cpp Sphere.cpp Diffuse_texture.cpp Vector.cpp Object.cpp Refracted_reflected_texture.cpp Phong.cpp Path_tracing_texture.cpp Distant_light.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)