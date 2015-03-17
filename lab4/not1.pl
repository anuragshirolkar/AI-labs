
%% Type Code
:- multifile type/2.
type(not0edeqz,not).



%% Signal Code
:- multifile signal/1.
signal(w0fxhuo).
signal(w1ghdrp).
signal(w2qsrrw).



%% In Code
:- multifile in/2.
in(not0edeqz,[w1ghdrp]).



%% Out Code
:- multifile out/2.
out(not0edeqz,[w2qsrrw]).



%% Connected Code
:- multifile connected/2.
connected(w1ghdrp,w0fxhuo).



%% output predicate
not1([W0],[W2]) :- valid(W0), asserta(value(w0fxhuo,W0)), value(w2qsrrw,W2).
