.export Main
.segment "CODE"

.proc Main
    ; Start loanding values to registers X and Y
    ldx #5
    ldy #10

    ; Increment the value of X twice
    inx
    inx

    ; Decrement the value of X once
    dex

    ; Increment the value of Y once
    iny

    ; Decrement the value of Y twice
    dey
    dey

    ; Load FF to X
    ldx #$FF

    ; Trying to increment X by one
    inx

    ; Load 00 to Y
    ldy #$00

    ; Trying to decrement Y by one
    dey

    ; Return from subroutine
    ; idk what this is
    rts

.endproc