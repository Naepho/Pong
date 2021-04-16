CXX      := g++
CXXFLAGS := -Wall -Wextra -mwindows
LDFLAGS  := -L lib -lsfml-system -lsfml-window -lsfml-audio -lsfml-graphics -lsfml-network
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := ./bin
TARGET   := pong
INCLUDE  := -I include
SRC      :=                      \
   $(wildcard src/module1/*.cpp) \
   $(wildcard src/module2/*.cpp) \
   $(wildcard src/*.cpp)         \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@if not exist "$(APP_DIR)" mkdir "$(APP_DIR)"
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rmdir /s "./build"

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
                       