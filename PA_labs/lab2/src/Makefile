CXX = g++
CXXFLAGS = -std=c++11 -pthread
TARGET = program
SOURCES = main.cpp FineGrainedLock.cpp CoarseGrainedLock.cpp PipelineTest.cpp LinkedList.cpp LockFreeList.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
