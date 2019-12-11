sudo stty -F /dev/ttyACM0 1200 hupcl
sleep 3
avrdude -q -q -patmega32u4 -cavr109 -D -b57600 -P /dev/ttyACM0 -b57600 -Uflash:w:./result/lib/Model01-Firmware-0.0.0.hex:i
