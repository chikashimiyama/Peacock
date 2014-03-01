Peacock
=======

Peacock is an openFramework / Pure Data / AVR microcontroller based software/hardware system for musical application.



##Protocol

The following serial protocol are utilized for communication between the firmware and software.
All messages starts with start delimeter(0xFF) and end with end delimeter(0xFE).



start delimeter --- type --- data --- data ... --- data ... checksum ... end delimeter


0xFF ... start delimeter, all message starts from this delimeter, the Peacock software starts to collect bytes when it receives this delimeter
0xFE ... end delimeter, the software start to interpret received bytes when it receives this delimeter.


type
0xFB ... data message
0xFC ... command message
0xFD ... error message

Data byte range 0-0xFC (250)



