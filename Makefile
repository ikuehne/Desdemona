CC          = g++
DOCGEN      = doxygen
CFLAGS      = -Wall -ansi -pedantic -ggdb -std=c++11
OBJS        = player.o board.o
PLAYERNAME  = player

all: $(PLAYERNAME) testgame

doc:
	$(DOCGEN) DoxygenLayout.xml
	rm -r latex
	
$(PLAYERNAME): $(OBJS) wrapper.o
	$(CC) -o $@ $^

testgame: testgame.o
	$(CC) -o $@ $^

testminimax: $(OBJS) testminimax.o
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@
	
java:
	make -C java/

cleanjava:
	make -C java/ clean

clean:
	rm -f *.o $(PLAYERNAME) testgame testminimax
	rm -rf html
	
.PHONY: java testminimax
