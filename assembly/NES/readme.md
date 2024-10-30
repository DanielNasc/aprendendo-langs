# 6502 Assembly Crash Course - NesHack

### Channel Link: [Link](https://www.youtube.com/channel/UCXR5PCyUI2pG_a3ydnCIS-g)
### Note: I did not write the `wrapper.s` file.

## System memory map

### $0000 - $07FF: RAM
* Main Game Data
* Temporary Storage
* Wiped Power-off / Reset
### $0800 - $0FFF: RAM mirror
### $1000 - $17FF: RAM mirror
### $1800 - $1FFF: RAM mirror
### $2000 - $401F: I/O
* Graphics
* Sound
* Controller Input
* PRG-ROM Bank Swapping
### $4020 - $FFFF: ROM

## Adressing Modes

### Immediate Addressing -> #$00
### ZeroPage Addressing -> $2F
### Absolute Addressing -> $0301
### Implicit Addressing -> `inx`

## Assembly Instructions

* `lda` - Load Accumulator
* `ldx` - Load a value into the X register
* `ldy` - Load a value into the Y register
* `inx` - Increment the X register
* `iny` - Increment the Y register
* `dex` - Decrement the X register
* `dey` - Decrement the Y register
* `sta` - Store Accumulator in Memory
* `stx` - Store the X register value in memory
* `sty` - Store the Y register value in memory
* `inc` - Increment the value in memory
* `dec` - Decrement the value in memory
* `clc` - Clear the carry flag
* `adc` - Add with carry
* `bcc` - Branch on Carry Clear
* `beq` - Branch if Equal
* `ora` - Or with accumulator