MAKEFILE_PATH := $(subst /,\,$(abspath $(lastword $(MAKEFILE_LIST))))
DIR := $(dir $(MAKEFILE_PATH))

BIN := $(DIR)TablasDeConversion.exe
TABLA_CONVERSION_OBJ := $(DIR)TablasDeConversion.o
CONVERSION_OBJ := $(DIR)Conversion.o
TABLA_CONVERSION_C := $(DIR)TablasDeConversion.c
CONVERSION_C := $(DIR)Conversion.c
CONVERSION_H := $(DIR)Conversion.h
TEST_BIN := $(DIR)ConversionTest.exe
TEST_OBJ := $(DIR)ConversionTest.o
TEST_C := $(DIR)ConversionTest.c

all: $(TEST_BIN) $(BIN)
	$(TEST_BIN)
	$(BIN)

test: $(TEST_BIN)
	$(TEST_BIN)

run: $(BIN)
	$(BIN)

$(TEST_BIN): $(TEST_OBJ) $(CONVERSION_OBJ)
	gcc $(TEST_OBJ) $(CONVERSION_OBJ) -o $(TEST_BIN)

$(TEST_OBJ): $(TEST_C) $(CONVERSION_H)
	gcc -c $(TEST_C) -std=c18 -o $(TEST_OBJ)

$(BIN): $(TABLA_CONVERSION_OBJ) $(CONVERSION_OBJ)
	gcc $(TABLA_CONVERSION_OBJ) $(CONVERSION_OBJ) -o $(BIN)

$(TABLA_CONVERSION_OBJ): $(TABLA_CONVERSION_C) $(CONVERSION_H)
	gcc -c $(TABLA_CONVERSION_C) $(C_FLAGS) -o $(TABLA_CONVERSION_OBJ)

$(CONVERSION_OBJ): $(CONVERSION_C) $(CONVERSION_H)
	gcc -c $(CONVERSION_C) -std=c18 -o $(CONVERSION_OBJ)

clean:
	del $(CONVERSION_OBJ)
	del $(BIN)
	del $(TABLA_CONVERSION_OBJ)
	del $(TEST_BIN)
	del $(TEST_OBJ)

