This repository contains the library programs (.h) files used by the LoRaTracker programs.

The library files need to be accessible to the Arduino IDE, there are two ways to achieve this;


1. In the Arduino libraries folder create a folder called 'LoRaTracker' and place all the files in there. 

	For instance I have my Arduino installation on a seperate drive so I would create this folder;

	Y:\Arduino\Libraries\LoRaTracker

	
2. Copy all the library files into the same folder as the programs .ino file. For example I have 
	the receiver program here;
	
	Y:\Projects\Reciever2\LoRaTracker_Receiver2_160717.ino

	So I would need to copy all the library files into the Y:\Projects\Reciever2\ folder.


Myself, I prefer to use option 1, then I can be sure that any updates to the Library files are common
to all programs. 


Stuart Robinson
July 2017