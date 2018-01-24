//I2CDisplay Commands, these go in the go in the first byte of a transfer on the I2C
//Some commnads are a single byte only


const byte ClearDisplay = 0x43;         //'C'
const byte CursorPosition = 0x50;       //'P'
const byte StartText = 0x54;            //'T'
const byte FontScale = 0x53;            //'S'
const byte UpdateDisplay = 0x55;        //'U'

const byte FontStyle = 0x46;            //'F'
const byte DisplayRotation = 0x52;      //'R'
const byte InitialiseDisplay = 0x49;    //'I'
const byte TextColour = 0x31;           //'1'
const byte BackgroundColour = 0x32;     //'2'
const byte ClearRow = 0x33;             //'3'
const byte Contrast = 0x34;             //'4' 
const byte Test = 0x35;                 //'5' 

//I2CDisplay Colours
const byte Black = 0x00;
const byte Blue = 0x01;
const byte Red = 0x02;
const byte Magenta = 0x03;
const byte Green = 0x04;
const byte Cyan = 0x05;
const byte Yellow = 0x06;
const byte White = 0x07;


/*
//I2C Commands
//Some commnads are a single byte only
ClearDisplay = 0x43;         //'C'
CursorPosition = 0x50;       //'P'
StartText = 0x54;            //'T'
FontScale = 0x53;            //'S'
UpdateDisplay = 0x55;        //'U'

FontStyle = 0x46;            //'F'
DisplayRotation = 0x52;      //'R'
InitialiseDisplay = 0x49;    //'I'
TextColour = 0x31;           //'1'
BackgroundColour = 0x32;     //'2'
ClearRow = 0x33;             //'3'
Contrast = 0x34;             //'4' 
Test = 0x35;                 //'5' 

//I2C Display Colours
Black = 0x00;
Blue = 0x01;
Red = 0x02;
Magenta = 0x03;
Green = 0x04;
Cyan = 0x05;
Yellow = 0x06;
White = 0x07;
*/