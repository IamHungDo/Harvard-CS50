//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

#define PADDLEW 100
#define PADDLEH 20
// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    // velocity of ball
    double vX = drand48();
    double vY = 2;
    // keep playing until game over
    while (lives > 0 && points<50)
    {
        move(ball,vX,vY);
        GEvent mouse = getNextEvent(MOUSE_EVENT);
        if(mouse!=NULL) {
            if(getEventType(mouse) == MOUSE_MOVED) {
            int y = 500;
            double x = getX(mouse) - getWidth(paddle)/2;
            setLocation(paddle,x,y);
            }
        }
      if(getX(ball) + getWidth(ball) >= getWidth(window)) {
        vX = -vX;
    } else if(getY(ball) <=0) {
        vY = -vY;
    } else if(getX(ball)<=0) {
        vX = -vX;
    } else if(getY(ball) + getHeight(ball) >= getHeight(window)) {
    lives--;
    waitForClick();
    setLocation(ball, 190, 290);
    setLocation(paddle, 150, 480);
    }
    
    GObject obj = detectCollision(window,ball);
    if(obj!=NULL) {
        if(obj == paddle) {
            vY = -vY;
    }   else if (strcmp(getType(obj),"GRect")==0) {
            removeGWindow(window,obj);
            points++;
            vY = -vY;
            updateScoreboard(window, label, points);
    
    }  

    }
    pause(10);
}
    // wait for click before exiting
    waitForClick();
    // game over
    closeGWindow(window);
    return 0;
}


/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
int x=0;
int y=40;

    for(int e = 0; e<ROWS; e++) {
    x=2;
        for(int i = 0; i<COLS;i++) {
         GRect bricks = newGRect(x,y,35,10);
        
            if(e==0) {
                setColor(bricks,"RED");
                setFilled(bricks,true);
            } if (e==1) {
                setColor(bricks,"FACC2E");
               setFilled(bricks,true);
            }  if (e==2) {
                setColor(bricks,"CE00F7");
              setFilled(bricks,true);
            }  if (e==3) {
                setColor(bricks,"BLUE");
                setFilled(bricks,true);
            } if (e==4) {
                setColor(bricks,"00DBF7");
                setFilled(bricks,true);
            }
          
              add(window,bricks);
              x = x+40;
   
        }
            y=y+13;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(190,290,20,20);
    add(window,ball);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
 GRect paddle = newGRect(150, 480, PADDLEW, PADDLEH);
      setFilled(paddle, true);
      setColor(paddle, "BLACK");
      add(window, paddle);
   
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel ("");
    setFont(label,"Courier-25");
    setColor(label,"DF7401");
    setFilled(label, true);
    add(window,label);
    setLocation(label,150,150);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
