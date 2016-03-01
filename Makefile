#Windows build

LIBS = -lSDL2 -lGL -lSDL2_image -g

C_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(C_FILES:.cpp=.o)))

open_spaceships: $(OBJ_FILES)
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	g++ $(CFLAGS) -c -g -o $@ $<
