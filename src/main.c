#include <stdio.h>
#include <stdint.h>

#include "all.h"



uint8_t dum[] = {
    0x40, 0x12
};

typedef enum {
    ROOT_UNKNOWN,
    DL_DCCH,
    UL_DCCH,
    DL_CCCH,
    UL_CCCH,
    BCCH_DL_SCH,
    PCCH,
    MCCH,
    SC_MCCH,
    BCCH_BCH

} lte_rrc_root_type_t;

typedef struct {
    const asn_TYPE_descriptor_t *td;
    lte_rrc_root_type_t root_type;
    const char *name;

} lte_rrc_root_entry_t;

static const lte_rrc_root_entry_t lte_rrc_root_table[] = {
    {
        .td = &asn_DEF_DL_DCCH_Message,
        .root_type = DL_DCCH,
        .name = "DL-DCCH"
    },
    {
        .td = &asn_DEF_UL_DCCH_Message,
        .root_type = UL_DCCH,
        .name = "UL-DCCH"
    },
    {
        .td = &asn_DEF_DL_CCCH_Message,
        .root_type = DL_CCCH,
        .name = "DL-CCCH"
    },
        {
        .td = &asn_DEF_UL_CCCH_Message,
        .root_type = UL_CCCH,
        .name = "UL-CCCH"
    },
        {
        .td = &asn_DEF_BCCH_DL_SCH_Message,
        .root_type = BCCH_DL_SCH,
        .name = "BCCH_DL_SCH"
    },
};

uint8_t  LTE_RRC_ROOT_TABLE_SIZE = (sizeof(lte_rrc_root_table) / sizeof(lte_rrc_root_table[0]));

void decode(const uint8_t *buf, size_t len)
{
    lte_rrc_root_type_t det_type = ROOT_UNKNOWN;
    const lte_rrc_root_entry_t *matched = NULL;
    void *decoded = NULL;

    for (size_t i = 0; i < LTE_RRC_ROOT_TABLE_SIZE; i++) {
        const lte_rrc_root_entry_t *e = &lte_rrc_root_table[i];
        void *msg = NULL;

        asn_dec_rval_t rval = uper_decode_complete(
            NULL,
            e->td,
            &msg,
            buf,
            len
        );

        if (rval.code == RC_OK &&
            rval.consumed > 0 &&
            rval.consumed <= (long)(len * 8)) {

            printf("Matched root type: %s\n",
                   e->name ? e->name : "unknown");
            printf("Consumed bits: %ld / %zu\n",
                   rval.consumed, len * 8);

            det_type = e->root_type;
            matched  = e;
            decoded  = msg;
            asn_fprint(stdout, matched->td, decoded);
            break;
        }

        /* cleanup failed attempt */
        if (msg) {
            ASN_STRUCT_FREE(*e->td, msg);
        }
    }

    if (!matched) {
        printf("No matching RRC root type\n");
        return;
    }

    /* decoded message is now valid */
    /* TODO: process decoded */

    /* cleanup final decoded */
    ASN_STRUCT_FREE(*matched->td, decoded);
}


void decode_dl_dcch(const uint8_t *buf, size_t len){
    DL_DCCH_Message_t *msg = NULL;

    asn_dec_rval_t rval = asn_decode(
        NULL,
        ATS_UNALIGNED_BASIC_PER,
        &asn_DEF_DL_DCCH_Message,
        (void **)&msg,
        buf,
        len
    );

    if (rval.code != RC_OK){
        printf("failed to decode, code %d consumed %zu \n", rval.code, rval.consumed);
        return;
    }

    printf("decoded OK, consumed %zu bytes \n", rval.consumed);

        switch (msg->message.present) {
    case DL_DCCH_MessageType_PR_c1:
        printf("DL-DCCH: c1 message\n");
        break;
    default:
        printf("DL-DCCH: other message\n");
        break;
    }

    ASN_STRUCT_FREE(asn_DEF_DL_DCCH_Message, msg);

}



int main(void){
    decode(dum, sizeof(dum));
    return 0;
    }