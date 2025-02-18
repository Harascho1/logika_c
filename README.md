# Logika

**Kod za gilliotine cutting koji koristi machine-learning i pvs algoritam.**

## Strukture

```c
typedef struct rect_t {
    int X, Y, Width, Height;
} rect_t;
```
>(X, Y) je pozicija gde moze da se smesti novo parce(pravougaonik)

>[Width, Height] cine sirinu i visinu koja moze da stane na toj poziciji.  


```c
typedef struct pice_t {
    int X, Y, Width, Height;
    bool Set;
} pice_t;
```
> __(X, Y)__ je pozicija gde je smesteno parce (ako nije onda je sa kordinatama (0, 0))

> __[Width, Height]__ cine velicinu parceta(pravougaonika)

>__Set__ je samo flag koji proverava da li je parce stavljeno za secenje.

## Fukncije

int evaluate() - vraca ukupnu povrsinu svih figura koja su smestena za secenje

int succsesors(pice_t *pice, rect_t *free_pos, int *count) - stavlja parce i pravi nove pozicije za secenje

int intersect(rect_t pos, pice_t pice) - proverava da li se figure presecaju.

int pvs(rect_t rect, int depth, int alpha, int beta) - pvs algoritam 
