.PHONY: all test clean s21_graph.a s21_graph_algorithms.a cppcheck run
CXX=g++
CXXFLAGS= -Wall -Werror -Wextra -std=c++17
GRAPH_ALGORITHMS_SRCS= s21_graph_algorithms.cc s21_queue.cc s21_stack.cc s21_matrix_methods.cc s21_random.cc ACO/s21_ant_system.cc ACO/s21_ant.cc ACO/s21_propabilites.cc 
GRAPH_ALGORITHMS_OBJS= s21_graph_algorithms.o s21_queue.o s21_stack.o s21_matrix_methods.o s21_random.o s21_ant_system.o s21_ant.o s21_propabilites.o
STATIC_LIBRARIES=s21_graph.a s21_graph_algorithms.a

all: style cppcheck run

s21_graph.a: s21_graph.cc s21_matrix_methods.cc
	@$(CXX) $(CXXFLAGS) -c s21_graph.cc s21_matrix_methods.cc
	@ar rcs s21_graph.a s21_graph.o s21_matrix_methods.o

s21_graph_algorithms.a: $(GRAPH_ALGORITHMS_SRCS)
	@$(CXX) $(CXXFLAGS) -c $(GRAPH_ALGORITHMS_SRCS)
	@ar rcs s21_graph_algorithms.a $(GRAPH_ALGORITHMS_OBJS)

test: s21_graph.a s21_graph_algorithms.a
	@$(CXX) $(CXXFLAGS) Tests/main_test.cc $(STATIC_LIBRARIES) -o test -lgtest
	@./test
	@rm -rf test.dot
	
clean:
	@rm -rf *.o *.a test a.out *.gcno *gcda report *.info app

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=useStlAlgorithm *.cc ACO/*.cc

style:
	@cp -r ../materials/linters/.clang-format ./
	@clang-format -n *.cc *.h
	@rm -rf .clang-format


run: s21_graph.a s21_graph_algorithms.a
	@$(CXX) $(CXXFLAGS) main.cc s21_console_view.cc s21_graph.a s21_graph_algorithms.a -o app
	@./app
