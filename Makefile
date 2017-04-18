all:
	make release
	make run
release:
	g++ main.cpp -o eseguibile.out -lSDL2 -std=c++11
run:
	./eseguibile.out
