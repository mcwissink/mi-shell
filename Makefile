.PHONY: all clean
all:
	g++ -omishell ./src/*.cxx
clean:
	rm -f mishell
 
