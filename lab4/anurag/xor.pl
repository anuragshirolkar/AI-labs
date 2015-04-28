
%% Type Code
:- multifile type/2.
type(not0chwoo,not).
type(not1kjcgb,not).
type(and0fridz,and).
type(and1slqgd,and).
type(or0dihmk,or).



%% Signal Code
:- multifile signal/1.
signal(w0gerfn).
signal(w1wdqgx).
signal(w2ngcmy).
signal(w3beesf).
signal(w4hueli).
signal(w5whwfi).
signal(w6okbkk).
signal(w7mhyts).
signal(w8gppta).
signal(w9nadpr).
signal(w10bplez).
signal(w11gnlad).
signal(w12ffeqf).
signal(w13qsdar).
signal(w14tcgew).



%% In Code
:- multifile in/2.
in(not0chwoo,[w2ngcmy]).
in(not1kjcgb,[w4hueli]).
in(and0fridz,[w6okbkk,w7mhyts]).
in(and1slqgd,[w9nadpr,w10bplez]).
in(or0dihmk,[w12ffeqf,w13qsdar]).



%% Out Code
:- multifile out/2.
out(not0chwoo,[w3beesf]).
out(not1kjcgb,[w5whwfi]).
out(and0fridz,[w8gppta]).
out(and1slqgd,[w11gnlad]).
out(or0dihmk,[w14tcgew]).



%% Connected Code
:- multifile connected/2.
connected(w2ngcmy,w0gerfn).
connected(w4hueli,w1wdqgx).
connected(w6okbkk,w3beesf).
connected(w7mhyts,w1wdqgx).
connected(w9nadpr,w5whwfi).
connected(w10bplez,w0gerfn).
connected(w12ffeqf,w8gppta).
connected(w13qsdar,w11gnlad).



%% output predicate
xor([W0,W1],[W14]) :- valid(W0), asserta(value(w0gerfn,W0)), valid(W1), asserta(value(w1wdqgx,W1)), value(w14tcgew,W14).
