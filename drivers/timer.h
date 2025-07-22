#ifndef TIMER_H
#define TIMER_H
u32 tick = 0;

void timercallback(){
    tick++;
}

void init_timer(u32 freq){
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    /* Send the command */
    outb(0x43, 0x36); /* Command port */
    outb(0x40, low);
    outb(0x40, high);
}
#endif
