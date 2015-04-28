
%% Type Code
:- multifile type/2.
type(and0mywbk,and).
type(and1jmkhf,and).
type(and2tetky,and).
type(xor0dgzpv,xor).
type(xor1egizc,xor).
type(or0jjpel,or).
type(or1qxnth,or).



%% Signal Code
:- multifile signal/1.
signal(w0zdwsb).
signal(w1xujab).
signal(w2ifyzj).
signal(w3ucnwd).
signal(w4diilm).
signal(w5ppgaw).
signal(w6mtvjb).
signal(w7mwgms).
signal(w8trxhn).
signal(w9gcexg).
signal(w10ukzmk).
signal(w11dvskb).
signal(w12pmmmo).
signal(w13ctfyh).
signal(w14cqdsd).
signal(w15dbydy).
signal(w16bivzu).
signal(w17ylaqh).
signal(w18ruutm).
signal(w19jjnam).
signal(w20ujnzf).
signal(w21tvqkz).
signal(w22xlwso).
signal(w23gjvrx).



%% In Code
:- multifile in/2.
in(and0mywbk,[w3ucnwd,w4diilm]).
in(and1jmkhf,[w6mtvjb,w7mwgms]).
in(and2tetky,[w9gcexg,w10ukzmk]).
in(xor0dgzpv,[w12pmmmo,w13ctfyh]).
in(xor1egizc,[w15dbydy,w16bivzu]).
in(or0jjpel,[w18ruutm,w19jjnam]).
in(or1qxnth,[w21tvqkz,w22xlwso]).



%% Out Code
:- multifile out/2.
out(and0mywbk,[w5ppgaw]).
out(and1jmkhf,[w8trxhn]).
out(and2tetky,[w11dvskb]).
out(xor0dgzpv,[w14cqdsd]).
out(xor1egizc,[w17ylaqh]).
out(or0jjpel,[w20ujnzf]).
out(or1qxnth,[w23gjvrx]).



%% Connected Code
:- multifile connected/2.
connected(w12pmmmo,w0zdwsb).
connected(w13ctfyh,w1xujab).
connected(w15dbydy,w14cqdsd).
connected(w16bivzu,w2ifyzj).
connected(w3ucnwd,w0zdwsb).
connected(w4diilm,w1xujab).
connected(w6mtvjb,w0zdwsb).
connected(w7mwgms,w2ifyzj).
connected(w9gcexg,w1xujab).
connected(w10ukzmk,w2ifyzj).
connected(w18ruutm,w5ppgaw).
connected(w19jjnam,w8trxhn).
connected(w21tvqkz,w20ujnzf).
connected(w22xlwso,w11dvskb).



%% output predicate
fa([W0,W1,W2],[W17,W23]) :- valid(W0), asserta(value(w0zdwsb,W0)), valid(W1), asserta(value(w1xujab,W1)), valid(W2), asserta(value(w2ifyzj,W2)), value(w17ylaqh,W17), value(w23gjvrx,W23).
