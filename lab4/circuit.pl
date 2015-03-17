
type(a,or).
type(b,and).
type(c,and).
type(d,not).
type(e,not).

signal(w1).
signal(w2).
signal(w3).
signal(w4).
signal(w5).
signal(w6).
signal(w7).
signal(w8).
signal(w9).
signal(w10).
signal(w11).
signal(w12).
signal(w13).
signal(w14).
signal(w15).


in(0,d,w3).
in(0,e,w4).
in(0,b,w7).
in(1,b,w8).
in(0,c,w10).
in(1,c,w11).
in(0,a,w13).
in(1,a,w14).

out(d,w5).
out(e,w6).
out(b,w9).
out(c,w12).
out(a,w15).

%% connected(w1,w3).
%% connected(w2,w4).
%% connected(w1,w10).
%% connected(w2,w8).
%% connected(w5,w7).
%% connected(w6,w11).
%% connected(w9,w13).
%% connected(w12,w14).

connected(w3,w1).
connected(w4,w2).
connected(w10,w1).
connected(w8,w2).
connected(w7,w5).
connected(w11,w6).
connected(w13,w9).
connected(w14,w12).

output(X,Y,Z) :- valid(X), valid(Y), assert(value(w1,X)), assert(value(w2,Y)), value(w15,Z).
