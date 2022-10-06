.PHONY: part1 part2 clean

part1: p1tests 
	g++ part1/research.cpp part1/count_sort.cpp -o research.out
	./research.out

p1tests:
	g++ part1/count_sort.cpp part1/tests.cpp -o p1_tests.out
	./p1_tests.out

part2: p2tests
	g++ part2/tests.cpp part2/dictionary.cpp -o research.out
	./research.out

p2tests:
	g++ part2/dictionary.cpp part2/tests.cpp -o p2_tests.out
	./p2_tests.out

clean:
	rm -rf *.out