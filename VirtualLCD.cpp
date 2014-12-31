#include <VirtualLCD.h>

void _VirtualLCD::begin(Stream &s) {
    _ser = &s;
    _width = 64;
    _height = 64;
}

void _VirtualLCD::setSize(uint8_t x, uint8_t y) {
    _ser->write(129);
    _ser->write('a' + (x & 0x0F));
    _ser->write(130);
    _ser->write('a' + ((x >> 4) & 0x0F));
    _ser->write(131);
    _ser->write('a' + (y & 0x0F));
    _ser->write(132);
    _ser->write('a' + ((y >> 4) & 0x0F));
    _width = x;
    _height = y;
}

void _VirtualLCD::setBackground(uint8_t r, uint8_t g, uint8_t b) {
    _ser->write(133);
    _ser->write('a' + (r & 0x0F));
    _ser->write(134);
    _ser->write('a' + ((r >> 4) & 0x0F));
    _ser->write(135);
    _ser->write('a' + (g & 0x0F));
    _ser->write(136);
    _ser->write('a' + ((g >> 4) & 0x0F));
    _ser->write(137);
    _ser->write('a' + (b & 0x0F));
    _ser->write(138);
    _ser->write('a' + ((b >> 4) & 0x0F));
}

void _VirtualLCD::setForeground(uint8_t r, uint8_t g, uint8_t b) {
    _ser->write(139);
    _ser->write('a' + (r & 0x0F));
    _ser->write(140);
    _ser->write('a' + ((r >> 4) & 0x0F));
    _ser->write(141);
    _ser->write('a' + (g & 0x0F));
    _ser->write(142);
    _ser->write('a' + ((g >> 4) & 0x0F));
    _ser->write(143);
    _ser->write('a' + (b & 0x0F));
    _ser->write(144);
    _ser->write('a' + ((b >> 4) & 0x0F));
}

void _VirtualLCD::sendData(uint8_t *data) {
    boolean first = true;
    uint32_t pos = 0;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width / 8; x++) {
            uint8_t b1 = data[pos] >> 4;
            uint8_t b2 = data[pos++] & 0x0F;

            if (first) {
                b1 += 'A';
                b2 += 'a';
            } else {
                b1 += 'a';
                b2 += 'a';
            }
            first = false;
            _ser->write(b1);
            _ser->write(b2);
        }
    }

}

_VirtualLCD VirtualLCD;
