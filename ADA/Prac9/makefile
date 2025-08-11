OPTS = -O3 -std=c++0x
OPTSDEBUG = -g -Wall -Wextra -std=c++0x

all: maze_bb

maze_bb: maze_bb.cc
	g++ ${OPTS} -o maze_bb maze_bb.cc

debug: maze_bb.cc
	g++ ${OPTSDEBUG} -o maze_bb maze_bb.cc

tar: maze_bb.cc makefile
	tar cvfz 51299727K.tar.gz maze_bb.cc makefile memoria.pdf

check: tar
	./validate-Pr9.sh 51299727K.tar.gz

clean: 
	rm -f maze_bb
