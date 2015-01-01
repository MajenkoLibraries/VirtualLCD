Virtual LCD Protocol
====================

The protocol developed for the Virtual LCD is based around a stack
system similar in operation to Reverse Polish Notation.

At the high level, parameters for a command are first pushed onto
the stack through the serial protocol.  Following that a single
command byte is sent to initiate the command.

The Virtual LCD then pops the required parameters off the stack in
reverse order and executes the required command.

A parameter "push" consists of three bytes of data.

First is the push command, byte 0x81.  Following this are two bytes
representing the low and the high nibble of the parameter in that order.
The nibble bytes are off-set by 0x61.  This means a nibble is represented by
the ASCII characters 'a' through 'p' for '0' through '15'.

While not the most efficient use of bandwidth possible, it does make for
very simple parsing, since all command bytes will have the high bit set, and
all data bytes will have the high bit cleared.  

As an example, pushing the parameter value "234" onto the stack would consist of:

    0x81 - Push command
    0x6B - Low nibble + 0x61
    0x6F - High nibble + 0x61

A subsequent command byte will consume all parameters in the stack regardless of
how many it requires.  If there are insufficient parameters in the stack the
command will silently fail, and the stack will be purged.

The current set of command bytes, and their parameters, are:

* 0x81 - Initiate push.

Doesn't take any parameters, but the following two bytes are interpreted as a parameter to push to the stack. This is a special case command.

* 0x82 - Set LCD dimensions in pixels.

Takes two parameters - the width and the height in pixels. These should be a multiple of 8, and internally the values have the lowest three bits cleared to force a multiple of 8.

* 0x83 - Set background colour

Takes three parameters - the red, green and blue colour values.

* 0x84 - Set foreground colour

Takes three parameters - the red, green and blue colour values.

* 0x85 - Set pixel

Takes two parameters - the X and Y coordinates.

* 0x86 - Clear pixel

Takes two parameters - the X and Y coordinates.

There is also a special "whole frame transfer" sub-protocol.  In this the entire
frame data is sent as one string of nibble characters.  It is initiated
by a special nibble character with a different offset to normal marking it
out as the beginning of a frame.

This start nibble character is offset by 0x41 instead of 0x61, making the
nibble represented by the characters 'A' through 'P' instead of 'a' through 'p'.

This sub-protocol requires twice as many bytes as there are in the frame to send, so is more efficient than the stack based protocol, for higher speed updates.  The entire frame must be sent with the exact number of bytes for the screen to be
updated with the new data.
