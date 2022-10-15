.PHONY: part1 part2 clean

part1:
	g++ part1/part1.cpp -o part1.out
	./part1.out

part2: tests research

research:
	g++ part2/research.cpp part2/part2.cpp -o research.out
	./research.out

tests:
	g++ part2/part2.cpp part2/tests.cpp -o part2_tests.out
	./part2_tests.out

clean:
	rm -rf *.out