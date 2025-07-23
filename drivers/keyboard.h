#ifndef KEYBOARD_H
#define KEYBOARD_H
bool is_extended = false;
bool caps_lock = false;
void kbdcallback(){
    if (inb(0x64) & 1) {
        u8 scancode = inb(0x60);
        if(scancode == 0xE0){
            is_extended = true;
            return;
        }
        print_letter(scancode);
    }
}

void print_letter(u8 scancode) {
    if(is_extended){
        is_extended = false;
        return;
    }
    switch (scancode) {
        case 0x0:
            write_text("ERROR");
            break;
        case 0x1:
            write_text("ESC");
            break;
        case 0x2:
            write_text("1");
            break;
        case 0x3:
            write_text("2");
            break;
        case 0x4:
            write_text("3");
            break;
        case 0x5:
            write_text("4");
            break;
        case 0x6:
            write_text("5");
            break;
        case 0x7:
            write_text("6");
            break;
        case 0x8:
            write_text("7");
            break;
        case 0x9:
            write_text("8");
            break;
        case 0x0A:
            write_text("9");
            break;
        case 0x0B:
            write_text("0");
            break;
        case 0x0C:
            write_text("-");
            break;
        case 0x0D:
            write_text("+");
            break;
        case 0x0E:
            vgabackspace();
            break;
        case 0x0F:
            write_text("Tab");
            break;
        case 0x10:
            if(caps_lock) write_text("Q");
            else{write_text("q");}
            break;
        case 0x11:
            if(caps_lock) write_text("W");
            else{write_text("w");}
            break;
        case 0x12:
            if(caps_lock) write_text("E");
            else{write_text("e");}
            break;
        case 0x13:
            if(caps_lock) write_text("R");
            else{write_text("r");}
            break;
        case 0x14:
            if(caps_lock) write_text("T");
            else{write_text("t");}
            break;
        case 0x15:
            if(caps_lock) write_text("Y");
            else{write_text("y");}
            break;
        case 0x16:
            if(caps_lock) write_text("U");
            else{write_text("u");}
            break;
        case 0x17:
            if(caps_lock) write_text("I");
            else{write_text("i");}
            break;
        case 0x18:
            if(caps_lock) write_text("O");
            else{write_text("o");}
            break;
        case 0x19:
            if(caps_lock) write_text("P");
            else{write_text("p");}
            break;
	case 0x1A:
	    write_text("[");
       	    break;
	case 0x1B:
	    write_text("]");
	    break;
	case 0x1C:
	    write_text("\n");
	    break;
	case 0x1D:
	    write_text("LCtrl");
	    break;
	case 0x1E:
        if(caps_lock) write_text("A");
        else{write_text("a");}
	    break;
	case 0x1F:
	    if(caps_lock) write_text("S");
        else{write_text("s");}
        break;
        case 0x20:
            if(caps_lock) write_text("D");
            else{write_text("d");}
            break;
        case 0x21:
            if(caps_lock) write_text("F");
            else{write_text("f");}
            break;
        case 0x22:
            if(caps_lock) write_text("G");
            else{write_text("g");}
            break;
        case 0x23:
            if(caps_lock) write_text("H");
            else{write_text("h");}
            break;
        case 0x24:
            if(caps_lock) write_text("J");
            else{write_text("j");}
            break;
        case 0x25:
            if(caps_lock) write_text("K");
            else{write_text("k");}
            break;
        case 0x26:
            if(caps_lock) write_text("L");
            else{write_text("l");}
            break;
        case 0x27:
            write_text(";");
            break;
        case 0x28:
            write_text("'");
            break;
        case 0x29:
            write_text("`");
            break;
	case 0x2A:
	    write_text("LShift");
	    break;
	case 0x2B:
	    write_text("\\");
	    break;
	case 0x2C:
	    if(caps_lock) write_text("Z");
        else{write_text("z");}
        break;
	case 0x2D:
	    if(caps_lock) write_text("X");
        else{write_text("x");}
        break;
	case 0x2E:
	    if(caps_lock) write_text("C");
        else{write_text("c");}
        break;
	case 0x2F:
	    if(caps_lock) write_text("V");
        else{write_text("v");}
        break;
        case 0x30:
            if(caps_lock) write_text("B");
            else{write_text("b");}
            break;
        case 0x31:
            if(caps_lock) write_text("N");
            else{write_text("n");}
            break;
        case 0x32:
            if(caps_lock) write_text("M");
            else{write_text("m");}
            break;
        case 0x33:
            write_text(",");
            break;
        case 0x34:
            write_text(".");
            break;
        case 0x35:
            write_text("/");
            break;
        case 0x36:
            write_text("Rshift");
            break;
        case 0x37:
            write_text("Keypad *");
            break;
        case 0x38:
            write_text("LAlt");
            break;
        case 0x39:
            write_text(" ");
            break;
        case 0x3A:
            caps_lock = !caps_lock;
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
               //write_text("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                // write_text("key up ");
                // print_letter(scancode - 0x80);
            } //else write_text("Unknown key up");
            break;
    }
}
#endif
