#![no_std]
#![no_main]
#![feature(naked_functions)]
use core::panic::PanicInfo;

#[link(name = "isr_stubs", kind = "static")]
extern "C" {}


extern "C" {
    fn init_kernel();
}
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {
        // Your error handling or infinite loop for embedded systems
    }
}


use core::arch::asm;

// Writes a single byte directly to the serial port

pub unsafe fn outb(port: u16, val: u8) {
    asm!(
    "out dx, al",
    in("dx") port,  // Force it into the DX register
    in("al") val,   // Force it into the AL register
    options(nomem, nostack, preserves_flags)
    );
}

pub unsafe fn print_serial(s: &str) {
    for byte in s.bytes() {
        outb(0x3F8, byte); // 0x3F8 is the standard COM1 serial port
    }
}


#[no_mangle]
#[link_section = ".text._start"]
pub extern "C" fn _start() -> ! {
    unsafe  {
        init_kernel();
        print_serial("REACHED RUST MAIN SUCCESS!\n");
    }
    loop {}
}