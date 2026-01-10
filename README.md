0 : frame start (0x20)

4..7 : subheader constant (observed 01 00 00 00)

8..11 : payload length (LE, 4 bytes) — use to compute frame_end = 12 + length

12..15 : unknown (DIAG / transport metadata; not timestamp)

16..19 : unknown (DIAG / transport metadata)

20..21 : likely subsystem / DIAG command short (observed 0x0010 in many frames)

22..23 : inner payload size (16-bit LE) — duplicate

24..25 : inner payload size (duplicate of 22..23)

26..27 : log_type (16-bit LE) — e.g. 0xb0c0 = LOG_LTE_RRC_OTA_MSG_LOG_C

28..(28+subheader_len-1) : RRC OTA subheader (Qualcomm-specific; observed length 18 in corpus)

ASN1_START = 28 + RRC_OTA_SUBHEADER_LEN (we used 46)

frame_end : 12 + length, trailing 0x7e at end