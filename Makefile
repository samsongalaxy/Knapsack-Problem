all:	submission

submission:	main.o Knapsack.o
	g++  main.o Knapsack.o -o submission

main.o:	main.cpp
	g++ -c main.cpp -o main.o

Knapsack.o:	Knapsack.cpp
	g++ -c Knapsack.cpp -o Knapsack.o

clean:
	rm -f *.o submission
