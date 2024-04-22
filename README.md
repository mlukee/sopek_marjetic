## Šopek marjetic

Omejitev časa: 4 s

Omejitev pomnilnika: 256 MiB

Polde se je odpravil na bližnji travnik, da bi si nabral šopek marjetic. Sprehaja se po travniku in nabira marjetice, ker pa je muhast fant, se vsake toliko časa tudi odloči, da mu kakšna od že nabranih marjetic ni več všeč, in jo zavrže. Poleg marjetic ima Polde rad tudi števila, zato pri vsaki marjetici prešteje, koliko cvetnih lističev ima. Ker mu pri tem prijetnem opravilu sčasoma postane dolgčas, se je začel kratkočasiti z razmišljanjem o tem, kakšen je največji skupni delitelj števila cvetnih lističev po vseh marjeticah v njegovem šopku. Ta delitelj se seveda lahko spreminja, ko Polde v šopek dodaja nove marjetice ali jih odmetava iz njega. Pomagajte mu in napišite program, ki po vsaki spremembi (dodajanju ali brisanju posamezne marjetice) izračuna novo vrednost največjega skupnega delitelja.

# Vhodni podatki

Vprvi vrstici je celo število <i>q</i>, ki pove število operacij (dodajanj in/ali brisanj) v vhodnih podatkih. Sledi <i>q</i> vrstic, ki po vrsti opisujejo te operacije. V posamezni od teh vrstic je najprej znak "+" ali "-" (ki pove, ali je Polde marjetico dodal v šopek ali pobrisal iz njega), nato presledek in celo število <i>n</i> (ki pove število cvetnih lističev te marjetice). Polde seveda nikoli ne pobriše iz šopka take marjetice, ki je ni v njem; poleg tega se posamezni marjetici število cvetnih lističev nikoli ne spremeni. Zato je na primer nemogoče, da bi se podatki začeli z operacijama "+ 3" in "- 2".

# Omejitve vhodnih podatkov

- Število operacij: 1 ≤ <i>q</i> ≤ 10<sup>6</sup>
- Pri vsaki operaciji: 1 ≤ <i>n</i> ≤ 10<sup>7</sup>

# Izhodni podatki

Po vsaki operaciji (dodajanju ali brisanju marjetice) izpišite največji skupni delitelj števila cvetnih lističev po vseh marjeticah, ki jih ima Polde po tej operaciji v šopku. Vsako število izpišite v svojo vrstico. (Če je šopek prazen, je največji skupni delitelj po definiciji enak 1.)

| <b>Vhod</b> | <b>Izhod</b> |
| :---------- | -----------: |
| 5           |           14 |
| + 14        |            2 |
| + 18        |            2 |
| + 14        |            2 |
| - 14        |           18 |
| - 14        |              |
