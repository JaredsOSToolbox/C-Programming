original: grep.c
	clang grep.c -o ed
original_run: original
	./ed
grep: grep_.c grepper.h
	clang grep_.c -o grep
grep_run: grep
	./grep "^yes" ./input.txt
clean: 
	rm ed grep
