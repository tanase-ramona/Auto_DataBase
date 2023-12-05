build: proiect1
	touch fisier.out

proiect1: proiect1.o
	gcc proiect1.o -o proiect1

proiect1.o: proiect1.c Struct.h Utils.h
	gcc -c proiect1.c -o proiect1.o

run: proiect1
	./proiect1

.PHONY: clean
clean:
	rm -f proiect1.o proiect1 proiect1.out
