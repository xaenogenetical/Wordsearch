wordsearch: wordsearch.c
	gcc wordsearch.c -o search.o
clean: search.o
	rm -f search.o
