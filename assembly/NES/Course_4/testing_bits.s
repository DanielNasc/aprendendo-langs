.export Main

.segment "CODE"

.proc Main
    ; Loading player's items
    ; Order: sword, shield, armor, helmet, boots, ring, amulet, mushroom
    lda #%10011011
    sta $00

    ; ~The player picks a shield
    lda #%01000000
    ora $00 ; do a bitwise or with the player's items, it will not change anything, besides the shield
    sta $00 ; store the result in the player's items

    ; checking if player has a sword
    lda #%10000000 ; Sword Bitmask
    and $00 ; if the accumulator is 0, then the zero flag is set
    beq has_no_sword ; branch if zero flag is set

has_sword:
    ; yey, player has a sword
    lda #$0A
    jmp finish 

has_no_sword:
    ; the player has no sword
    lda #$00

finish:
    rts

.endproc