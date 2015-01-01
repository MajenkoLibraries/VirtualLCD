#include <VirtualLCD.h>

static const uint8_t CMD_PUSH = 129;
static const uint8_t CMD_SET_DIM = 130;
static const uint8_t CMD_SET_BG = 131;
static const uint8_t CMD_SET_FG = 132;
static const uint8_t CMD_SET_PIX = 133;
static const uint8_t CMD_CLR_PIX = 134;
static const uint8_t CMD_SET_LINE = 135;
static const uint8_t CMD_CLR_LINE = 136;

void _VirtualLCD::begin() {
    begin(Serial);
}

void _VirtualLCD::begin(Stream &s) {
    _ser = &s;
    _width = 64;
    _height = 64;
}

void _VirtualLCD::push(uint8_t v) {
    _ser->write(CMD_PUSH);
    _ser->write('a' + (v & 0x0F));
    _ser->write('a' + ((v >> 4) & 0x0F));
}

void _VirtualLCD::setPixel(uint8_t x, uint8_t y) {
    push(x);
    push(y);
    _ser->write(CMD_SET_PIX);
}

void _VirtualLCD::clearPixel(uint8_t x, uint8_t y) {
    push(x);
    push(y);
    _ser->write(CMD_CLR_PIX);
}

void _VirtualLCD::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, boolean col) {
    push(x0);
    push(y0);
    push(x1);
    push(y1);
    if (col) {
        _ser->write(CMD_SET_LINE);
    } else {
        _ser->write(CMD_CLR_LINE);
    }
}

void _VirtualLCD::setSize(uint8_t x, uint8_t y) {
    push(x);
    push(y);
    _ser->write(CMD_SET_DIM);
    _width = x;
    _height = y;
}

void _VirtualLCD::setBackground(uint8_t r, uint8_t g, uint8_t b) {
    push(r);
    push(g);
    push(b);
    _ser->write(CMD_SET_BG);
}

void _VirtualLCD::setForeground(uint8_t r, uint8_t g, uint8_t b) {
    push(r);
    push(g);
    push(b);
    _ser->write(CMD_SET_FG);
}

void _VirtualLCD::sendData(uint8_t *data) {
    boolean first = true;
    uint32_t pos = 0;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width / 8; x++) {
            sendByte(data[pos++], first);
            first = false;
        }
    }

}

void _VirtualLCD::sendByte(uint8_t v, boolean startbit) {
    uint8_t b1 = v >> 4;
    uint8_t b2 = v & 0x0F;

    if (startbit) {
        b1 += 'A';
        b2 += 'a';
    } else {
        b1 += 'a';
        b2 += 'a';
    }
    _ser->write(b1);
    _ser->write(b2);
}

_VirtualLCD VirtualLCD;
