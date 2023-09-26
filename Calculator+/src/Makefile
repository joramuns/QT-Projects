CXX=g++
STATLIB_BUILD=ar rcs
CFLAGS=-Wall -Werror -Wextra -std=c++17
ASAN=-fsanitize=address
GCOV=--coverage
LIB_FLAGS=-lgtest -pthread -I/usr/local/include -L/usr/local/lib/ 
VGFLAGS=--trace-children=yes --track-fds=all  --leak-check=full --show-leak-kinds=all --track-origins=yes

TARGET=Calculator.app
TEST_TARGET=test.out
LIB_TARGET=libbin/calc_model.a
DISTTARGET=SmartCalc_v2.0.tar.gz

MODEL_SRCDIR=application/model
TEST_SRCDIR=tests
OBJDIR=bin
LIBDIR=libbin
BUILDDIR=../build
BINDIR=../bin
CMAKELISTS=../src/application/CMakeLists.txt

LIB_SOURCES=$(shell find $(MODEL_SRCDIR) -type f -name '*.cc')
TEST_SOURCES=$(shell find $(TEST_SRCDIR) -type f -name '*.cc')

LIB_OBJECTS = $(patsubst $(MODEL_SRCDIR)/%,$(LIBDIR)/%,$($(notdir LIB_SOURCES):.cc=.o))
TEST_OBJECTS = $(patsubst $(TEST_SRCDIR)/%,$(OBJDIR)/%,$($(notdir TEST_SOURCES):.cc=.o))

##################################################################

all: gcov_report dvi dist

install:
	@echo "Installing application..."
	@mkdir -p $(BUILDDIR) $(BINDIR)
	@cd $(BUILDDIR) && cmake $(CMAKELISTS)
	@cd $(BUILDDIR) && make
	@rm -rf $(BINDIR)/$(TARGET)
	@mv -f $(BUILDDIR)/$(TARGET) $(BINDIR)/$(TARGET)

dist: install
	@echo "Creating a distribution file for the program..."
	@tar -czf $(BINDIR)/$(DISTTARGET) $(BINDIR)/$(TARGET)

uninstall: clean
	@rm -rf $(BINDIR)/$(TARGET)

dvi:
	doxygen dox_config
	open dvi/index.html

##################################################################

$(LIB_TARGET): $(LIB_OBJECTS)
	@echo "Building model library..."
	@$(STATLIB_BUILD) $@ $(LIB_OBJECTS)
	@ranlib $@

$(LIBDIR)/%.o : $(MODEL_SRCDIR)/%.cc | $(LIBDIR)
	@echo "Compiling source files..."
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -o $@ -c $< $(LIB)

$(LIBDIR):
	@mkdir -p $@

##################################################################

test: $(TEST_TARGET)
	@echo "Running executable:"
	@./$(TEST_TARGET) --gtest_brief=1

$(TEST_TARGET): $(LIB_TARGET) $(TEST_OBJECTS)
	@echo "Linking object files..."
	@$(CXX) $(CFLAGS) -o $@ $(TEST_OBJECTS) $(LIB_TARGET) $(LIB_FLAGS)

$(OBJDIR)/%.o : $(TEST_SRCDIR)/%.cc | $(OBJDIR)
	@echo "Compiling test source files..."
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -o $@ -c $< $(LIB_FLAGS)

$(OBJDIR):
	@mkdir -p $@

##################################################################

asan:CXX+=$(ASAN)
asan: clean test clean

gcov_report: CXX+=$(GCOV)
gcov_report: fclean test
	lcov -t "Calculator+" -o coverage.info -c -d . --rc lcov_branch_coverage=0 --no-external
	genhtml -o report coverage.info --rc lcov_branch_coverage=0
	open ./report/index.html

vg: $(TEST_TARGET)
	valgrind $(VGFLAGS) ./$<

clean:
	@rm -rf $(TEST_TARGET) $(OBJDIR)/*.o
	@rm -rf $(LIB_TARGET) $(LIBDIR)/*.o
	@rm -rf $(BINDIR)/$(TARGET)
	@rm -rf $(BINDIR)/$(DISTTARGET)
	@rm -rf *.out *.gcno *.gcov *.gcda objects report *.info
	@rm -rf dvi

fclean: clean
	@rm -rf $(OBJDIR) $(LIBDIR) $(BUILDDIR) $(BINDIR)
