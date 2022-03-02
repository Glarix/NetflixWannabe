/*CODREANU DAN 311CB*/

Punctaj obtinut la teste pe calculator propriu:
TOTAL: 135/135
BONUS: 20/20

Tema se ruleaza cu comanda ./tema2 in_file out_file
in_file -- fisierul cu datele de intrare
out_file -- fisierul cu datele obtinute in urma rularii programului

Implementarea temei:

Functia citesteInput este folosita pentru citirea rand cu rand a fisierului de intrare si obtinerea si
gestionarea fiecarei operatii.

Operatiile de add si add_top sunt efectuate de functiile:

-- createSerial -- care formeaza serialul si stocheaza in el informatiile obtinute de functia citesteInput
aceasta functie aloca memorie pentru cozile de sezon si stocheaza in ele fiecare episod iar fiecare coada sezon
este stocata in coada serial.

-- push_in -- pentru serialele din primele 3 categorii. Functia primeste ca parametru serialul si lista in care
acesta trebuie sa fie inserat si il pozitioneaza in locul potrivit in functie de rating si nume.

-- push_inTop -- pentru serialele din categoria top10. Functia primeste ca parametru serialul si lista in care
acesta trebuie sa fie inserat si il pozitioneaza in locul potrivit in functie de pozitia sa din top.

-- restrictTop -- functia elimina ultimul element din lista daca sunt peste 10 elemente in top si seteaza pozitiile
potrivite fiecarui element in functie de pozitia lor curenta.

Operatia de show este efectuata de functiile:

-- f_WriteQ, f_WriteS si show -- aceste functii primesc ca parametru structura pe care trebuie sa o afiseze, numele
fisierului out si denumirea structurii pe care o afiseaza.

Operatia later scoate un serial din una dintre categorii si il insereaza in coada later, este efectuata de functiile:

-- findSerial -- functia primeste numele unui serial, lista in care sa-l caute si o functie de comparare a doua nume,
daca serialul este gasit in lista respectiva, il returneaza, in caz contrar returneaza NULL.

-- insertLater -- functia primeste ca parametru celula ce contine serialul spre inserare, numele fisierului out si
coada later, celula este inserata in coada later si se afiseaza pozitia pe care a fost inserata.

Operatia add_sez adauga un nou sezon unui serial si este efectuata de functiile:

-- citesteInput -- care obtine si stocheaza informatiile necesare pentru crearea unui sezon.

-- CreateSeason -- primeste ca parametri un tablou de int-uri si un int pentru numarul de episoade, functia aloca memorie
pentru o coada de episoade si stocheaza in ea informatiile primite, coada e returnata la final.

-- add_sez -- functia ia sezonul nou creat si il cauta serialul in care acesta trebuie inserat prin categorii, later si currently_
watching, odata ce il gaseste ii ataseaza noul sezon serialului respectiv.

Operatia watch vizioneaza un serial pentru un anumit numar de minute si este efectuata de functiile:

-- citesteInput -- in aceasta functie sunt colectate datele despre serial si timpul de vizionare.

-- findSerial, get_by_nameS si get_by_nameQ -- functiile cauta prin categoriile lor serialul cu numele potrivit si returneaza
celula ce contine acel serial.

-- watch_serial -- functia primeste ca parametri celula cu serialul si timpul de vizionare si verifica daca acest timp este
suficient pentru vizionarea integrala a serialului, in caz afirmativ acesta este mutat in stiva history, in caz contrar este
mutat in varful stivei currently_watching