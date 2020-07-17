This repository contains the library programs (.h) files required by the various Tracker programs.

The library files need to be accessible to the Arduino IDE at program compile time, there are three ways
to achieve this;


1. Create a 'Tracker' folder in your \users\Arduino\libraries folder, mine is located here on a Windows 7 PC;

   C:\Users\Admin\Documents\Arduino\libraries\Tracker
   
   And copy all the Tracker library files there.  

2. For a seperate Arduino installation create a folder called 'Tracker' and place all the files in there. 

   For instance I have my own Arduino installation on a separate drive (Y:) so I would create this folder;

   Y:\Arduino\libraries\Tracker


3. Copy all the library files into the same folder as the programs .ino file. For example on my own PC I have 
   a HAB tracker program here;

   Y:\Projects\HAB2Tracker_HAB2_011017.ino

   So I would need to copy all the library files into the Y:\Projects\HAB2\ folder, or you could copy just the
   ones you need. 


Myself, I prefer to use option 2, then I can be sure that any updates to the Library files are common to all programs. 



Stuart Robinson

October 2017