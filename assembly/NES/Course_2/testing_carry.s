.export Main

.segment "CODE"

.proc Main
  lda #$FF

  clc
  adc #$0F

  rts
.endproc
