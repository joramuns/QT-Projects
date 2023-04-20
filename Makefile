CC = gcc
CFLAGS:= -Wall -Werror -Wextra -g
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -fprofile-arcs --coverage
LCHECK= $(shell pkg-config --libs check)
PROJECT_NAME= 3D_Viewer
PROJECT_FILE := $(addsuffix .pro,$(PROJECT_NAME))
OBJ_DIR     := ./obj
SOURCE_DIR = ./3D_Viewer/c-function
SOURCE := $(shell find $(SOURCE_DIR) -name '*.c')
# SOURCE := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJ_DIR)/%.o, $(SOURCE))
# OBJECTS := $(addprefix $(OBJ_DIR)/,$(SOURCES:%.c=%.o))
#
# TESTS_SOURCE=$(shell find ../tests -name '*.cc')
# OBJ=$(SOURCE:.cc=.o)
# SRCS := $(shell find $(SRC_DIRS) -name 's21_*.c')
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
#
OBJECTS_GCOV := $(addprefix obj_gcov/,$(SOURCES:.c=.o))
HEADER:= calculation_module.h
OBJ_GCOV_DIR:= obj_gcov
CHECKMK_FILE:= s21_view.check
TEST_EXE		:=test_test.out
LIB_NAME		=view_core.a
TEST_FILE		=test_view

.PHONY: all clean rebuild style

all: clean $(LIB_NAME)

build: install open

open:
	@chmod a+rwx 3D_Viewer
	@open 3D_Viewer/3D_Viewer.app/Contents/MacOS/3D_Viewer
	
install:
	cd $(PROJECT_NAME) && qmake -makefile $(PROJECT_FILE) && make
	
uninstall:
	rm -rf 3D_Viewer/3D_Viewer.app
	rm -f $(PROJECT_NAME)/*.o
	rm -f $(PROJECT_NAME)/moc_*
	rm -f $(PROJECT_NAME)/Makefile .qmake.stash
	rm -rf $(PROJECT_NAME)/ui_*
	rm -rf 3D_Viewer/3D_Viewer

dist:
	tar czf dist.tar  *

dvi:
	@doxygen calc_config
	@open html/index.html

create_dir:
	@mkdir -p $(OBJ_DIR) $(OBJ_GCOV_DIR)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(CHECK_FLAGS) -o $@

test: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TEST_EXE) $(LCHECK) -lm
	@./$(TEST_EXE)

$(LIB_NAME): create_dir $(OBJECTS)
	ar rc $@ $(OBJ_DIR)/*.o

main:
	gcc -Wall -Werror -Wextra -g s21_3D_Viewer.c -o $(TEST_EXE)
	./$(TEST_EXE)

$(OBJ_GCOV_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $(subst /,_,$@) $(CHECK_FLAGS)
	mv *.o *gcno $(OBJ_GCOV_DIR)/

libgcov.a: create_dir $(OBJECTS_GCOV)
	ar rcs libgcov.a $(OBJ_GCOV_DIR)/*.o

gcov_report: $(TEST_FILE) $(HEADER) libgcov.a
	$(CC) $(CFLAGS) $^ -o $(TEST_EXE) $(LCHECK) $(LDFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
	./$(TEST_EXE)
	@mv *.gcda *.gcno $(OBJ_GCOV_DIR)
	@rm -f $(OBJ_GCOV_DIR)/*tests*
	@lcov/bin/./lcov -c -d $(OBJ_GCOV_DIR)/. -o $(OBJ_GCOV_DIR)/coverage.info
	@lcov/bin/./genhtml $(OBJ_GCOV_DIR)/coverage.info --output-directory out
	open out/index.html

style:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.c
	@clang-format -n *.h
	@rm .clang-format

rebuild: uninstall install

go: clean install open

leaks: clean main
	leaks --atExit -- ./$(TEST_EXE)

valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXE)

clean:
	@rm -rf test_test.out*
	@rm -rf *.a *.gcda *.gcno *.o *.out
	@rm -rf $(OBJ_DIR) $(OBJ_GCOV_DIR) out
	@rm -rf $(TEST_FILE)
	@rm -rf 3D_Viewer/*.o
	@rm -rf 3D_Viewer/moc_*
	@rm -rf 3D_Viewer/3D_Viewer.app
	@rm -rf 3D_Viewer/3D_Viewer
	@rm -rf 3D_Viewer/Makefile
	@rm -rf html latex
	@rm -rf dist*


