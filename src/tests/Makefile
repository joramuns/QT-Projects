CXX=g++ -fsanitize=address
TEST_FLAGS=-lgtest_main  -lgtest -lpthread -pthread -lGL -lGLU -lglut

all: run

object:
	$(CXX) $(TEST_FLAGS) -c ../application/model/parser/indices_pars/faces_strategy.cc
	$(CXX) $(TEST_FLAGS) -c ../application/model/parser/packer/coordinate_packer.cc
	$(CXX) $(TEST_FLAGS) -c ../application/model/parser/new-parser.cc
	$(CXX) $(TEST_FLAGS) -c tests.cc

link: object
	$(CXX) $(TEST_FLAGS) -o test.out *.o

run: link
	./test.out

clean:
	rm -rf *.o *.out