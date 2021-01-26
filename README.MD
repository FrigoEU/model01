* nix-build release.nix
* sudo ./flash.sh
* $ fill in sudo pw
* hold prog key down BEFORE you press enter to run sudo / enter password
  * possible error: Connecting to programmer .
  * possible error: avrdude: ser_open(): can't open device "/dev/ttyACM0": Input/output error
  => Both: try again, you were too slow on the prog key
