# Data Structures


## Exercise 1


Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.

Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100

## Exercise 2

Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:

1. dinamički dodaje novi element na početak liste
2. ispisuje listu
3. dinamički dodaje novi element na kraj liste
4. pronalazi element u listi (po prezimenu)
5. briše određeni element iz liste

U zadatku se ne smiju koristiti globalne varijable.

## Exercise 3

Prethodnom zadatku dodati funkcije:

1. dinamički dodaje novi element iza određenog elementa
2. dinamički dodaje novi element ispred određenog elementa
3. sortira listu po prezimenima osoba
4. upisuje listu u datoteku
5. čita listu iz datoteke

## Exercise 4

Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.

Napomena: Eksponenti u datoteci nisu nužno sortirani.

## Exercise 5

Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:

1. L1∪L2
2. L1∩L2

Liste osim pokazivača na sljedeću strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.

## Exercise 6

Napisati program koji pomoću vezanih listi simulira rad:

1. stoga
2. reda

Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100

## Exercise 7

Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.

## Exercise 8

Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.

Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

## Exercise 9

Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.

## Exercise 10

Napisati program koji iz datoteke čita postfiks izraz i zatim stvara stablo proračuna. Iz
gotovog stabla proračuna upisati u datoteku infiks izraz.

## Exercise 11

Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Studenti s istim
ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.
