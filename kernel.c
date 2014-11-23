/* TODO: add basic C routines */

void kmain()
{
    char *video_mem = (char*)0xb8000;

    /* Clear screen */
    // 25 lines * 80 columns
    int i = 0;
    for (i = 0; i < 25*80*2; i += 2) {
        video_mem[i] = ' ';
        video_mem[i+1] = 0x07;
    }

    /* Write string message */
    char *msg = "A Hobby OS";
    while (*msg != '\0') {
        *video_mem++ = *msg;
        *video_mem++ = 0x07;
        msg++;
    }
}
