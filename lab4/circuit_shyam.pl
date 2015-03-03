/* Definition of the basic boolean operators */
and(1,1,1). 
and(1,0,0). 
and(0,1,0). 
and(0,0,0). 

or(1,1,1). 
or(1,0,1). 
or(0,1,1). 
or(0,0,0). 

not(0,1). 
not(1,0). 

xor(A,B,X) :- 
	not(A,A1), 
	not(B,B1),
	and(A,B1,C1), 
	and(A1,B,C2), 
	or(C1,C2,X).


/* Defining valid gate types */
type(not).
type(or). 
type(and). 
type(xor). 

/* Defining valid signal values */
signal(0). 
signal(1). 

/* Defining meaning of output for each gate */
out(X1,G) :- andG(A,B,X,G), value(X,X1).
out(X1,G) :- orG(A,B,X,G), value(X,X1).
out(X1,G) :- notG(A,X,G), value(X,X1).

/* Defining our circuit below */
orG(t1,t2,t3,g1). 
andG(t4,t5,t6,g2). 
andG(t7,t8,t9,g3). 
notG(i1,t10,g4).
notG(i2,t11,g5).

connected(t1,t6). 
connected(t2,t9). 
connected(t4,i1). 
connected(t5,t11). 
connected(t7,t10). 
connected(t8,i2). 

value(i1,0).
value(i2,0).

/* Defining meaning of value based on connection */
value(A,S) :- connected(A,B), value(B,S), signal(S).

/* Defining meaning of value based on boolean function */
value(C,C1)   :- andG(A,B,C,G), value(A,A1), value(B,B1), and(A1,B1,C1).
value(C,C1)   :- orG(A,B,C,G), value(A,A1), value(B,B1), or(A1,B1,C1).
value(C,C1)   :- notG(A,C,G), value(A,A1), not(A1,C1).
