COMPILER=g++
demo1: ampersand.cc
	$(COMPILER) -std=c++11 -DDEMO1=1 ampersand.cc

demo2: ampersand.cc
	$(COMPILER) -std=c++11 -DDEMO2=1 ampersand.cc

demo3: ampersand.cc # This is the only demo that compiles.
	$(COMPILER) -std=c++11 -DDEMO3=1 ampersand.cc -o demo3 && ./demo3
