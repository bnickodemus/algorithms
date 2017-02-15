main: main.o insertionSort.o quickSort.o radixSort.o 
	g++ -o main main.o insertionSort.o quickSort.o radixSort.o 

main.o: main.cpp
	g++ -c main.cpp

insertionSort.o: insertionSort.cpp
	g++ -c insertionSort.cpp

quickSort.o: quickSort.cpp
	g++ -c quickSort.cpp

radixSort.o: radixSort.cpp
	g++ -c radixSort.cpp

clean:
	rm *.o
	rm main
