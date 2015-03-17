
%% Type Code
:- multifile type/2.
type(not0lvift,not).
type(and0jsrfo,and).



%% Signal Code
:- multifile signal/1.
signal(w0xspch).
signal(w1xulkz).
signal(w2rpzqq).
signal(w3hawpt).
signal(w4vzped).
signal(w5eoulf).
signal(w6bvlgs).



%% In Code
:- multifile in/3.
in(not0lvift,[w2rpzqq]).
in(and0jsrfo,[w4vzped,w5eoulf]).



%% Out Code
:- multifile out/2.
out(not0lvift,w3hawpt).
out(and0jsrfo,w6bvlgs).



%% Connected Code
:- multifile connected/2.
connected(w4vzped,w0xspch).
connected(w5eoulf,w1xulkz).
connected(w2rpzqq,w6bvlgs).



%% output predicate
nand([W0,W1],[W3]) :- valid(W0), asserta(value(w0xspch,W0)), valid(W1), asserta(value(w1xulkz,W1)), value(w3hawpt,W3).
