# Rezultati i Feedback

## Bodovanje

Ukupan broj poena koji je mogao da se osvoji: **120 poena**:

| Kategorija | Maksimalno poena | Opis | Osvojeno |
|------------|------------------|------|----------|
| Funkcionalnost | 80 | Automatski testovi | 72       |
| Kvalitet koda | 40 | Pregled koda + unit testovi | 30       |

### Funkcionalni deo (80 poena)

| Tip testa | Maksimalno | Osvojeno | Napomena |
|-----------|------------|----------|----------|
| Public testovi | 20 | 20       | Testovi poslati unapred |
| Private testovi | 60 | 52       | Automatski testovi QA tima |
| **Ukupno** | **80** | **72**   | |

**Statistika:**
- Medijalna vrednost: 70
- Maksimum koji je neko osvojio: 79
- Minimum: 43

---

## Kvalitet

### Kvalitet koda (40 poena)

| Komponenta | Maksimalno | Osvojeno |
|------------|------------|----------|
| Sam kod | 35 | 30       |
| Unit testovi | 5 | 34% - 2  |
| **Ukupno** | **40** | **32**   |

**Statistika:**
- Medijalna vrednost: 30.5
- Maksimum koji je neko osvojio: 40
- Minimum: 5

---

## Saveti za unapređenje rešenja

- Kreirati interfejse koje servisi implementiraju (loose coupling, flexibility, and testability)
- Implementirati validaciju u entitetima: npr. `Student` → `@Email` za email, `Canteen` → `@Positive` za capacity
- Umesto pisanja query-a direktno, iskoristiti JPARepository  
- Izdvojiti konvertere entity → dto i obrnuto (elegantno preko biblioteka npr MapStruct)
- Dodati validaciju u DTOs
- Globalna autentikacija, pre nego sto i dodje do servisa (u produkciji na velikim projektima i na nivou baze)
- Kod je mogao biti elegantniji
- **Unit testovi!** ⚠️


- Odlicno uvezivanje entiteta
- Bravo za exception handling
---

## Zaključak

Sve u svemu, rešenje je dobro, ovo su neke sugestije za unapređenje.
Cestitamo na ucescu ma hakatonu. 

