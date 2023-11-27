CC=g++ -Wall -Werror -Wextra -std=c++17
ASAN=-fsanitize=address
GCOV=--coverage
TARGET=test.out
SRCDIR=tests
OBJDIR=bin
SOURCES=$(shell find $(SRCDIR) -type f -name '*.cc')
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$($(notdir SOURCES):.cc=.o))
LIB=-lgtest -pthread

VGFLAGS=--trace-children=yes --track-fds=all  --leak-check=full --show-leak-kinds=all --track-origins=yes

parser:
	@$(CC) $(ASAN) *.cc 
	@./a.out
