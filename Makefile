all: symbol.cpp rule.cpp grammars.cpp main.cpp
	g++ $^ -o $@ 