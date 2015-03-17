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

valid(0).
valid(1).

:- dynamic
	   value/2.

value(X,Y) :- connected(X,Z), value(Z,Y), !.
value(X,Y) :- out(G,X), type(G,OP), current_predicate(OP/3), in(0,G,In0), in(1,G,In1), value(In0,V0), value(In1,V1), call(OP,V0,V1,Y), !.
value(X,Y) :- out(G,X), type(G,OP), current_predicate(OP/2), in(0,G,In0), value(In0,V0), call(OP,V0,Y), !.

verify(OP,[A,B],C) :- call(OP,A,B,C).
verify(OP,[A],C) :- call(OP,A,C).
