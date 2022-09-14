CC=g++
INCLUDE_DIRS=-I ./include
OPTIONS=-std=c++17
REQUIRED_FILES=./src/StringUtils.cpp ./src/main.cpp ./src/NvidiaSmiParser.cpp ./src/GraphOutputCli.cpp 
OUTPUT=-o gpu-graph-cli
build: $(REQUIRED_FILES)
	$(info Builing gpu-graph-cli executable...)
	$(CC) $(OPTIONS) $(INCLUDE_DIRS) $(OUTPUT) $(REQUIRED_FILES)
