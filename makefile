gcc \
  -I
  asn1/asn-lte-rrc \
  src/main.c \
  asn1/asn-lte-rcc/*.c \
  -o rrc_decoder
