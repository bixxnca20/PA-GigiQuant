Acest program prelucreaza date economice pentru 4 scenarii diferite:
- scenariul 1: se da un fisier cu nr de observatii si preturile, ca dupa sa se calculeze randamentul, volatilitatea si Sharpe Ratio-ul portofoliului respectiv
- scenariul 2: se da un fisier care contine 3 orase, fiecare avand preturile unei burse pe mai multe zile. Programul afiseaza orasul, diferenta absoluta de preturi si ziua in care se poate profita de arbitraj
- scenariul 3: se da un fisier care contine numele a 10 companii si pretul stocurilor acestora pe mai multe zile. Programul afiseaza perechile de companii care impreuna formeaza un portofoliu stabil.
- scenariul 4: Se da un fisier care contine numarul de observatii, numarul de zile, dimensiunea intervalelor, pretul de inceput, si cel target, precum si pretul pentru fiecare observatie. Programul calculeaza lantul markov al acestor date si afiseaza pentru fiecare zi probabilitatea ca pretul curent sa fie chiar cel target.

Date despre proiect:
In fisierul src se gaseste fisierul sursa "test.c", precum si headerele si fisierele pentru fiecare functie si pentru selectarea scenariului. Programul intra pe scenarii in functie de numele fisierului de intrare. Pentru a rula programul, se va face un astfel de apel:
/a.exe dataN.in dataN.out, unde N poate lua valori intre 1 si 20. 
Daca N are valoarea: 
- intre 1 si 5: se va executa codul pentru scenariul 1
- intre 6 si 10: se va executa codul pentru scenariul 2
- intre 11 si 15: se va execura codul pentru scenariul 3
- intre 16 si 20: se va executa codul pentru scenariul 4

  Pentru a modifica ce se intampla intr-un anumit scenariu, se pot accesa fisierele taskN.h si functiiN.c, unde N este numaraul scenariului care se doreste sa fie schimbat.

  Imbunatatiri:
  Fiecare tablou unidimensional sau bidimensional prezent atat in codul sursa, cat si in fisierele pentru fiecare scenariu, care este alocat static, poate sa fie alocat dinamic.
