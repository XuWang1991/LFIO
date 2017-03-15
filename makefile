CXXFLAGS = -w -Wall -Wextra -ansi -g -ldl
OBJECTS = parse.o lex.o function.o main.o

LFIO : $(OBJECTS)
	g++ $(OBJECTS) $(CXXFLAGS) -fkeep-inline-functions -o LFIO -lfl -lm 

clean :
	rm -f *.o

lex.cc : lex.ll
	flex --header-file=lex.hh --outfile=lex.cc lex.ll

parse.hh : parse.cc

parse.cc : parse.yy function.h algorithm.h
	bison -v --output-file=parse.cc --defines=parse.hh --warnings=all --feature=all parse.yy

%.o: %.cc %.h
	g++ $(CXXFLAGS) -c -o $@ $< -lm -ll

function.o : function.h function.cc

parse.o : parse.cc parse.hh function.h algorithm.h

lex.o :lex.hh algorithm.h function.h

main.o : main.cc function.h algorithm.h 
