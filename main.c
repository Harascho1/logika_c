#include "dec.h"

pice_t *pices_array = NULL;
pice_t *final_array = NULL;
int MAX_AREA = 0;
int pices_num = 5;
const int WIDTH = 500;
const int HEIGHT = 700;

int get_area(pice_t pice) {
    return pice.Width * pice.Height;
}

int evaluate(pice_t *pices) {
    int sum = 0;
    for (int i = 0; i < pices_num; i++) {
        if (pices[i].Set == true) {
            sum += get_area(pices_array[i]);
        }
    }
    //printf("suma = %d", sum);
    return sum;
}

int succsesors(pice_t *pice, rect_t *free_pos, int *count, int* p) {
    int tmp = *count;
    for (int i = *p; i < tmp; i++) {
        if (intersect(free_pos[i], *pice) == true) {
            printf("Parce [%d, %d] se intersektuje\n", pice->Width, pice->Height);
            continue;
        }
        if (out_of_bounds(free_pos[i], *pice) == true) {
            printf("Parce [%d, %d] je out of bounds na poziciji (%d, %d), jer je slobodna dimenzija [%d, %d]\n", 
                pice->Width, pice->Height, free_pos[i].X, free_pos[i].Y, free_pos[i].Width, free_pos[i].Height);
            continue;
        }
        pice->Set = true;
        pice->X = free_pos[i].X;
        pice->Y = free_pos[i].Y;
        int old_x = free_pos[i].X;
        int old_y = free_pos[i].Y;
        int x = pice->X;
        int y = pice->Y;
        int width = pice->Width;
        int height = pice->Height;

        free_pos[(*count)++] = (rect_t){old_x + width, old_y, free_pos[i].Width - width, free_pos[i].Height};
        free_pos[i] = (rect_t){old_x, old_y + height, free_pos[i].Width, free_pos[i].Height- height};
        printf("Stavljena je plocica na mestu (%d, %d), dimenzije [%d, %d]\n",
            x, y, width, height);
        print_pos(free_pos, *count);
        (*p) = i + 1;
        break;
    }
    if (*count == tmp) {
        return -1;
    }
    return 1;
}

int intersect(rect_t pos, pice_t pice) {

    for (int i = 0; i < pices_num; i++) {
        int x = pos.X;
        int width = pos.X + pice.Width;
        int y = pos.Y;
        int height = pos.Y + pice.Height;

        if (pices_array[i].Set == true) {
            int tmp_x = pices_array[i].X;
            int tmp_width = pices_array[i].X + pices_array[i].Height;
            int tmp_y = pices_array[i].Y;
            int tmp_height = pices_array[i].Height + tmp_y;

            // provera sirine
            if ((tmp_x > x && tmp_x < width) &&
                (y >= tmp_y && y <= tmp_height)) {
                printf("Intersektuje se u sirini sa parcetom koji se nalazi na (%d, %d) i velicine [%d, %d]\n",
                    tmp_x, tmp_y, pices_array[i].Width, pices_array[i].Height);
                return 1;
            }
            //provera visine
            if ((tmp_y > y && tmp_y < height) &&
                (x >= tmp_x && x <= tmp_width)) {
                printf("Intersektuje se u visini sa parcetom koji se nalazi na (%d, %d) i velicine [%d, %d]\n",
                    tmp_x, tmp_y, pices_array[i].Width, pices_array[i].Height);
                return 1;
            }
        }
    }
    return 0;
}

//* algo
void algo(pice_t *pices, int depth, rect_t *free_pos, int count) {

    // * pravi se free_pos
    // if (free_pos == NULL && depth == pices_num) {
    //     free_pos = (rect_t*)malloc(sizeof(rect_t)*pices_num * 2);
    //     free_pos[0] = (rect_t){0, 0, WIDTH, HEIGHT};
    // }
    // if (pices == NULL && depth == pices_num) {
    //     pices = (pice_t*)malloc(sizeof(pice_t)*pices_num);
    //     for (int i = 0; i < pices_num; i++) {
    //         pices[i] = pices_array[i];
    //         //pices[i] = (pice_t){pices_array[i].X, pices_array[i].Y, pices_array[i].Width, pices_array[i].Height, pices_array[i].Set};
    //     }
    // }

    printf("ALGO JE SA DEPTHOM = %d\n", depth);
    if (depth == 0) {
        int tmp = evaluate(pices);
        if (tmp > MAX_AREA) {
            printf("Dobio sam final_array\n");
            copy_to_array(final_array, pices);
        }
        return;
    }
    

    for (int i = 0; i < pices_num; i++) {
        int p = 0;
        if (pices[i].Set == false) {
            printf("(%d, %d) i [%d, %d]\n", pices[i].X, pices[i].Y, pices[i].Width, pices[i].Height);
            int tmp = count;
            pice_t *tmp_pices;
            rect_t *tmp_pos;
            // Set pice
            while (succsesors(&pices[i], free_pos, &count, &p) != -1) {
                print(pices);
                tmp_pices = (pice_t*)malloc(sizeof(pice_t) * pices_num);
                tmp_pos = (rect_t*)malloc(sizeof(rect_t) * pices_num * 2);
                copy_to_pos(tmp_pos, free_pos);
                copy_to_array(tmp_pices, pices);
                printf("pozvao sam algo sa depthom = %d\n", depth-1);
                algo(tmp_pices, depth - 1, tmp_pos, count);
                copy_to_array(pices, tmp_pices);
                copy_to_pos(free_pos, tmp_pos);
                count = tmp;
            }
            free(tmp_pices);
            free(tmp_pos);
        }
    }
    return;

}

int main() {
    pices_num = 5;

    pices_array = (pice_t*)malloc(sizeof(pice_t)*pices_num);
    final_array = (pice_t*)malloc(sizeof(pice_t)*pices_num);

    pice_t *pices = NULL;
    rect_t *free_pos = NULL;
    pices_array[0] = (pice_t){0, 0, 250, 100, false};
    pices_array[1] = (pice_t){0, 0, 100, 100, false};
    pices_array[2] = (pice_t){0, 0, 300, 50, false};
    pices_array[3] = (pice_t){0, 0, 250, 500, false};
    pices_array[4] = (pice_t){0, 0, 400, 20, false};


    for (int i = 0; i < pices_num; i++) {
        free_pos = (rect_t*)malloc(sizeof(rect_t)*pices_num * 2);
        free_pos[0] = (rect_t){0, 0, WIDTH, HEIGHT};

        pices = (pice_t*)malloc(sizeof(pice_t)*pices_num);
        copy_to_array(pices,pices_array);
        algo(&pices[i], pices_num, free_pos, 1);
        // free(pices);
    }

    printf("ukupna povrsina je: %d\n", evaluate(final_array));

    free(pices);
    free(free_pos);

    free(pices_array);
    free(final_array);



    //print(final_array);
    
    return 0;
}

void print(pice_t *array) {
    printf("-----------------------------------\n");
    printf("Niz postavljenih parcica:\n\n");
    for (int i = 0; i < pices_num; i++) {
        if (array[i].Set == true) {
            printf("Parce: [%d, %d], postavljeno je (%d, %d) i povrsina je %d\n", 
                array[i].Width, array[i].Height, array[i].X, array[i].Y, get_area(array[i]));
        }
    }
    printf("-----------------------------------\n");
}

bool is_square(pice_t pice) {
    return pice.Height == pice.Width;
}

void rotate(pice_t *pice) {
    int tmp = pice->Width;
    pice->Width = pice->Height;
    pice->Height = tmp;
}

void copy_to_array(pice_t *copy_to, pice_t *copy_from) {
    for (int i = 0; i < pices_num; i++) {
        copy_to[i] = copy_from[i];
    }
}

void copy_to_pos(rect_t *copyTo, rect_t *copyFrom) {
    for (int i = 0; i < pices_num; i++) {
        copyTo[i] = copyFrom[i];
    }
}

void sort() {
    for (int i = 0; i < pices_num- 1; i++) {
        for (int j = i + 1; j < pices_num; j++) {
            if (get_area(pices_array[j]) > get_area(pices_array[j])) {
                pice_t tmp = pices_array[j];
                pices_array[j] = pices_array[i];
                pices_array[i] = tmp;
            }
        }
    }
}

bool out_of_bounds(rect_t free_pos, pice_t pice) {
    return (free_pos.Width < pice.Width || free_pos.Height < pice.Height);
}

void print_pos(rect_t *free_pos, int count) {
    printf("-----------------------------------\n");
    printf("Niz slobodni mesta:\n\n");
    for (int i = 0; i < count; i++) {
        printf("Pozicija je: (%d, %d), i slobodno mesto [%d, %d]\n", 
            free_pos[i].X, free_pos[i].Y, free_pos[i].Width, free_pos[i].Height);
    }
    printf("-----------------------------------\n");
}