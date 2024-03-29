#№ Отчет по лабораторной работе №4
## по курсу "Логическое программирование"

## Обработка естественного языка

### студент: Губарева М.К.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |               |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*


## Введение

Основные подходы к обработке естественных и искусственных языков:

* Символьный
* Статистический
* Коннективистский
* Гибридный
* В данный момент нам более интересен символьный подход.

Символьный подход к обработке данных основан на использовании словарей и заранее разработанных правил. Такие системы обычно представлены в виде логических высказываний, и все преобразования осуществляются в соответствии с заданными правилами вывода. В таких системах знания представляются в виде набора фактов и правил в базе знаний.

Явные сходства можно увидеть между символьным подходом и процессом логического вывода в языке Пролог. Многие диалекты Пролога предоставляют удобные средства для работы с DCG-грамматиками, основанными на разностных списках. Это позволяет более эффективно обрабатывать структуру предложений, чем при использовании более прямолинейных методов, таких как операции слияния списков.

## Задание

Реализовать грамматический разбор фраз на ограниченном естественном языке и преобразовать данные фразы в язык исчисления предикатов первого порядка типа:
```prolog
?-test([every, man, that, lives, loves, a, woman],Res).
Res=all(X,man(X)&lives(X)=>exists(Y,woman(Y)&loves(X,Y)))
```

## Принцип решения

Предложения в любом языке, - гораздо больше, чем просто произвольные последовательности слов. Мы не можем связать вместе какой-либо набор случайных слов и составить разумное предложение. По крайней мере, результат должен соответствовать тому, что мы считаем грамматически верно составленным предложением.

Грамматика языка - это набор правил, определяющих, какие последовательности слов приемлемы в качестве предложений этого языка. Он определяет, как слова должны группироваться в фразы и какие "порядки" использования этих фраз разрешены. Учитывая грамматику языка, мы можем посмотреть на любую последовательность слов и увидеть, соответствует ли она критериям "приемлемого" предложения.

Если последовательность слов действительно верно составлена, то процесс проверки установит, что в нем есть какие-либо группы слов, установит их взаимосвязь.

Пример "контексто-свободной" грамматики:\
sentence --> noun_phrase, verb_phrase.\
noun_phrase --> determiner, noun.\
verb_phrase --> verb, noun_phrase.\
verb_phrase --> verb.\
determiner --> [the].\
noun --> [apple].\
noun --> [man].\
verb --> [eats].\
verb --> [sings].

Грамматика состоит из набора правил, продемонстрированных выше, по одному в строке. Каждое правило определяет "форму", которую может принять определенный "тип" фразы. Первое правило гласит, что предложение состоит из фразы, называемой noun_phrase, за которой следует фраза, называемая verb_phrase. Эти две фразы являются тем, что обычно называют подлежащим и сказуемым предложения:

Чтобы понять, что означает правило в контекстно-свободной грамматике, необходимо прочитать X --> Y как выражение "X может принимать форму Y", а "X, Y" - как выражение "X следует за Y". таким образом, первое правило можно прочитать как:

```
Предложение может принимать форму: существительное, за которым следует глагол.
```

Все это очень хорошо, но что такое существительное и что такое глагол? Как же нам распознать такие вещи и узнать, что
составляет для них грамматические формы? На эти вопросы отвечают второе, третье и четвертое правила грамматики. Например,

```
Фраза noun_phrase может иметь вид: определитель, за которым следует noun.
```

Грубо говоря, noun_phrase - это группа слов, которые называют вещь (или вещи). Такая фраза содержит слово, "существительное", которое определяет основной класс, к которому принадлежит вещь. Таким образом, "человек" называет человека, "программа" - программу и так далее. Кроме того, согласно этой грамматике, существительному предшествует фраза, называемая "определитель":

Аналогично, внутренняя структура для verb_phrase описывается правилами. Важно заметить, что есть два правила, определяющих, что такое verb_phrase. Всё потому, что есть две возможные формы: глагольная фраза может содержать фразу-существительное, как в "человек ест яблоко", а может и не содержать, как в "человек поет".

Наконец,
```
determiner --> [the].
```
может быть прочитано, как:
```
determiner может принимать вид: слово "the"
```
Теперь, зная всю грамматику, не составит труда описать решение поставленной задачи.

Определим инфиксные операторы:
```prolog
:- op(900, xfx, =>).
:- op(800, xfy, &).
:- op(300, xfx, :).
```

Разобъем предложение:
```prolog
sentence(P) --> noun_phrase(X, P1, P), verb_phrase(X, P1).
```

Определим noun_phrase, verb_phrase:
```prolog
noun_phrase(X, P1, P) -->
        determiner(X, P2, P1, P), noun(X, P3), rel_clause(X, P3, P2).
noun_phrase(X, P, P) --> name(X).

verb_phrase(X, P) --> trans_verb(X, Y, P1), noun_phrase(Y, P1, P).
verb_phrase(X, P) --> intrans_verb(X, P).
```

Условия "отношения":
```prolog
rel_clause(X, P1, P1&P2) --> [that], verb_phrase(X, P2).
rel_clause(_, P, P) --> [].
```

Определитель "that", "a":
```prolog
determiner(X, P1, P2, all(X):(P1=>P2)) --> [every].
determiner(X, P1, P2, exists(X):(P1&P2)) --> [a].
```

Наконец определим, чем может являться существительное, имя:
```prolog
noun(X, man(X)) --> [man].
noun(X, woman(X)) --> [woman].
name(john) --> [john].
```

Перевод в глаголы:
```prolog
trans_verb(X, Y, loves(X,Y)) --> [loves].
intrans_verb(X, lives(X)) --> [lives].
```

## Результаты

```prolog
?- phrase(sentence(P), [every,man,that,lives,loves,a,woman]).
P = all(X):(man(X)&lives(X)=>exists(Y):(woman(Y)&loves(X, Y))) .
```
```prolog
?- phrase(sentence(P), [john,loves,a,woman]).
P = exists(X):(woman(X)&loves(john, X)) .
```

## Выводы

В ходе выполнения данной лабораторной работы я ознакомилась с основными принципами обработки естественных языков и реализовала грамматический разбор предложений на английском языке, преобразовав их в язык исчисления предикатов первого типа.

Процесс обработки языка оказался довольно широким и насыщенным, с множеством нюансов и особых условий, которые иногда бывает сложно реализовать с помощью программного кода. Однако стоит отметить, что Prolog справился с этой задачей очень хорошо. Написание программ для обработки текста не потребовало много усилий и времени, особенно при базовой обработке. Это связано с тем, что в используемом мной диалекте языка Prolog есть удобные средства для работы с DCG-грамматиками. С их помощью предложение можно представить как упорядоченный набор частей, что позволяет лаконично описать структуру предложений.

Скромным минусом такого подхода к решению задачи обработки естественных языков на языке Prolog является необходимость в базе данных, однако создание такой базы оказалось совсем несложным.