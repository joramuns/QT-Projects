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
	@$(CC) -I/Users/mammiemi/.brew/Cellar/glm/0.9.9.8/include test_parser.cc parser.cc 
	@./a.out
