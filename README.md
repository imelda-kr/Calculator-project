# Kalkulator Projekt

Ovo je jednostavan kalkulator izrađen korištenjem Qt Creator-a i C++ programskog jezika. Aplikacija omogućava osnovne matematičke operacije (zbrajanje, oduzimanje, množenje, dijeljenje) te podržava korištenje zagrada i decimalnih brojeva.

## Sadržaj
- [Instalacija](#instalacija)
- [Pokretanje programa](#pokretanje-programa)
- [Dokumentacija](#dokumentacija)
- [Opis problema](#opis-problema)
- [Moguća poboljšanja](#moguća-poboljšanja)

## Instalacija

1. **Preuzimanje projekta**:
   - Klonirajte GitHub repozitorij na svoje računalo:
     ```bash
     git clone https://github.com/vaš-korisnički-račun/ime-repozitorija.git
     ```
   - Ili preuzmite projekt kao ZIP datoteku i raspakirajte je.

2. **Instalacija Qt Creator-a**:
   - Preuzmite i instalirajte [Qt Creator](https://www.qt.io/download) (ako ga već nemate).

3. **Otvaranje projekta**:
   - Pokrenite Qt Creator.
   - Kliknite na **File > Open File or Project** i odaberite `CMakeLists.txt` datoteku unutar preuzetog projekta.

4. **Kompilacija projekta**:
   - Nakon otvaranja projekta, kliknite na **Build > Build Project** ili pritisnite `Ctrl + B` za izgradnju projekta.

## Pokretanje programa

Nakon što je projekt uspješno kompiliran:
1. Kliknite na **Run > Start Debugging** (ili pritisnite `Ctrl + R`).
2. Aplikacija kalkulatora će se pokrenuti i možete početi koristiti osnovne funkcionalnosti kalkulatora.

## Dokumentacija

### Funkcionalnosti:
- **Osnovne matematičke operacije**: Zbrajanje, oduzimanje, množenje, dijeljenje.
- **Mogućnost za zagrade**: Mogućnost korištenja zagrada za složenije izraze.
- **Mogućnost za decimalne brojeve**: Korištenje decimalne točke (npr. 3.14).
- **Promjena znaka**: Mogućnost promjene znaka trenutnog broja na ekranu.
- **Brisanje (AC)**: Resetiranje kalkulatora na početno stanje.

### Ključne funkcije:
- `NumPressed()` – Obrada pritiska numeričkih tipki.
- `MathButtonPressed()` – Obrada pritiska matematičkih operatora.
- `EqualButtonPressed()` – Izračunavanje izraza.
- `ClearPressed()` – Resetiranje kalkulatora.
- `ChangeNumberSign()` – Promjena znaka trenutnog broja.
- `evaluateExpression()` – Evaluacija matematičkog izraza pomoću stoga.

## Opis problema

Tijekom razvoja projekta suočili smo se s nekoliko izazova:
1. **Mogućnost za zagrade i decimalne brojeve**: Implementacija mogućnosti za zagrade i decimalne brojeve zahtijevala je posebnu pažnju zbog složenosti evaluacije izraza.
2. **Greška pri negativnim brojevima**: Pojavila se greška prilikom unosa izraza koji započinju negativnim brojevima (npr. `-3+6*2`). Problem je riješen dodatnim provjerama i prilagodbama funkcije za evaluaciju izraza.
3. **Ispravno rukovanje nizom na ekranu**: Prilagodili smo unos kako bismo izbjegli prikaz suvišnih nula na početku izraza, osobito pri unosu zagrada ili decimalne točke.

## Moguća poboljšanja

1. **Dodavanje novih funkcionalnosti**:
   - Funkcionalnosti kao što su eksponencijalne funkcije, korijeni, i trigonometrijske operacije.
   
2. **Bolje rukovanje greškama**:
   - Dodavanje korisničkih obavijesti za greške poput dijeljenja s nulom.
   
3. **Poboljšanje korisničkog sučelja**:
   - Redizajn sučelja s još modernijim izgledom i dodatnim vizualnim efektima.

4. **Testiranje i optimizacija**:
   - Dodavanje jediničnih testova kako bi se osigurala stabilnost aplikacije.
