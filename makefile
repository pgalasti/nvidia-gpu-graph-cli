CC=g++
INCLUDE_DIRS=-I ./include
OPTIONS=-std=c++17
REQUIRED_FILES=./src/StringUtils.cpp ./src/main.cpp ./src/NvidiaSmiParser.cpp ./src/GraphOutputCli.cpp 
OUTPUT=gpu-graph-cli
INSTALL_DIR=~/tools
$(OUTPUT): $(REQUIRED_FILES)
	$(info Builing gpu-graph-cli executable...)
	$(CC) $(OPTIONS) $(INCLUDE_DIRS) -o $(OUTPUT) $(REQUIRED_FILES)

clean: 
	$(info Removing executable...)
	rm $(OUTPUT)

install: $(OUTPUT)
	$(info Installing executable...)
	cp $(OUTPUT) $(INSTALL_DIR)
