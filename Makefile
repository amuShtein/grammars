# EDIT THESE LINES

#ENTER NAME OF FILE WITH MAIN() FUNCTION
main_file := main.cpp
#

build_folder := build
source_folder := grammars
source := symbol.cpp rule.cpp grammar_types.cpp grammars.cpp grammar_check.cpp context_free_algo.cpp automata.cpp

options = -std=c++20

obj=$(join $(addsuffix $(build_folder)/, $(dir $(source))), $(notdir $(source:.cpp=.o)))
main_obj := $(build_folder)/$(main_file:.cpp=.o)

program_name := run_gram.out

default: build

$(main_obj): $(main_file)
	g++ -c $(options) $^ -o $@

$(build_folder)/%.o: $(source_folder)/%.cpp
	g++ -c $(options) $^ -o $@

$(program_name): $(obj) $(main_obj)
	g++ $(options) $^ -o $@

build: $(program_name)

run: $(program_name)
	./$(program_name)

clear:
	rm $(obj) $(main_obj)
	rm $(program_name)

