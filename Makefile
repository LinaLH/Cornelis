# Makefile

# Variables
CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
PPM_DIR = cornelis
TARGET = $(BIN_DIR)/programme

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Fichiers PPM
#PPM_FILES = c Piet_hello.ppm adder.ppm alpha.ppm cowsay.ppm euclide.ppm fact.ppm hw2.ppm hw3.ppm hw4.ppm mondrian.ppm pi.ppm pietquest.ppm power.ppm tetris.ppm
PPM_TARGETS = $(patsubst %,$(BIN_DIR)/%,$(99bottles.ppm))

# Compilation
$(TARGET): $(OBJS) $(PPM_TARGETS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle générique pour copier les fichiers PPM
$(BIN_DIR)/%.ppm: $(PPM_DIR)/%.ppm | $(BIN_DIR)
	cp $< $@

# Création des répertoires si nécessaire
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/programme $(BIN_DIR)/*.ppm

# Phony target pour éviter conflits avec des fichiers réels ayant le même nom
.PHONY: clean
