/**********************ETUDE 3 CART 360 2020*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (4 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS OR TIMING). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  looper   ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */

#include "pitches.h" // includes the library 'pitches'
 
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_B 9  // B PIN
#define LED_PIN_G 10 // G PIN
#define LED_PIN_R 11 // R PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// duration for a single played note
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 

/*************************************************************************/

/******** MY NEW VARIABLES *****************************************************/
//my new variable for state changing
int buttonRead = 0; // current state of the button
int previousButtonState = 0;

//variables for record and play
int whatNote = 0;
int analogValueRead = 0;


/*************************************************************************/

/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
   Serial.begin(115200); //Serial Monitor for debugging
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
// here we are using a pull up resistor
//mode is on low initially
//when button pressed it's pulled up to high 
//need to make a mode counter 

int buttonRead = digitalRead(BUTTON_MODE_PIN); //pull down

if(buttonRead != previousButtonState){ // edge detection so holding button doesn't make a difference
  if (buttonRead == HIGH) {
     mode = mode + 1;
     delay(200); 
     if (mode ==5){
      mode=0; //set mode back to zero if the user has clicked 5 times 
     }
   }
}

previousButtonState = buttonRead; //make sure to set these equal to eachother for next comparison
//https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection (got some help here)

}
/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{

switch (mode) { //mode determines what happens in each case, we change the mode based on the # times the button has been pressed in chooseMode()

      case 0: //lights off
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, LOW);
      
        break;

      case 1://blue
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, HIGH);
      
        break;

      case 2://red
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, LOW);

        break;

      case 3://green
        digitalWrite(LED_PIN_R, LOW);
        digitalWrite(LED_PIN_G, HIGH);
        digitalWrite(LED_PIN_B, LOW);

        break;

      case 4://purple
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, LOW);
        digitalWrite(LED_PIN_B, HIGH);

        break;

}
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  
  else if(mode == 3) {
    play();
  }
   
   else if(mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // IMPLEMENT
  int i =0;
  //go through the notes array and set all values to zero
  for (int i = 0; i < MAX_NOTES; i = i + 1) {
  notes[i] =0;
  }
   // set counters to 0
  countNotes = 0;
  whatNote = 0;
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
   //IMPLEMENT

  // get analog value
  int analogValueRead =analogRead(NOTE_IN_PIN);
  
  if (analogValueRead ==0 ){ // Makes sure that if no buttons are pressed there will be no tone 
  noTone(BUZZER_PIN); }
  
  if(analogValueRead>0){// depinding on what button pressed the voltage to the AO pin will change 
    tone(BUZZER_PIN, whatNoteChosen(), duration);
  }
 }

/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // IMPLEMENT
 //array creation usign variabels -> notes[] (our array) -> countNotes(varible that starts at 0) -> MAX_NOTES (constant 16)
//  for (countNotes = 0; countNotes < MAX_NOTES; countNotes = countNotes + 1) {
//  Serial.println(notes[countNotes]);//Display the array values

  // get analog value
  int analogValueRead = analogRead(NOTE_IN_PIN); //reading the analog value per the pin 

  if (analogValueRead > 0) {
    // play whatNoteChosen() return value as a tone 
    tone(BUZZER_PIN, whatNoteChosen(), duration);//
  }

  // record a maximum of 16 notes in the array
   //make sure counter won't count when the button is not being pressed .. analogValueRead must be greater than 0
  if (countNotes < MAX_NOTES && analogValueRead > 0) {
    notes[countNotes] = whatNoteChosen(); //set the correct incremented index via countNotes to the return value of whatNoteChosen() function!
    //ie. what button did we press? What note is that?, (note will be an int) set that to the correct spot in the notes array ! 
    //countNotes starts at zero (ie. index 0), so you start off by setting the first button pressed to index 0
    //after setting the first index you increment the countNotes so now at 1... etc., do a delay so no strange numbers
    countNotes++;
    delay(duration);
  }
}

/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // play a note depending on the counter 'whatNote' which starts at 0, so it will play index 0 first
  //after playing index zero of whatNote, whatNote updates and counts up by 1, 
  //next check if whatNote has reached the number of notes recorded within the counter 'countNotes'
  //if whatNote has reached countNotes this means that the sequence should repeat again, so reset whatNote to 0
  
  tone(BUZZER_PIN, notes[whatNote], duration); //starts off at 0

  // increment whatNote
 whatNote++;
  Serial.println(notes[whatNote]);
  // set whatNote back to zero when it reaches the amount of notes stored in the array
  if (whatNote >= countNotes) {
    whatNote = 0;
  }
  // add delay 
  delay(duration);
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
  tone(BUZZER_PIN, notes[whatNote], duration); //starts off at 0

  // change whatNote to be a random number according to the countNotes value which would be the max index number in array
  whatNote = random(countNotes);
  
  // add delay between each note
  delay(duration);
}

/**************************************************************************/
/************************My New Function**********************************************/

int whatNoteChosen(){
//  returns a  NOTE CONSTANT :); 
  // get analog value
  int analogValueRead =analogRead(NOTE_IN_PIN);
  
 if(analogValueRead>0){// depinding on what button pressed the voltage to the AO pin will change 
//    tone(BUZZER_PIN, analogValueRead, duration);
if (analogValueRead < 300 ){ //reasoble if else statements to distinguish between buttons based on AO values
 return NOTE_C5;
} else if(analogValueRead > 300 && analogValueRead <400){
return NOTE_D5;
} else if (analogValueRead >400 && analogValueRead < 800){
  return NOTE_E5;
}
  else if (analogValueRead > 1000){
return NOTE_F5;
  }
  }
//  Serial.println(analogValueRead); //relic from determining thresholds /intervals
}
