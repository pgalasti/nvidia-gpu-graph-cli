CC=g++
INCLUDE_DIRS=-I ./include -I ./libs/g-lib/include
LIBS_DIRS=
GLIB=
OPTIONS=-std=c++23
POST_OPS=-lpthread
REQUIRED_FILES=./src/main.cpp ./src/NvidiaSmiParser.cpp ./src/GraphOutputCli.cpp ./libs/g-lib/src/util/StringParser.cpp
OUTPUT=gpu-graph-cli
INSTALL_DIR=~/tools
$(OUTPUT): $(REQUIRED_FILES)
	$(info Builing gpu-graph-cli executable...)
	$(CC) $(OPTIONS) $(INCLUDE_DIRS) -o $(OUTPUT) $(REQUIRED_FILES) $(LIBS_DIRS) $(GLIB) $(POST_OPS)

clean: 
	$(info Removing executable...)
	rm $(OUTPUT)

install: $(OUTPUT)
	$(info Installing executable...)
	cp $(OUTPUT) $(INSTALL_DIR)
