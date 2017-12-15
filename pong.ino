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
int paddleheight = 10;
int playerx = 0;
int playery = 0;
int opponentx = 127 - paddlewidth;
int opponenty = 0;
int playerscore = 0;
int opponentscore = 0;

void resetgame() {
    ballx = 63;
    playerscore = 0;
    opponentscore = 0;
}

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
            // Scores
            arduboy.setCursor(20, 0);
            arduboy.print(playerscore);
            arduboy.setCursor(101, 0);
            arduboy.print(opponentscore);
            if(ballx < -10) {
                ballx = 63;
                opponentscore = opponentscore + 1;
            }
            if(ballx > 130) {
                ballx = 63;
                playerscore = playerscore + 1;
            }
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
            // Reflect ball off player paddle only
            if (ballx == playerx + paddlewidth and playery < bally + ballsize and playery + paddleheight > bally) {
                ballright = 1;
            }
            // Reflect ball off opponent paddle
            if (ballx + ballsize == opponentx and opponenty < bally + ballsize and opponenty + paddleheight > bally) {
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
            // Player 2
            arduboy.fillRect(opponentx, opponenty, paddlewidth, paddleheight, WHITE);
            // Simple AI
            if (bally < opponenty) {
                opponenty = opponenty -1;
            }
            if ( bally + ballsize > opponenty + paddleheight) {
                opponenty = opponenty + 1;
            }
            
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 2;
            }
            if (playerscore == 5 or opponentscore == 5)
            {
                gamestate = 3;
            }
            break;
        case 2: 
            // Two Player
        case 3:
            // Win Screen
            arduboy.setCursor(0, 0);
            arduboy.print("A Winner Is");
            if ( playerscore == 5) {
                arduboy.print('Player 1')
            }
            if ( opponentscore == 5) {
                arduboy.print('Player 2')
            }
            if (arduboy.pressed(A_BUTTON) and justpressed == 0)
            {
                justpressed = 1;
                gamestate = 3;
            }
            resetgame()
            break;
        case 4:
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
