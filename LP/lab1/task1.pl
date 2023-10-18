% 1.1
% Реализация стандартных предикатов обработки списков

% Длина списка
my_length([], 0).
my_length([_|L], N) :- my_length(L, M), N is M + 1.

% Принадлежит ли элемент списку
my_member(X,[X|_]).
my_member(X,[_|T]) :- my_member(X,T).

% Конкатeнация списков
my_append([],Y,Y).
my_append([X|T],Y,[X|Z]) :- my_append(T,Y,Z).

% Удаление элемента из списка
my_remove(X,[X|T],T).
my_remove(X, [H|T], [H|R]) :- my_remove(X, T, R).

% Перестановки элементов в списке
my_permute([], []).
my_permute(L, [X|T]) :- my_remove(X, L, Y), my_permute(Y, T).

% Подсписки списка
my_sublist(S, R) :- my_append(X, _, S), my_append(_, R, X).

% Вариант 7: усечение списка до указанной длины

% Реализация на основе стандартных предикатов
truncation1(A,L,R) :- 
    my_append(R, _, A), 
    my_length(R, L), !.

% Реализация без стандартных предикатов
truncation2(_,0,[]).
truncation2([H|T],L,[H|RT]) :- 
    L1 is L - 1, 
    truncation2(T, L1, RT), !.

% 1.2

% Вариант 13: проверка списка на арифметическую прогрессию
% Реализация на основе стандартных предикатов
arprogression1(List) :-
    my_length(List, Length),
    Length >= 3, 
    arprogression(List, Difference). 

arprogression([X,Y,Z|T],D):-!,
    X - Y =:= Y - Z,
    arprogression([Y,Z|T],D).
arprogression(_,_).

% Реализация без стандартных предикатов
arprogression2([X,Y,Z|T]):-!,
    X - Y =:= Y - Z,
    arprogression2([Y,Z|T]).
arprogression2(_).

% 1.3

% Пример совместного использования предикатов 1.1 и 1.2:
% Усечение исходного списка до указанной длины, затем проверка списка на арифметическую прогрессию:
new_arithmprogres(A,L1) :- 
    truncation1(A,L1,L2), 
    arprogression2(L2).
new_arithmprogres(_,_).