#ifndef KEYBOARD_H
#define KEYBOARD_H

void kbdcallback(){
    u8 scancode = inb(0x60);
    print_letter(scancode);
}

void print_letter(u8 scancode) {
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
            write_text("Backspace");
            break;
        case 0x0F:
            write_text("Tab");
            break;
        case 0x10:
            write_text("Q");
            break;
        case 0x11:
            write_text("W");
            break;
        case 0x12:
            write_text("E");
            break;
        case 0x13:
            write_text("R");
            break;
        case 0x14:
            write_text("T");
            break;
        case 0x15:
            write_text("Y");
            break;
        case 0x16:
            write_text("U");
            break;
        case 0x17:
            write_text("I");
            break;
        case 0x18:
            write_text("O");
            break;
        case 0x19:
            write_text("P");
            break;
	case 0x1A:
	    write_text("[");
       	    break;
	case 0x1B:
	    write_text("]");
	    break;
	case 0x1C:
	    write_text("ENTER");
	    break;
	case 0x1D:
	    write_text("LCtrl");
	    break;
	case 0x1E:
	    write_text("A");
	    break;
	case 0x1F:
	    write_text("S");
	    break;
        case 0x20:
            write_text("D");
            break;
        case 0x21:
            write_text("F");
            break;
        case 0x22:
            write_text("G");
            break;
        case 0x23:
            write_text("H");
            break;
        case 0x24:
            write_text("J");
            break;
        case 0x25:
            write_text("K");
            break;
        case 0x26:
            write_text("L");
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
	    write_text("Z");
	    break;
	case 0x2D:
	    write_text("X");
	    break;
	case 0x2E:
	    write_text("C");
	    break;
	case 0x2F:
	    write_text("V");
	    break;
        case 0x30:
            write_text("B");
            break;
        case 0x31:
            write_text("N");
            break;
        case 0x32:
            write_text("M");
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
            write_text("Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                write_text("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                write_text("key up ");
                print_letter(scancode - 0x80);
            } else write_text("Unknown key up");
            break;
    }
}
#endif
