MAKEFILE_PATH := $(subst /,\,$(abspath $(lastword $(MAKEFILE_LIST))))
DIR := $(dir $(MAKEFILE_PATH))
LIB_FOLDER_PATH := C:\msys64\mingw64\lib

STUDIO_LIB_C := $(DIR)studio2.c
STUDIO_LIB_O := $(DIR)studioLibrary.o
TEST_C := $(DIR)hello10_libreria.c
TEST_BIN := $(DIR)hello10_libreria.exe

installLibrary:
	gcc -c $(STUDIO_LIB_C) -o $(STUDIO_LIB_O)
	ar rcs $(LIB_FOLDER_PATH)\studioLibrary.a $(STUDIO_LIB_O)

test:
	gcc $(TEST_C) -l:studioLibrary.a -o $(TEST_BIN)
	$(TEST_BIN)

uninstallLibrary:
	del $(LIB_FOLDER_PATH)\studioLibrary.a

