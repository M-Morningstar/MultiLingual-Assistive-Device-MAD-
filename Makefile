CXX=g++
CXXFLAGS=-g -Wall -std=c++17
SRC_DIR=./src
LIB_DIR=./lib

# Specify include directories for each library
INCLUDES=-I$(LIB_DIR)/curl/include -I$(LIB_DIR)/portaudio/include -I$(LIB_DIR)/jsoncpp-master/include -I$(LIB_DIR)/base64/include -I$(LIB_DIR)/libao/include/ao -I$(LIB_DIR)/soxr-installed/include -I$(LIB_DIR)/SDL2/x86_64-w64-mingw32/include/SDL2

# Specify the lib directories for libraries that have them
LDFLAGS=-L$(LIB_DIR)/curl/lib -L$(LIB_DIR)/portaudio/build -L$(LIB_DIR)/libao/src/.libs -L$(LIB_DIR)/soxr-installed/lib -L$(LIB_DIR)/SDL2/x86_64-w64-mingw32/lib

# Specify the libraries to link against
LIBS=-lcurl -lportaudio -ljsoncpp -lao -lsoxr -lSDL2

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXECUTABLE)
