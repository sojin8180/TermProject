.PHONY: all clean

libfuncs.a: sojin.o sangeun.o
	ar rv libfuncs.a sojin.o sangeun.o
sangeun.o: sangeunfunc.c
	gcc sangeunfunc.c -c -g -I../inc -o sangeun.o
sojin.o: sojinfunc.c
	gcc sojinfunc.c -c -g -I../inc -o sojin.o
clean:
	rm -f sojin.o sangeun.o libfuncs.a
