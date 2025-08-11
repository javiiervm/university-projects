OPTS = -O3 -std=c++0x
OPTSDEBUG = -g -Wall -Wextra -std=c++0x

all: maze_bt

maze_bt: maze_bt.cc
	g++ ${OPTS} -o maze_bt maze_bt.cc

debug: maze_bt.cc
	g++ ${OPTSDEBUG} -o maze_bt maze_bt.cc

tar: maze_bt.cc makefile
	tar cvfz 51299727K.tar.gz maze_bt.cc makefile

check: tar
	./validate-Pr8.sh 51299727K.tar.gz

clean: 
	rm -f maze_bt
