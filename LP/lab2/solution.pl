% Place your solution here

day('Chuck','Monday',0).
day('Chuck','Tuesday',0).
day('Chuck','Wednesday',0).
day('Chuck','Thursday',1).
day('Chuck','Friday',1).
day('Chuck','Saturday',1).
day('Chuck','Sunday',1).

day('Gek','Monday',1).
day('Gek','Tuesday',0).
day('Gek','Wednesday',1).
day('Gek','Thursday',0).
day('Gek','Friday',1).
day('Gek','Saturday',0).
day('Gek','Sunday',1).

previousday('Monday','Tuesday').
previousday('Tuesday','Wednesday').
previousday('Wednesday','Thursday').
previousday('Thursday','Friday').
previousday('Friday','Saturday').
previousday('Saturday','Sunday').
previousday('Sunday','Monday').

diff('Gek', 'Chuck').
diff('Chuck', 'Gek').
 
phrase1(0, First) :- 
    First \= 'Chuck'.
phrase1(1, First) :- 
    First = 'Chuck'.
 
phrase2(0, Today) :- 
    not(previousday('Sunday',Today)).
phrase2(1, Today) :- 
    previousday('Sunday',Today).
 
phrase3(0, Today) :- 
    not(previousday(Today,'Friday')).
phrase3(1, Today) :- 
    previousday(Today,'Friday').

phrase4(SecondTrue, Second) :-
    day(Second, 'Wednesday', SecondTrue).
 
 
solve :-
    day(First, Today, FirstTrue),
    diff(First, Second),
    day(Second, Today, SecondTrue),
    
    phrase1(FirstTrue, First),
    phrase2(FirstTrue, Today),
    phrase3(SecondTrue, Today),
    phrase4(SecondTrue, Second),
    
    write('First: '), write(First),nl,
    write('Second: '), write(Second), nl,
    write('Today: '), write(Today), nl,
    !.
