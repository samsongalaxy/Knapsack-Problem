all:	program4

program4:	main.o Knapsack.o
	g++  main.o Knapsack.o -o program4

main.o:	main.cpp
	g++ -c main.cpp -o main.o

Knapsack.o:	Knapsack.cpp
	g++ -c Knapsack.cpp -o Knapsack.o

clean:
	rm -f *.o program4
