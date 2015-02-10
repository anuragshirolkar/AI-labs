belong(a).
belong(b).
belong(c).
belong(X):-notmc(X),notsk(X),!, fail. /*contraposition to have horn clause*/
belong(X).
like(a,rain).
like(a,snow).
like(a,X) :- dislike(b,X).
like(b,X) :- like(a,X),!,fail.
like(b,X).
mc(X):-like(X,rain),!,fail.
mc(X).
notsk(X):- dislike(X,snow). /*contraposition to have horn clause*/
notmc(X):- mc(X),!,fail.
notmc(X).
dislike(P,Q):- like(P,Q),!,fail.
dislike(P,Q).
g(X):-belong(X),mc(X),notsk(X),!.
