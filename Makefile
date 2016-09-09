FILES = dynamicArray.c Mergesort.c
OUT = Mergesort
all:
	gcc $(FILES) -g -pthread -Wall -o $(OUT)
clean:

	rm $(OUT) 
