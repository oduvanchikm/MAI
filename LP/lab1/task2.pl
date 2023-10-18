% Task 2: Relational Data
% Вариант 3 (three.pl)
% The line below imports the data
:- ['three.pl'].

% 1. Для каждого студента, найти средний балл, и сдал ли он экзамены или нет.

average(Student, Res) :-
    student(_, Student, Grade),
    length(Grade, Number),
    sum(Grade, Summa),
    Res is Summa / Number.

sum([],0).
sum([grade(_,M)|T],S) :- 
    sum(T,Y),
    S is Y + M.

pass(StudentsPassed):-
    student(_,Students,Marks),
    member(grade(_,2),Marks),
    StudentsPassed = Students.

% 2. Для каждого предмета, найти количество не сдавших студентов

failstudents(Subject,N):-
	subject(M,Subject), 
	findall(A,(student(_,_,A),gradelist(A,M)),AllMarks), 
	length(AllMarks,N). 

gradelist([grade(Subject,2)|_],Subject).
gradelist([_|T],Subject):-
	gradelist(T,Subject).


% 3. Для каждой группы, найти студента (студентов) с максимальным средним баллом

highscore(Group,N):-
    findall(Mark, (student(Group,Stud,_), average(Stud,Mark)),Marks),
    max_list(Marks,Res),
    findall(A,(student(Group,A,_), average(A,M), M == Res), N),!.

max_list([X], X).
max_list([X|Xs], Max) :-
    max_list(Xs, TempMax),
    Max is max(X, TempMax).