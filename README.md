# SubjectRush
## 🎓 SubjectRush – Supraviețuiește Semestrului 2! 🚀
### 📢 Bine ai venit... sau poate nu?
Bine ai venit rau ai nimerit in semestrul 2 din anul intai la FMI Informatica. Inteleg ca ai trecut prin primul
semestru cu bine daca citesti asta, daca nu, te astept la anul la ASC... Daca vrei (si mai poti) sa treci cu bine
si de semestrul asta, trebuie sa folosesti cateva metode simple, dar eficiente, pentru a promova toate materiile. 
Stiu ca te gandesti la ChatG.. in fine in acest joc vom folosi cateva metode conventionale de a trece examenele.
Cred ca ai folosit la un moment dat una din metodele astea: Somn, RedBull, Intrebari si Invatat. Acestea reprezinta
singura ta modalitate de a trece cu bine de inamicii nostrii de temut:
- 👾 BD (Baze de Date)
- 👾 SD (Structuri de Date)
- 👾 LMC (Logică Matematică și Computațională)
- 👾 GAL (Geometrie și Algebră Liniară)
- 👾 LFA (Limbaje Formale și Automate)
- 💀 Boss-ul Final: POO (nu mai are nevoie de descriere...) 😨
- Daca te intrebi cum sa folosesti metodele de mai sus ca sa treci anul, continua sa citesti.📚🔥

### 🎯 Instructiuni
Joculetul este de tipul Tower-Defense. Te folosesti de un set de turnuri implicite denumite dupa metodele prezentate 
mai sus. Acestea te apara de RESTANTA atacand inamicii(materiile) scazadu-le dificultatea(hp).
### 📌 Reguli de bază:
- ✔ Turnurile pot fi amplasate doar în locuri prestabilite.
- ✔ Inamicii vin în valuri. 📊
- ✔ Resursa ta principală este Timpul – cea mai prețioasă resursa a unui student 🕒
- ✔ Fiecare turn necesită o anumită cantitate de timp pentru a fi plasat. Unele turnuri necesita mai mult timp decat altele. Cand omori un inamic primesti
- ✔ Daca un inamic ajunge la capatul drumului, iti scade o viata..sau mai multe? Incearca si o sa vezi. 
- ✔ Ai dreptul la 10 RESTANTE inainte sa repeti anul. 
- Scopul tau este crearea unei strategii eficieinte de gestionare a timpului pentru a nu repeta anul.
- ### 🎯 SUCCES! 🚀




## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
