.export Main

.segment "CODE"

.proc Main
  lda #5
  sta $00
  sta $01

  lda #7
  sta $02

  lda #3
  sta $03

  lda $00

  ; test N flag
  cmp $02

  ; test Z flag
  cmp $00

  ;test C flag
  cmp $03

  rts
.endproc
