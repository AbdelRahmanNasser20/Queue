CXX = g++
CXXFLAGS = -Wall

proj5: Lqueue.o Hero.o Villain.o Game.o proj5.cpp
	$(CXX) $(CXXFLAGS) Lqueue.o Villain.o Hero.o Game.o proj5.cpp -o proj5

Game.o: Villain.o Hero.o Lqueue.o Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Lqueue.o: Lqueue.cpp
	$(CXX) $(CXXFLAGS) -c Lqueue.cpp

Villain.o: Villain.cpp Villain.h
	$(CXX) $(CXXFLAGS) -c Villain.cpp

Hero.o: Hero.cpp Hero.h
	$(CXX) $(CXXFLAGS) -c Hero.cpp

run:
	proj5

val:
	valgrind ./proj5 proj5_data.txt

clean:
	rm *~
	rm *.o

check:
	ls ~/cs202proj/proj5
