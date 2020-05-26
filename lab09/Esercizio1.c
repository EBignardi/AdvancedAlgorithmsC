#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool IsAdjacent(uint8_t a, uint8_t b) {
    switch (a) {
    case 1: 
        return true;
    case 2: 
        return true;
    case 3:
        if (b == 5) {
            return false; 
        }
        else {
            return true;
        }
    case 4: 
        return true;
    case 5:
        if (b == 3) {
            return false;
        }
        else {
            return true;
        }
    }
    return true; // useless
}

bool Check(char *colors_chosed) {
    for (int i = 1; i <= 5; ++i) {
        for (int j = i+1; j <= 5; ++j) {
            if (IsAdjacent(i, j) && colors_chosed[i-1] == colors_chosed[j-1]) {
                return false;
            }
        }
    }
    return true;
}

void ColorMap(int map_pos, char *color_chosed, int *total_sol) {

    if (map_pos == 6) {
        // Check solution
        if(Check(color_chosed)) {
            for (int i = 0; i < 5; ++i) {
                printf("%d -> %c; ", i + 1, color_chosed[i]);
            }
            puts("");
            (*total_sol)++;
        }
        
        return;
    }
    
    color_chosed[map_pos - 1] = 'r';
    ColorMap(map_pos + 1, color_chosed, total_sol);
    color_chosed[map_pos - 1] = 'v';
    ColorMap(map_pos + 1, color_chosed, total_sol);
    color_chosed[map_pos - 1] = 'b';
    ColorMap(map_pos + 1, color_chosed, total_sol);
    color_chosed[map_pos - 1] = 'g';
    ColorMap(map_pos + 1, color_chosed, total_sol);
}

void main(void) {

    char colors_chosed[5];
    int total_sol = 0; 
    ColorMap(1, colors_chosed, &total_sol);

    printf("Il numero totale di soluzioni e': %d", total_sol);
}