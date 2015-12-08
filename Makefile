all : subsystem1 subsystem2

subsystem1 :
	cd lib; make all
subsystem2 : 
	cd apps; make
clean :
	cd lib; make clean
	cd apps; make clean
