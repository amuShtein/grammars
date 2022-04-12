files := symbol.o rule.o grammar_types.o grammars.o grammar_check.o main.o
program_name := run_gram

%.o: %.cpp
	g++ -c $^ -o $@

$(program_name): $(files)
	g++ $^ -o $@

run: $(program_name)
	./$(program_name)

clear:
	rm *.o
	rm $(program_name)

