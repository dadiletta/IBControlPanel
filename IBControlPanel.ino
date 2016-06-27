/* ----------------------------
// ------TO DO & NOTES---------
// ----------------------------
Listen to IFTTT --- DONE
Signals between IBs using subscribe  --- 
JJ food ordering using webtask
CAD of possible case
Harmony remote

*/
// ----------------------------
// ------HEADER SETUP----------
// ----------------------------
// This SparkButton library has some useful functions
#include "InternetButton/InternetButton.h"
InternetButton b = InternetButton();

//toggling modes with this variable will allow me to double up the functions on certain buttons
int mode = 0;
//what's the max mode number? Will be used to loop through the modes
int MODEMAX = 5;

//the PAUSE int will slow down any of the commands so it doesn't spam a single command
int PAUSE = 800;
int circleCounter = 1;
int overwatchCounter = 1;


void setup() {
    //Does a welcoming animation go here?

    Particle.function("goPats", goPats);
    Particle.subscribe("hook-response/response", overwatch, MY_DEVICES);
    
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

// ----------------------------
// ------ANIMATIONS------------
// ----------------------------
void dance() {
    b.rainbow(5);
    delay(400);
    b.rainbow(10);
    delay(400);
}

void cirlceOff(){
    b.ledOff(circleCounter);
    delay(200);
    if(circleCounter < 12){
        circleCounter++;
    }
    else{
        circleCounter = 1;
    }
}

// ----------------------------
// ------MAIN LOOP-------------
// ----------------------------
void loop(){
    
    
    //This mode switch will let us cycle through the buttons' functionalities
    switch (mode)
    {
        //MODE 0 -- DEMO
        case 0:
            b.allLedsOn(255,51,255);  //HOT PINK
            cirlceOff();
            if(b.buttonOn(2)){
                dance();
                delay(PAUSE);
            }
            else if(b.buttonOn(3)){
                for(int i = 0; i<12; i++){
                    b.ledOn(i, i*20, i*18, i*18);
                    delay(100);
                }
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                goPats("whatever");
                delay(PAUSE);
            }
            break;
        
        //MODE 1 -- FIND PHONE
        case 1:
            b.allLedsOn(30,200,20); //GREEN
            cirlceOff();
            if(b.buttonOn(2)){
                Particle.publish("Mode1Action1");
                delay(PAUSE);
            }
            else if(b.buttonOn(3)){
                Particle.publish("Mode1Action2");
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                Particle.publish("Mode1Action3");
                delay(PAUSE);
            }
            break;
        
        //MODE 2 -- SLACK
        case 2:
            b.allLedsOn(5,20,150);  //Blueish
            cirlceOff();
            if(b.buttonOn(2)){
                Particle.publish("Mode2Action1");
                delay(PAUSE);
            }
            else if(b.buttonOn(3)){
                Particle.publish("Mode2Action2");
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                Particle.publish("Mode2Action3");
                delay(PAUSE);
            }
            break;
        
        //MODE 3 -- LIGHTS
        case 3:
            b.allLedsOn(90,90,90);  //WHITE.. makes sense for lights, right?
            cirlceOff();
            if(b.buttonOn(2)){
                Particle.publish("Mode3Action1");
                delay(PAUSE);
            }
            else if(b.buttonOn(3)){
                Particle.publish("Mode3Action2");
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                Particle.publish("Mode3Action3");
                delay(PAUSE);
            }
            break;
        //MODE 4 -- ADVANCED LIGHTS
        case 4:
            b.allLedsOn(255,255,51); //YELLOW
            cirlceOff();
            if(b.buttonOn(2)){
                Particle.publish("Mode4Action1");
                delay(PAUSE);
            }
            else if(b.buttonOn(3)){
                Particle.publish("Mode4Action2");
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                Particle.publish("Mode4Action3");
                delay(PAUSE);
            }
            break;   
        case 5:  //SUMMON OVERWATCH
            b.allLedsOn(30,155,51); 
            //animates the lights by turning off one at a time in a circle
            cirlceOff();
            if(b.buttonOn(2)){
                Particle.publish("response", "yes", PRIVATE);  //DOES THIS WORK? no...
                delay(60000);
            }
            else if(b.buttonOn(3)){
                mode = MODEMAX+1;
                Particle.publish("Mode4Action2"); //NOT CONFIGURED
                delay(PAUSE);
            }
            else if(b.buttonOn(4)){
                Particle.publish("response", "no", PRIVATE);
                delay(60000);
            }
            break;   
        default:
            if(b.buttonOn(2)){
                Particle.publish("response", "yes", PRIVATE);  //DOES THIS WORK? no...
                delay(60000);
            }
            else if(b.buttonOn(4)){
                Particle.publish("response", "no", PRIVATE); //This ends up sending a green dot?
                delay(60000);
            }
            break;
    } //closes mode switch
    
    
    // ----------------------------
    // ------MODE CYCLE------------
    // ----------------------------
    //Advance or loop the mode when top button is pressed
    if(b.buttonOn(1)){
        //reset the overwatchCounter?
        if(mode < MODEMAX){
            mode++;
            delay(PAUSE);
        }
        else{
            mode = 0;
            delay(PAUSE);
        }
    }
} //closes main loop


// ----------------------------
// ----IFTTT FUNCTIONS---------
// ----------------------------


//!!!PROBLEM... how do I handle the data? 

void overwatch(const char *event, const char *data){
    //Switch modes so the mode lights won't overwrite the replies
    mode = MODEMAX + 1;
    //loop ahead and turn off the rest of the lights so it's easier to see
    for(int x = overwatchCounter; x < 12; x++){
        b.ledOff(x);
    }
    if(strcmp (data, "yes")){
        b.ledOn(overwatchCounter, 0, 255, 0);
    }
    else{
        b.ledOn(overwatchCounter, 255, 0, 0);
    }
    overwatchCounter++;

}

int goPats(String command){
    for(int x; x<10; x++){
        b.allLedsOn(255,0,0);
        delay(500);
        b.allLedsOn(255,255,255);
        delay(500);
        b.allLedsOn(0,0,255);
        delay(500);
    }
    return 1;
    
}
