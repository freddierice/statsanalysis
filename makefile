CC=g++
LD=g++
CFLAGS=-Wall -lpthread
EXEC_NAME=stats_analysis

SRC_DIR=source
BUILD_DIR=build/linux
BIN_DIR=build/linux

CFLAGS_OBJ=$(CFLAGS) -c
EXEC=$(BIN_DIR)/$(EXEC_NAME)

SRC=$(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ=$(patsubst src/%.c,build/%.o,$(SRC))
#INCLUDES=$(addprefix -I,$(SRC_DIR))
Includes=-Isrc

vpath %.c $(SRC_DIR)

define make-objs
$1/%.o: %.c
	$(CC) $$< -o $$@ $(CFLAGS_OBJ) $(INCLUDES)
endef

.PHONY: all checkdirs clean

all: checkdirs $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $(EXEC) $(CFLAGS)
$(foreach bdir,$(BUILD_DIR),$(eval $(call make-objs,$(bdir))))

checkdirs: $(BUILD_DIR) $(BIN_DIR)
$(BUILD_DIR): 
	@mkdir -p $@
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)


