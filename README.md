0 : frame start (0x20)

4..7 : subheader constant (observed always 00 00 00 01, or 0x1 LE)

8..11 : payload length (LE, 4 bytes) — use to compute frame_end = 12 + length

12..15 : unknown (DIAG / transport metadata; not timestamp) (0x00000098 if 22-23 and 24-25 are equal, else 0x00000010)

16..19 : unknown (DIAG / transport metadata) (observed 0x00000001 in many frames, if 22-23 and 24-25 are equal)

20..21 : likely subsystem / DIAG command short (observed 0x0010 in many frames, if 22-23 and 24-25 are equal)

22..23 : inner payload size (16-bit LE) — duplicate

24..25 : inner payload size (duplicate of 22..23) (NOT ASN1 LENGTH, just payload length after this)

26..27 : log_type (16-bit LE) — e.g. 0xb0c0 = LOG_LTE_RRC_OTA_MSG_LOG_C

28..(28+SUBHEADER_LEN), currently assumed SUBHEADER_LEN = 21

ASN1_START = 28 + SUBHEADER_LEN = 49

49..(payload length - 3) : ASN.1 Payload

payload length - 2 .. payload_length - 3 : CRC
payload length -1 : delimiter, trailing 0x7e at end