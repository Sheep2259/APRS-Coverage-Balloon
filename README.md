things that need implementation

gps functionality
gps coords to aprs format
should move gps to seperate file

voltage measuring and reporting   DONE

wspr functions in radio.cpp possibly

implement Mixed radix encoding (like traquito big number encoding)


the following things must be transmitted periodically:
a range of packet lengths to test how many characters are usable,
packets with a wide veriaty of characters so we can tell which ones can be used for encoding,
packets in clusters, as in many consecutive transmission in a row to test large data thoughputs

Mixed radix encoding should probably be used, same as big number encoding on traquito wspr
will need to make some sort of byte array as one variable cant store the size of the encoded integer

aprs may have a comment message limit of 67 chars, although not certain
i think aprs has a min 5s between packets
so possibly test alternating callsign to bypass


not in this code but need aprs tracker website