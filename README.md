# Problema 1 - Battleships

Scopul primei probleme este de a simula unul sau mai multe meciuri ale 
jocului Battleships, afisandu-se cele doua table de joc ale jucatorilor cu
navele amplasate si mesaje pentru fiecare atac. Pentru tabla fiecarui jucator
am alocat memorie pentru o matrice, grid_p1, respectiv grid_p2, de dimensiuni
n si m citite la tastatura, si in plus am retinut in vectorul de tip struct
shipbow coordonatele fiecarui capat de nava pentru fiecare jucator, dar si
dimensiune si orientarea navei si daca este scufundata sau nu. Folosind
functiile definite am verificat daca navele citite sunt valide si daca da
le-am amplasat pe tablele fiecarui jucator, iar daca nu am afisat un mesaj.
Apoi am luat o variabila win ce, in urma functiei simulate_game ce imi citeste
atacurile, afiseaza mesaj pentru fiecare si modifica tablele de joc pana cand
unul dintre jucatori ramane fara nave, primeste valoarea 1 daca al doilea
jucator a ramas fara nave sau valoarea 2 daca primul jucator a ramas fara nave.
In functie de valoarea variabilei win este afisat mesajul de castig si se
incheie meciul. Apoi daca cei doi jucatori vor sa joace mai multe meciuri,
se incepe urmatorul meci. Se repeta pana cand se numarul de meciuri care mai
vor sa fie jucate ajunge la 0.

# Problema 2 - Statistici, Criptare, Decriptare

Scopul problemei 2, o extindere a problemei 1, este de a calcula anumite
statistici pentru un anumit meci sau toate meciurile jucate de catre cei doi
jucatori. Pentru a rezolva aceasta problema, in cadrul rezolvarii primei
probleme am retinut intr-un vector de tip struct game_info informatii despre
fiecare meci jucat : numarul de atacuri nimerite, numarul de atacuri ratate,
acuratetea fiecarui meci si numarul de nave pentru fiecare meci. Se citeste
cheia si daca este "-" se apeleaza functiile pentru problema 2, prelucrand
statistica necriptata. La sfarsit se afiseaza sirul de caractere stat obtinut.

# Problema 3 - Algoritmul Hill Cipher

Scopul problemei 3, o extindere a problemei 1 si 2, este de a calcula anumite
statistici care sunt primite de la tastatura criptate cu o anumita cheie.
Pentru a decriptate cheia trebuie urmati pasii de decriptare enumerate
in enuntul problemei pe care i-am realizat in mai multe functii. Dupa ce
statistica citita este decriptata cu ajutorul algoritmului ea urmeaza aceiasi
pasi ca pentru problema 2. La sfarsit, dupa ce se obtine sirul de caractere
stat, el este criptat tot urmand pasii de criptare enumerati in enuntul
problemei si ulterior afisat pe ecran.
