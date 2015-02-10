CPP_FILES := $(shell find src/ -type f -name '*.cpp')
OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(CPP_FILES))
CC := i686-w64-mingw32-g++
CC_FLAGS := -std=c++11 -g
LD_FLAGS := -static
LIBS := -lws2_32

AvocadoBot.exe: $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o bin/$@ $(addprefix obj/,$(notdir $^)) $(LIBS)

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -c -o obj/$(notdir $@) $<

clean:
	rm -rf obj/ bin/

dirs:
	mkdir -p obj/ bin/