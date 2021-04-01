TR=Trace
MN=Main

all : $(TR).a $(MN).o
	g++ $(MN).o $(TR).a -ldl -o out -rdynamic

#stat : $(TR).o $(MN).o
#	g++ $(TR).o $(MN).o -ldl -o out

$(TR).a : $(TR).o
	ar rvs $(TR).a $(TR).o 

$(TR).o : $(TR).cc $(TR).h
	g++ -c -finstrument-functions $(TR).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include

$(MN).o : $(MN).cc
	g++ -c -finstrument-functions $(MN).cc -rdynamic -finstrument-functions-exclude-file-list=/usr/include

clean :
	rm $(TR).a $(TR).o $(MN).o out
