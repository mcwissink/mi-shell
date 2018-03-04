.PHONY: all clean
all:
	g++ -Wall -omishell ./src/*.cxx
clean:
	rm -f mishell
 
