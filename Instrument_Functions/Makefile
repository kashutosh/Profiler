TR=Trace
MN=Main
AX=Aux

all : $(TR).a $(MN).o $(AX).o
	g++ $(MN).o $(TR).a $(AX).o -ldl -o out -rdynamic

$(TR).a : $(TR).o
	ar rvs $(TR).a $(TR).o 

$(AX).a : $(AX).o $(AX).h
	ar rvs $(AX).a $(AX).o 

$(TR).o : $(TR).cc $(TR).h
	g++ -c -finstrument-functions $(TR).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(MN).o : $(MN).cc
	# It is mandatory to call finstrument-functions on main
	g++ -c -finstrument-functions $(MN).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++

$(AX).o : $(AX).cc
	g++ -c -finstrument-functions $(AX).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include/c++



clean :
	rm $(TR).a $(TR).o $(MN).o out $(AX).o $(AX).a
