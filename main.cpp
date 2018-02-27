#include <allegro.h>
#include "Jogo.h"

int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600,0,0);
    set_window_title("Mine Sweeper 2.0");
    srand(time(NULL));
    Jogo *jogo = new Jogo();
    delete jogo;

    allegro_exit();
    return 0;
}
END_OF_MAIN()
