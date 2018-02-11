CFLAGS = -Wall -fpic -coverage -lm
COMPILER = gcc

testme.o: testme.c 
	$(COMPILER) -c testme.c -g $(CFLAGS)

testme: testme.o
	$(COMPILER) -o testme testme.o $(CFLAGS)

run-test: testme
	./testme &> testmeresult.out

collect-coverage:
	gcov testme.c >> testmeresult.out
	cat testme.c.gcov >> testmeresult.out

clean: 
	rm -f testme.c.gcov testme.gcda testme.gcno testme.o testme testmeresult.out