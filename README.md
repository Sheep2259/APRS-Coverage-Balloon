This code is for a rp2040 and sx1278 based superpressure picoballoon, 
designed to test the coverage and reliability of the aprs network for upcoming balloons.
It uses mixed radix and base 91 encoding to efficiently use the limited aprs payload.





things that need implementation


wspr functions in radio.cpp possibly

implement wraparound on Mixed radix encoding to avoid breaking from out of bounds data

should fill extra packet space with some pseudorandom data, like a hash

the following things must be transmitted periodically:
a range of packet lengths to test how many characters are usable,
packets in clusters, as in many consecutive transmission in a row to test large data thoughputs






aprs may have a comment message limit of 67 chars, although not certain
i think aprs has a min 5s between packets
so possibly test alternating callsign to bypass


not in this code but need aprs tracker website
