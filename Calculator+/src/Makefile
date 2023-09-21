CXX=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
ASAN=-fsanitize=address
GCOV=--coverage
TARGET=Calculator.app
TESTTARGET=test.out
DISTTARGET=SmartCalc_v2.0.tar.gz
SRCDIR=application/model
OBJDIR=bin
BUILDDIR=../build
CMAKELISTS=../src/application/CMakeLists.txt
SOURCES=$(shell find $(SRCDIR) -type f -name '*.cc')
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$($(notdir SOURCES):.cc=.o))
LIB=-lgtest -pthread

VGFLAGS=--trace-children=yes --track-fds=all  --leak-check=full --show-leak-kinds=all --track-origins=yes

all: test

install:
	@echo "Installing application..."
	@mkdir -p $(BUILDDIR)
	@cd $(BUILDDIR) && cmake $(CMAKELISTS)
	@cd $(BUILDDIR) && make
	@mv -f $(BUILDDIR)/$(TARGET) .

dist: install
	@echo "Creating a distribution file for the program..."
	@tar -czf $(DISTTARGET) $(TARGET)

uninstall: clean
	@rm -rf $(TARGET)

dvi:

##################################################################

test: $(TARGET)
	@echo "Running executable:"
	@./$(TARGET) --gtest_brief=1

asan:CXX+=$(ASAN)
asan: clean test clean

gcov_report:CC+=$(GCOV)
gcov_report: clean test
	lcov -t "Calculator+" -o coverage.info -c -d . --rc lcov_branch_coverage=0 --no-external
	genhtml -o report coverage.info --rc lcov_branc_coverage=0
	open ./report/index.html

$(TARGET): $(OBJECTS)
	@echo "Linking object files..."
	@$(CXX) $(CFLAGS) -o $@ $(OBJDIR)/*.o $(OBJDIR)/*/*.o $(LIB)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc | $(OBJDIR)
	@echo "Compiling source files..."
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -o $@ -c $< $(LIB)

$(OBJDIR):
	@mkdir -p $@

vg: $(TARGET)
	valgrind $(VGFLAGS) ./$<

clean:
	@rm -rf $(TESTTARGET) $(OBJDIR)
	@rm -rf $(TARGET) $(BUILDDIR)
	@rm -rf $(DISTTARGET)
	@rm -rf *.out *.gcno *.gcov *.gcda objects report *.info

