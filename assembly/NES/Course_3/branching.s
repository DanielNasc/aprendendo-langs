.export Main

.segment "CODE"

.proc Main
    ; Health
    lda #30
    sta $00

    ; Damage
    lda #29
    sta $01

    ; Results of routine
    lda #0 ; 0 => not dead  
    sta $02

    ; Check if Damage is >= Health
    lda $01
    cmp $00
    bcc not_dead ; 

    ; Set $02 to 1 if dead
    lda #1
    sta $02

not_dead:
    rts
.endproc