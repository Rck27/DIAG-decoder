#include <stdio.h>
#include <stdint.h>

#include "asn1/asn-lte-rrc/DL-DCCH-Message.h"

void decode_rrc(const uint8_t *buf, size_t len) {
    DL_DCCH_Message_t *msg = NULL;

    asn_dec_rval_t rval = aper_decode(
        NULL,
        &asn_DEF_DL_DCCH_Message,
        (void **)&msg,
        buf,
        len
    );

    if (rval.code != RC_OK) {
        printf("Decode failed, consumed=%zu\n", rval.consumed);
        return;
    }

    printf("Decode success!\n");

    ASN_STRUCT_FREE(asn_DEF_DL_DCCH_Message, msg);
}

int main() {
    /* contoh payload ASN.1 (dummy) */
    uint8_t sample[] = { 0x00, 0x01, 0x02 };

    decode_rrc(sample, sizeof(sample));
    return 0;
}
