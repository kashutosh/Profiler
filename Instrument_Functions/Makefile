TR=Trace
MN=Main
AX=Aux
ST=Stack
FTR=FunctionTracer

all : $(TR).a $(MN).o $(AX).o $(ST).o $(FTR).o
	g++ $(MN).o $(TR).a $(AX).o $(ST).o $(FTR).o -ldl -o $(FTR) -rdynamic

$(TR).a : $(TR).o
	ar rvs $(TR).a $(TR).o 

$(TR).o : $(TR).cc $(TR).h
	g++ -c -finstrument-functions $(TR).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(MN).o : $(MN).cc
	# It is mandatory to call finstrument-functions on main
	g++ -c -finstrument-functions $(MN).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(AX).o : $(AX).cc
	g++ -c -finstrument-functions $(AX).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(ST).o : $(ST).cc $(TR).h
	g++ -c -finstrument-functions $(ST).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(FTR).o : $(FTR).cc $(TR).h
	g++ -c $(FTR).cc -rdynamic 


clean :
	rm $(TR).a $(TR).o $(MN).o out $(AX).o $(AX).a
