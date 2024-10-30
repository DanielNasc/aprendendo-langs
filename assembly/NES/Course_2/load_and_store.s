.export Main

.segment "CODE"

.proc Main
    ; Initialize some ZeroPage memory
    ldx #10 ; # -> Constant / Immediate Value
    stx $00 ; Store X -> Stores X Register Data into memory
    stx $01

    inc $00 ; Increment the value at memory location 00 directly
    dec $01 ; Decrement the value at memory location 01 directly

    ; Loading $00 and $01 into $0300 and $0301
    ldx $00 ; Load X Register with the value at memory location 00
    stx $0300
    ldx $01
    stx $0301

.endproc