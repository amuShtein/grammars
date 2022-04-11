files := symbol.o rule.o grammars.o main.o

%.o: %.cpp
	g++ -c $^ -o $@

all: $(files)
	g++ $^ -o $@

run: all
	./all

clear:
	rm *.o

