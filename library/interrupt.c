#include <kernel/types.h>

uint8_t inb(uint16_t port)
{
    uint8_t data;
    asm volatile("inb %1, %0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}

void outb(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "Nd"(port));
}

void wait_for_io(uint32_t timer_count)
{
    while (1)
    {
        asm volatile("nop");
        timer_count--;
        if (timer_count <= 0)
            break;
    }
}
// A simple beep implementation. See https://wiki.osdev.org/PC_Speaker#Sample_Code/ /**Code by HyperCreeck**/
void sleep(uint32_t timer_count)
{
    wait_for_io(timer_count * 0x02FFFFFF);
}
static void play_sound(uint32_t nFrequence)
{
    uint32_t Div;
    uint8_t tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(Div));
    outb(0x42, (uint8_t)(Div >> 8));

    //And play the sound using the PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
        outb(0x61, tmp | 3);
    }
}

//make it shutup
static void nosound()
{
    uint8_t tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}

//Make a beep
void beep()
{
    play_sound(600);
    sleep(1);
    nosound();
    //set_PIT_2(old_frequency);
}
// End sound code
