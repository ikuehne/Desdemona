CC          = g++
DOCGEN      = doxygen
CFLAGS      = -Wall -ansi -pedantic -ggdb -std=c++11
OBJS        = player.o board.o gametree.o
PLAYERNAME  = desdemona
NETPLAYER   = neuralnetplayer

all: $(PLAYERNAME) $(NETPLAYER) testgame nettestgame

doc:
	$(DOCGEN) Doxyfile
	rm -r latex
	
$(PLAYERNAME): $(OBJS) wrapper.o
	$(CC) -o $@ $^

$(NETPLAYER): neuralnetplayer.o board.o netwrapper.o gametree.o
	$(CC) -o $@ $^

testgame: testgame.o
	$(CC) -o $@ $^

nettestgame: nettestgame.o
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
	rm -f *.o $(PLAYERNAME) $(NETPLAYER) nettestgame testgame testminimax
	rm -rf html
	
.PHONY: java testminimax
