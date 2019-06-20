pi_gl: pi_gl.c
	gcc pi_gl.c -o pi_gl -lm
	/usr/bin/time -f "%e" ./pi_gl < entrada_pi.txt > saida_pi.txt

pi_bw: pi_bw.c
	gcc pi_bw.c -o pi_bw -lm
	/usr/bin/time -f "%e" ./pi_bw < entrada_pi.txt > saida_pi.txt

pi_mc_sequencial: pi_mc_sequencial.c random.o
	gcc pi_mc_sequencial.c random.o -o pi_mc_sequencial
	rm *.o
	/usr/bin/time -f "%e" ./pi_mc_sequencial < entrada_pi.txt > saida_pi.txt

pi_mc_paralelo: pi_mc_paralelo.c random.o
	gcc pi_mc_paralelo.c random.o -o pi_mc_paralelo -lpthread
	rm *.o
	/usr/bin/time -f "%e" ./pi_mc_paralelo < entrada_pi.txt > saida_pi.txt

bs_mc_paralelo: bs_mc_paralelo.c statistics.o random.o
	gcc bs_mc_paralelo.c statistics.o random.o -o bs_mc_paralelo -lm -lpthread
	rm *.o
	/usr/bin/time -f "%e" ./bs_mc_paralelo < entrada_blackscholes.txt > saida_blackscholes.txt

bs_mc_sequencial: bs_mc_sequencial.c statistics.o random.o
	gcc bs_mc_sequencial.c statistics.o random.o -o bs_mc_sequencial -lm
	rm *.o
	/usr/bin/time -f "%e" ./bs_mc_sequencial < entrada_blackscholes.txt > saida_blackscholes.txt

#arquivos parciais
statistics.o: statistics.c statistics.h
	gcc statistics.c -c

random.o:random.c random.h
	gcc random.c -c

enviar:
	zip so.zip *.c *.h README.md Makefile
