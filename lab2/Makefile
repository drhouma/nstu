.PHONY: part1 part2 clean

part1: p1tests p1research

p1tests:
	# g++ part1/count_sort.cpp part1/tests.cpp -o p1_tests.out
	# ./p1_tests.out

p1research:
	g++ part1/research.cpp part1/count_sort.cpp -o research.out
	./research.out


part2: p2tests p2research

p2tests:
	# g++ part2/dictionary.cpp part2/tests.cpp -o p2_tests.out
	# ./p2_tests.out

p2research:
	@g++ part2/hash_1_research.cpp part2/dictionary.cpp part2/random_string.cpp -o hash1.out
	./hash1.out

	@g++ part2/hash_2_research.cpp part2/dictionary.cpp part2/random_string.cpp -o hash2.out
	./hash2.out
	
	@g++ part2/hash_shift_research.cpp part2/dictionary.cpp part2/random_string.cpp -o shift.out
	./shift.out

	@g++ part2/map_research.cpp part2/dictionary.cpp part2/random_string.cpp -o map_research.out
	./map_research.out

clean:
	rm -rf *.out