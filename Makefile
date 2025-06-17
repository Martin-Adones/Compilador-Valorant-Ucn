CC = gcc
CFLAGS = -Wall -I./include
FLEX = flex
BISON = bison

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Archivos fuente
BISON_SRC = $(SRC_DIR)/valorant.y
FLEX_SRC = $(SRC_DIR)/valorant.l
AST_SRC = $(SRC_DIR)/ast.c
MAIN_SRC = $(SRC_DIR)/main.c
INTERPRETER_SRC = $(SRC_DIR)/interpreter.c

# Archivos generados
BISON_C = $(BUILD_DIR)/valorant.tab.c
BISON_H = $(BUILD_DIR)/valorant.tab.h
FLEX_C = $(BUILD_DIR)/lex.yy.c

# Archivos objeto
OBJS = $(BUILD_DIR)/valorant.tab.o $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/ast.o \
       $(BUILD_DIR)/main.o $(BUILD_DIR)/interpreter.o

# Ejecutable
TARGET = $(BIN_DIR)/valorant

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/valorant.tab.o: $(BISON_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lex.yy.o: $(FLEX_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/ast.o: $(AST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/interpreter.o: $(INTERPRETER_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BISON_C) $(BISON_H): $(BISON_SRC) | $(BUILD_DIR)
	$(BISON) -d $< -o $(BISON_C)

$(FLEX_C): $(FLEX_SRC) $(BISON_H) | $(BUILD_DIR)
	$(FLEX) -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Regla para ejecutar ejemplos
run: all
	@echo "Ejecutando ejemplo..."
	./$(BIN_DIR)/valorant < examples/fizzbuzz.val

.PHONY: all clean
