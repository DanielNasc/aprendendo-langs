.export Main

.segment "CODE"

.proc Main
    ldx #$B1
    stx $00
    ldx #$A9
    stx $01

    ; Add $01 and $00
    lda $00
    clc ; clear carry
    adc $01

    ; Store result in $02
    sta $02

    ; Reset A register, add the carry and store in $03
    lda #0
    adc #0 ; A <- #0 + #0 + Carry
    sta $03
    
.endproc