.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Board.o Player.o TileBag.o qwirkle.o GameMenu.o
	g++ -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -std=c++14 -g -O -c $^
