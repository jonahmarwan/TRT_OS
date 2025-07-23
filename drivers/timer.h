#ifndef TIMER_H
#define TIMER_H
u32 tick = 0;

void timercallback(){
    tick++;
}

void sleep(u32 ms){
    ms = (ms * 50) / 1000;
    u32 start_ticks = tick;

    while(tick - start_ticks < ms) asm volatile("hlt");
}

void sleep_ticks(u32 ticks){
    u32 start_ticks = ticks;
    while(tick - start_ticks < ticks) asm volatile("hlt");
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
