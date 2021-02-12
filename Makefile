CXX = g++
CXXFLAGS = -O2 -Wall -Wextra
BUILD = ./build
OBJ_DIR = $(BUILD)/objects
APP_DIR = $(BUILD)/apps
SRC = ./src

all: $(APP_DIR)/main

$(APP_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/core.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC)/main.cpp $(SRC)/Timer.hpp $(SRC)/core.cpp $(SRC)/core.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/core.o: $(SRC)/core.cpp $(SRC)/core.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

create_dirs:
	@mkdir $(BUILD)
	@mkdir $(APP_DIR)
	@mkdir $(OBJ_DIR)

clean:
	@rm $(APP_DIR)/* $(OBJ_DIR)/* *.csv

info:
	@echo "[*] Application dir: $(APP_DIR)"
	@echo "[*] Object dir: $(OBJ_DIR)"
	@echo "[*] Sources: $(SRC)"
