.PHONY: part1 part2 clean

part1: p1tests
	g++ part1/research.cpp part1/count_sort.cpp -o research.out
	./research.out

p1tests:
	g++ part1/count_sort.cpp part1/tests.cpp -o p1_tests.out
	./p1_tests.out

part2: tests research

research:
	g++ part2/research.cpp part2/part2.cpp -o research.out
	./research.out


clean:
	rm -rf *.out