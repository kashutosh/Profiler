TR=Trace
MN=Main
AX=Auxillary
ST=Stack
FTR=FunctionTracer
HST=hashtable
LSTFR=LinkedListOfFrames
BM=Benchmark_Overhead
AGS=Aggregate_Stacks

all : $(TR).a $(MN).o $(AX).o $(ST).o $(FTR).o $(HST).o $(LSTFR).o $(BM).o $(AGS).o
	g++ $(MN).o $(TR).a $(AX).o $(ST).o $(FTR).o $(HST).o $(LSTFR).o $(BM).o $(AGS).o -ldl -o $(FTR) -rdynamic -lpthread

$(TR).a : $(TR).o
	ar rvs $(TR).a $(TR).o 

$(TR).o : $(TR).cc $(TR).h
	g++ -c -g -finstrument-functions $(TR).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(MN).o : $(MN).cc
	# It is mandatory to call finstrument-functions on main
	g++ -c -g -finstrument-functions $(MN).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++ -fpermissive 

$(AX).o : $(AX).cc
	g++ -c -g -finstrument-functions $(AX).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(ST).o : $(ST).cc $(TR).h
	g++ -c -g -finstrument-functions $(ST).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(FTR).o : $(FTR).cc $(TR).h
	g++ -c -g $(FTR).cc -rdynamic 

$(HST).o : $(HST).cc $(HST).h
	g++ -c -g $(HST).cc -rdynamic 

$(LSTFR).o : $(LSTFR).cc $(LSTFR).h
	g++ -c -g $(LSTFR).cc -rdynamic 

$(BM).o : $(BM).cc 
	g++ -c -g $(BM).cc -rdynamic 


$(AGS).o : $(AGS).cc $(AGS).h
	g++ -c -g $(AGS).cc -rdynamic 

clean :
	rm *.o *.a $(FTR)
