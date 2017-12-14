// William T
// ArduPong
#include <Arduboy.h>
Arduboy arduboy;
int gamestate = 0;
int justpressed = 0;
int ballx = 62;
int bally = 4;
int ballsize = 4;
int ballright = 1;
int balldown = 1;
int paddlewidth = 4;
int paddleheight = 9;
int playerx = 0;
int playery = 0;
void setup() {
    arduboy.begin();
    // seed the rng
    srand(7/8);
    // set game to 60fps
    arduboy.setFrameRate(60);
    arduboy.clear();
}

void loop() {
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
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 1;
            }
            break;
        case 1:
            // Gameplay Screen
            arduboy.setCursor(0, 0);
            arduboy.print("Gameplay");
            // The Ball
            arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);
            // Move the ball right
            if (ballright == 1) {
                ballx = ballx + 1;
            }
            // Move the ball left
            if (ballright == -1) {
                ballx = ballx - 1;
            }
            // Same for vertical
            if (balldown == 1) {
                bally = bally + 1;
            }
            if (balldown == -1) {
                bally = bally - 1;
            }
            // Reflect ball off left side of Screen
            if (ballx == 0) {
                ballright = 1;
            }
            // Reflect ball off right side of screen
            if (ballx + ballsize == 127) {
                ballright = -1;
            }
            // Same for top and bottom
            if (bally == 0) {
                balldown = 1;
            }
            if (bally + ballsize == 63) {
                balldown = -1;
            }
            // The Paddle
            arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);
            // no need for buffers since we want continuous movement
            if (arduboy.pressed(UP_BUTTON) and playery > 0) {
                playery = playery - 1;
            }
            if (arduboy.pressed(DOWN_BUTTON) and playery + paddleheight < 63) {
                playery = playery + 1;
            }
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 2;
            }
            break;
        case 2:
            // Win Screen
            arduboy.setCursor(0, 0);
            arduboy.print("Win");
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 3;
            }
            break;
        case 3:
            // Game Over
            arduboy.setCursor(0, 0);
            arduboy.print("Over");
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 0;
            }
            break;
    }
    // Check if button is not being held down
    if ( arduboy.notPressed(A_BUTTON) ) {
        justpressed = 0;
    }
    arduboy.display();
}
