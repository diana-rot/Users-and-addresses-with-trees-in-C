# Users-and-addresses-with-trees-in-C
Implementing users and adsreses with trees in c

Am uitilizat o structura de tipul Sort pentru a citi din fisierul 
tree.in si am salvat in campurile necesare in functia complete_st.
Apoi am facut un vectoralocat dinamic in care retin nodurile 
arborelui, pentru a putea face usor legaturile. Retin din campurile
structurii de tip sort in cea de tip Vnod, in functia create_tree.
Arborele meu e conceput ca fiecare parinte sa pointeze la primul
copil(kids),si copilul, daca are frati, pointeazala ei(siblings).
Afisez cu functia DFS pentru punctul 1, care e o functie recursiva,
in care m-am dus pana in frunze, apoi urc si afisez parintii insotiti
de copiii lor.

Pentru ex2 am uitilzat functia create_hierarchy unde ma duc recursiv in
copii si compar fiecare adresa a copilului cu toate ale parintelui sau.
Daca gasesc cel putin una care sa fie egala, creste nradresei, daca nu,
aloc memorie si copiez adresa copilui printre adresele parintelui.
In functia printh afisez fiecare nod recursiv, cate unul pe linie 
si adresele sale.

Pentru ex3 am facut o noua structura si anume cea de user, in care retin
toti userii cititi din fisierul user.in. Pentru acest exercitiu am avut
nevoie si de functia search_tree, in care caut un nod dupa campul data 
din el, si il returnez cand l-am gasit. In insert_addr pun adresa pe 
care o caut prin noduri si afisez nodurile prin care trec pana cand
o gasesc. In functia users_queries citesc din fisierul users si
queries, completandu-mi vectorul de useri si urmand in functie de litera
primita, instructiunea corespunzatoare. Daca e q, citesc campurile
id_nod si id_user, apoi, apeland insert_addr ma duc sa caut adresa.

Pentru eliberare folosesc:
frees-elibereaza structura sort
freen-elibereaza fiecare nod
freet-elibereaza arborele
