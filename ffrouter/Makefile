# Object files
OBJ = main.o ffrouter.o rdma_api.o shared_memory.o verbs_cmd.o

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O3
LDFLAGS = -lrdmacm -libverbs -lpthread -lrt

# Target
TARGET = router

# Default target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Compile object files
main.o: main.cpp constant.h ffrouter.h rdma_api.h shared_memory.h log.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ffrouter.o: ffrouter.cpp
	$(CXX) $(CXXFLAGS) -c ffrouter.cpp

rdma_api.o: rdma_api.cpp
	$(CXX) $(CXXFLAGS) -c rdma_api.cpp

shared_memory.o: shared_memory.cpp
	$(CXX) $(CXXFLAGS) -c shared_memory.cpp

verbs_cmd.o: verbs_cmd.cpp
	$(CXX) $(CXXFLAGS) -c verbs_cmd.cpp

# Clean up
clean:
	rm -f $(TARGET) $(OBJ)
