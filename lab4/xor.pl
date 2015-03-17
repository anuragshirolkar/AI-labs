
%% Type Code
:- multifile type/2.
type(xravh,not).
type(xocyw,not).
type(bnwiw,and).
type(nitby,and).
type(untto,or).



%% Signal Code
:- multifile signal/1.
signal(zztxr).
signal(sroqr).
signal(hzsma).
signal(ceqmr).
signal(mdzoa).
signal(druuv).
signal(mvuor).
signal(hocwg).
signal(efsxk).
signal(uxxrc).
signal(wzlvi).
signal(vkqge).
signal(twdfw).
signal(qxahy).
signal(cwyxy).



%% In Code
:- multifile in/3.
in(xravh,[hzsma]).
in(xocyw,[mdzoa]).
in(bnwiw,[mvuor,hocwg]).
in(nitby,[uxxrc,wzlvi]).
in(untto,[twdfw,qxahy]).



%% Out Code
:- multifile out/2.
out(xravh,[ceqmr]).
out(xocyw,[druuv]).
out(bnwiw,[efsxk]).
out(nitby,[vkqge]).
out(untto,[cwyxy]).



%% Connected Code
:- multifile connected/2.
connected(hzsma,zztxr).
connected(mdzoa,sroqr).
connected(mvuor,ceqmr).
connected(hocwg,sroqr).
connected(uxxrc,druuv).
connected(wzlvi,zztxr).
connected(twdfw,efsxk).
connected(qxahy,vkqge).



%% output predicate
xor([W0,W1],[W14]) :- valid(W0), asserta(value(zztxr,W0)), valid(W1), asserta(value(sroqr,W1)), value(cwyxy,W14).
