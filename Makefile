OPT = -O3 -DB_64 -I. -ISAPPOROBDD
OPTCPP = -std=c++11

enum_cis: enum_cis.cpp ConnectedInducedSubgraphSpec.hpp ConvEVDD.hpp SAPPOROBDD/bddc.o SAPPOROBDD/BDD.o SAPPOROBDD/ZBDD.o
	g++ $(OPT) $(OPTCPP) enum_cis.cpp SAPPOROBDD/bddc.o SAPPOROBDD/BDD.o SAPPOROBDD/ZBDD.o -o enum_cis

e_to_v: e_to_v.cpp ConvEVDD.hpp SAPPOROBDD/bddc.o SAPPOROBDD/BDD.o SAPPOROBDD/ZBDD.o
	g++ $(OPT) $(OPTCPP) e_to_v.cpp SAPPOROBDD/bddc.o SAPPOROBDD/BDD.o SAPPOROBDD/ZBDD.o -o e_to_v

SAPPOROBDD/bddc.o: SAPPOROBDD/bddc.c SAPPOROBDD/bddc.h
	gcc $(OPT) SAPPOROBDD/bddc.c -c -o SAPPOROBDD/bddc.o

SAPPOROBDD/BDD.o: SAPPOROBDD/BDD.cc SAPPOROBDD/BDD.h
	g++ $(OPT) $(OPTCPP) SAPPOROBDD/BDD.cc -c -o SAPPOROBDD/BDD.o

SAPPOROBDD/ZBDD.o: SAPPOROBDD/ZBDD.cc SAPPOROBDD/ZBDD.h
	g++ $(OPT) $(OPTCPP) SAPPOROBDD/ZBDD.cc -c -o SAPPOROBDD/ZBDD.o

clean:
	rm -f enum_cis enum_cis.exe *.o SAPPOROBDD/*.o
