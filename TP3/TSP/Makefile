main : main.o
	g++ -o $@ $^

main.o : main.cpp
	g++ -Wall -c $<


main.pdf : main.cpp Makefile
	a2ps -o - main.cpp Makefile | ps2pdf - main.pdf


clean :
	rm -f *~

mrproper : clean
	rm -f main
