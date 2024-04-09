bool buttonState1 = LOW;
bool lastButtonState1 = HIGH;
int buttonPin1 = 33;
int ledPin1 = 29;

bool buttonState2 = LOW;
bool lastButtonState2 = HIGH;
int buttonPin2 = 34;
int ledPin2 = 30;

bool buttonState3 = LOW;
bool lastButtonState3 = HIGH;
int buttonPin3 = 35;
int ledPin3 = 31;

bool buttonState4 = LOW;
bool lastButtonState4 = HIGH;
int buttonPin4 = 36;
int ledPin4 = 32;

int potValue = 0;

int switchPin1 = 37;
int switchPin2 = 38;

long randNumber;
//initializing variables


void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  randomSeed(analogRead(0));
}
//setup buttons to produce info and LEDs to read info

void keyboardMode() {
  if (digitalRead(switchPin2) == HIGH) {
    checkButton(buttonPin1, ledPin1, 72, buttonState1, lastButtonState1);
    checkButton(buttonPin2, ledPin2, 76, buttonState2, lastButtonState2);
    checkButton(buttonPin3, ledPin3, 79, buttonState3, lastButtonState3);
    checkButton(buttonPin4, ledPin4, 84, buttonState4, lastButtonState4);
  } else {
    checkButton(buttonPin1, ledPin1, 60, buttonState1, lastButtonState1);
    checkButton(buttonPin2, ledPin2, 64, buttonState2, lastButtonState2);
    checkButton(buttonPin3, ledPin3, 67, buttonState3, lastButtonState3);
    checkButton(buttonPin4, ledPin4, 72, buttonState4, lastButtonState4);
  }
}  //keyboardMode inputs the values from the buttons into the checkButton function.
// I wrote this function in a way that the octave would change depending on switch 2

void checkButton(int buttonPin, int ledPin, int note, bool &buttonState, bool &lastButtonState) {
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);

  if (lastButtonState == LOW and buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    usbMIDI.sendNoteOn(note, 127, 1);
    delay(5);
  }
  if (lastButtonState == HIGH and buttonState == LOW) {
    digitalWrite(ledPin, LOW);
    usbMIDI.sendNoteOff(note, 0, 1);
    delay(5);
  }
}
//the checkButton function uses the buttonState variables to turn on and off the notes based only on the users input not a certain delay time
//the & or (reference) symbol before the buttonState variables allows the code to access the address of the variable instead of its current state
//if it were to access the current state there are times it would encounter the same state preventing the program from turning off the MIDI message and only sending on signals

void arpeggioMode(int note) {
  potValue = analogRead(A13);
  if (digitalRead(buttonPin1) == HIGH) {
    usbMIDI.sendNoteOn(note, 127, 1);
    digitalWrite(ledPin1, HIGH);
    delay(potValue);
    usbMIDI.sendNoteOff(note, 0, 1);
    digitalWrite(ledPin1, LOW);
    delay(potValue);
    usbMIDI.sendNoteOn(note + 4, 127, 1);
    digitalWrite(ledPin2, HIGH);
    delay(potValue);
    usbMIDI.sendNoteOff(note + 4, 0, 1);
    digitalWrite(ledPin2, LOW);
    delay(potValue);
    usbMIDI.sendNoteOn(note + 7, 127, 1);
    digitalWrite(ledPin3, HIGH);
    delay(potValue);
    usbMIDI.sendNoteOff(note + 7, 0, 1);
    digitalWrite(ledPin3, LOW);
    delay(potValue);
    usbMIDI.sendNoteOn(note + 12, 127, 1);
    digitalWrite(ledPin4, HIGH);
    delay(potValue);
    usbMIDI.sendNoteOff(note + 12, 0, 1);
    digitalWrite(ledPin4, LOW);
    delay(potValue);
  }
}
//arpeggioMode uses an establish note variable to play a 4 note sequence by added certain intervals to change the note in a major key
//the octave changing is made later

void randomNotes() {
  if (digitalRead(switchPin1) == HIGH) {
    if (digitalRead(buttonPin2) == HIGH) {
      randNumber = random(60, 84);
      usbMIDI.sendNoteOn(randNumber, 127, 1);
      digitalWrite(ledPin1, HIGH);
      delay(potValue);
      usbMIDI.sendNoteOff(randNumber, 0, 1);
      digitalWrite(ledPin1, LOW);
      delay(potValue);
      usbMIDI.sendNoteOn(randNumber + 4, 127, 1);
      digitalWrite(ledPin2, HIGH);
      delay(potValue);
      usbMIDI.sendNoteOff(randNumber + 4, 0, 1);
      digitalWrite(ledPin2, LOW);
      delay(potValue);
      usbMIDI.sendNoteOn(randNumber + 7, 127, 1);
      digitalWrite(ledPin3, HIGH);
      delay(potValue);
      usbMIDI.sendNoteOff(randNumber + 7, 0, 1);
      digitalWrite(ledPin3, LOW);
      delay(potValue);
      usbMIDI.sendNoteOn(randNumber + 12, 127, 1);
      digitalWrite(ledPin4, HIGH);
      delay(potValue);
      usbMIDI.sendNoteOff(randNumber + 12, 0, 1);
      digitalWrite(ledPin4, LOW);
      delay(potValue);
    }
  }
}
//randomNotes uses most of the code from the arpeggioMode but the note values change every cycle
//therefore it will always be the same intervals between the 4 notes but not the same key

void loop() {
  if (digitalRead(switchPin2) == HIGH) {
    if (digitalRead(switchPin1) == HIGH) {
      arpeggioMode(72);
    }
    if (digitalRead(switchPin1) == LOW) {
      keyboardMode();
    }
  } else {
    if (digitalRead(switchPin1) == HIGH) {
      arpeggioMode(60);
    }
    if (digitalRead(switchPin1) == LOW) {
      keyboardMode();
    }
    randomNotes();
  }
}
//The loop implements the switches by dictating certain modes based on switch positions.
//randomNotes is outside any if statements b/c it does not need switch 1 to operate.

//I tried to do the extra credit but I ran out of buttons.
//Even if I had an extra button I would have to edit most of my code to make the major - minor switch.
