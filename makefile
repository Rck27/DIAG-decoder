CC = gcc
CFLAGS = -Wall -O2 -Iasn1/asn-lte-rrc

ASN1_SRCS = $(wildcard asn1/asn-lte-rrc/*.c)
ASN1_OBJS = $(ASN1_SRCS:.c=.o)

SRC_SRCS = src/main.c
SRC_OBJS = $(SRC_SRCS:.c=.o)

all: rrc_decoder

rrc_decoder: $(ASN1_OBJS) $(SRC_OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f asn1/asn-lte-rrc/*.o src/*.o rrc_decoder
