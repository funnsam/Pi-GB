#include <gbdk/font.h>
#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdbool.h>
#include "themes.h"

#define N 50        // Change this for more / less digits

void set_theme(enum ColorTheme theme) {
    if (_cpu == CGB_TYPE) {
        switch (theme) {
            case OneDark_D: {
                set_bkg_palette_entry(0, 0, OD_BLACK);
                set_bkg_palette_entry(0, 1, OD_DGREY);
                set_bkg_palette_entry(0, 2, OD_LGREY);
                set_bkg_palette_entry(0, 3, OD_WHITE);
                break;
            }
            case OneDark_L: {
                set_bkg_palette_entry(0, 0, OD_WHITE);
                set_bkg_palette_entry(0, 1, OD_LGREY);
                set_bkg_palette_entry(0, 2, OD_DGREY);
                set_bkg_palette_entry(0, 3, OD_BLACK);
                break;
            }
            default: {
                set_bkg_palette_entry(0, 0, RGB_RED);
                break;
            }
        }
    }
}

enum ColorTheme current_theme = OneDark_D;
bool select_state = false;
void vb_han() {
    uint8_t j_state = joypad();
    switch (j_state) {
        case J_UP: {
            scroll_bkg(0, -1);
            break;
        }
        case J_DOWN: {
            scroll_bkg(0, 1);
            break;
        }
        case J_SELECT: {
            if (!select_state) {
                current_theme = (current_theme + 1) % ColorThemeItems;
                set_theme(current_theme);
            }
            break;
        }
    }
    select_state = j_state & J_SELECT;
}

void init() {
    if (_cpu == CGB_TYPE) {
        cpu_fast();
        set_theme(current_theme);
    }

    font_init();
    font_set(font_load(font_spect));

    add_VBL(vb_han);
}


#define len (10 * N/3) + 1
uint16_t buf[len];
uint16_t n = 0;
uint16_t p = 0;

void spigot_algo() {
    for (int i = 0; i < len; i++) buf[i] = 2;

    for (int i = 0; i < N; i++) {
        uint16_t q = 0;
        for (int i = len-1; i >= 0; i--) {
            uint16_t x = 10 * buf[i] + q * (i + 1);
            uint16_t y = (i << 1) + 1;
            buf[i]  = x % y;
            q       = x / y;
        }
        buf[0] = q % 10;
        q /= 10;

        if (q == 9) {
            n++;
        } else if (q == 10) {
            if (i > 1) {
                printf("%d", p + 1);
                for (int k = 0; k < n; k++) printf("0");
            }
            p, n = 0;
        } else {
            if (i > 1) printf("%d", p);
            p = q;
            for (int k = 0; k < n; k++) printf("9");
            n = 0;
        }
    }
}

int main() {
    init();
    printf("Pi=3.");
    spigot_algo();
    return 0;
}