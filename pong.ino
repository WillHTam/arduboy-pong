// William T
// ArduPong
#include <Arduboy.h>
Arduboy arduboy;
int gamestate = 0;
void setup() {
    arduboy.begin();
    // seed the rng
    srand(7/8);
    // set game to 60fps
    arduboy.setFramerate(60);
    arduboy.clear();
}

voice loop() {
    // Prevent Arduboy from running too fast
    // If it is too early to display the next frame, restart loop
    if (!arduboy.nextFrame()) {
        return;
    }
    arduboy.clear();
    switch ( gamestate ) {
        case 0:
            // Title Screen
            arduboy.setCursor(0, 0);
            arduboy.print("Title Screen");
            break;
        case 1:
            // Gameplay Screen
            arduboy.setCursor(0, 0);
            arduboy.print("Gameplay");
            break;
        case 2:
            // Win Screen
            arduboy.setCursor(0, 0);
            arduboy.print("Win");
        case 3:
            // Game Over
            arduboy.setCursor(0, 0);
            arduboy.print("Over");
            break;
    }
    arduboy.display();
}