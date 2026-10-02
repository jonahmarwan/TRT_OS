fn main() {
    println!("cargo:rerun-if-changed=init_kernel.c");
    println!("cargo:rerun-if-changed=isr_stubs.asm");

    nasm_rs::Build::new()
        .file("isr_stubs.asm")
        .flag("-f") // Force 32-bit ELF format for our i686 kernel
        .flag("elf32")
        .compile("isr_stubs")
        .unwrap();


    cc::Build::new()
        .file("init_kernel.c")
        .include(".")
        .flag("-ffreestanding")
        .compile("c_entry")
}