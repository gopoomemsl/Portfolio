// FallingObject.java
// Paul Szyller
// Lab 4

import java.util.*;
import java.awt.*;
// Imports to use the Scanner and DrawingPanel functions.

public class FallingObject
  // This program prompts the user for a ball color, an initial position ( x and y ), 
  // and an initial velocity ( x and y ), then it animates a ball of the given color 
  // being thrown from the given initial position with the given initial velocity in 
  // front of a backfround.
{
  // Class Constants:
  public static final int WIDTH = 1024; // Width of the DrawindPanel
  public static final int HEIGHT = 768; // Height of the DrawingPanel
  public static final int FLOOR_HEIGHT = 50; // Height of the floor from the bottom of the panel
  public static final int BALL_SIZE = 20; // Size of the ball being thrown
  public static final int N_STEPS = 25; // Number of steps in the animation
  public static final Scanner CONSOLE = new Scanner ( System.in ); // Seting up the Scanner for use inputs
  
  public static void main ( String [] args )
    // This is the main method, it prompts the user for all the requiered inputs and perform a check 
    // on those values. If the values are inputed incorrectly the program will display an error message 
    // and stop, otherwise the program will continue, set up the DrawingPanel, and start the animation 
    // method. It does not call the background and signature method, since this is animated they are 
    // called in the loop of the animation method instead.
  {
    //__________________________________________________
    //______________________INPUTS______________________
    //__________________________________________________
    
    // Ball Color:
    System.out.println ( "Select a color for your ball, choose between:" + 
                        "\n\t-Red\n\t-Blue\n\t-Green" );
    String ballColor = CONSOLE.nextLine ();
    Color bColor = getBallColor ( ballColor ); // Once the color is inputed as a String, the getBallColor 
                                               // method is called to translate it into a Color class
    
    // Initial x position:
    System.out.println ( "Select an initial position:" +
                        "\nx value:" +
                        "\n(must be between 0 and " + WIDTH );
    int inx = CONSOLE.nextInt ();
    
    // Initial y position:
    System.out.println ( "y value:" +
                        "\n(must be between 0 and " + ( HEIGHT - FLOOR_HEIGHT - BALL_SIZE ) ); 
                         //I know the lab said the values had to be within bounds of the DrawingPanel, 
                         //so that would be "between 0 and HEIGHT" but it did not make sense to me 
                         //to start below the ground so it is "between 0 and HEIGHT - FLOOR_HEIGHT - BALL_SIZE"
    int iny = CONSOLE.nextInt ();
    
    // Initial x velocity:
    System.out.println ( "Select an initial velocity:" +
                        "\nx value:" +
                        "\n(must be between -100 and 100" );
    int vx = CONSOLE.nextInt ();
    
    // Initial y velocity:
    System.out.println ( "y value:" +
                        "\n(must be between -100 and 100" );
    int vy = CONSOLE.nextInt ();
    //__________________________________________________
    //__________________________________________________
    //__________________________________________________
    
    
    // If the values' given range are not met, print an error message:
    if ( inx < 0 || inx > WIDTH || iny < 0 || iny > ( HEIGHT - FLOOR_HEIGHT ) || vx < -100 || vx > 100 || vy < -100 || vy > 100 )
    {
      System.out.println ( "ERROR: Values are out of bounds." );
    }
    
    // Else, if the values' given range are met, continue with the program:
    else
    {
      DrawingPanel dp = new DrawingPanel ( WIDTH, HEIGHT );
      Graphics g = dp.getGraphics ();
      
      drawBall ( g, dp, bColor, inx, iny, vx, vy ); // This is the animation method, we use all of the previously 
                                                    // inputed variables (using the Color class bColor and not the
                                                    // String ballColor) and the DrawingPanel and Graphics variables 
                                                    // as parameters. 
    } 
  }
  
  public static Color getBallColor ( String ballColor )
    // This method takes in a String and if it corresponds to one of the choices it will return the 
    // corresponding Color class. It is not case sensitive and if the given String is not one of 
    // the choices, it will return the Color as yellow.
  {
    Color c = new Color ( 255, 255, 255 );
    if ( ballColor.equalsIgnoreCase ( "red" ) || ballColor.equalsIgnoreCase ( "r" ) )
    {
      c = Color.RED;
    }
    else if ( ballColor.equalsIgnoreCase ( "blue" ) || ballColor.equalsIgnoreCase ( "b" ) )
    {
      c = Color.BLUE;
    }
    else if ( ballColor.equalsIgnoreCase ( "green" ) || ballColor.equalsIgnoreCase ( "g" ) )
    {
      c = Color.GREEN;
    }
    else
    {
      c = Color.YELLOW;
    }
    return c;
  }
  
  public static void drawBackground ( Graphics g )
    // This method simply draws the background. This includes a light blue "sky" and 
    // a brown "floor", the height of the floor is dependant on the previously set class
    // constant FLOOR_HEIGHT
  {
    Color c = new Color ( 170, 197, 242 ); // light blue
    g.setColor ( c );
    g.fillRect ( 0, 0, WIDTH, HEIGHT );
    
    c = new Color ( 117, 89, 65 ); // brown
    g.setColor ( c );
    g.fillRect ( 0, HEIGHT - FLOOR_HEIGHT, WIDTH, FLOOR_HEIGHT );
  }
  
  public static void signDrawing ( Graphics g )
    // This method simply prints out the "signature" on the drawing
  {
    g.setColor ( Color.RED );
    g.drawString ( "Lab 4 by PAUL SZYLLER", 10, 20 );
  }
  
  public static void drawBall ( Graphics g, DrawingPanel dp, Color bColor, int inx, int iny, int vx, int vy )
    // This is the animation method. It uses all of the parameters in an animated 
    // loop to calculate the new position an draw the ball at every step.
  {
    for ( int i = 0; i < N_STEPS; i = i + 1 ) // The number of steps has been made a class constant
    {
      int x = inx + vx * i; 
      // next x position = initial x position + x velocity * step number
      double y = iny - vy * i + .5 * 9.8 * i * i; 
      // next y position = initial y position + negative y velocity (because of the DP coordinate system)
      // * step number + .5 * gravity (positive because of the DP coordinate system) * step number squared
      
      drawBackground ( g ); 
      signDrawing ( g );
      g.setColor ( bColor );
      // The background and signature are redrawn in every loop, then the ball color is set
      
      if ( y + BALL_SIZE > HEIGHT - FLOOR_HEIGHT ) 
        // For every loop, the position of the ball is checked to make sure it has not fallen 
        // below the floor, if it has it is set on top of the floor and the loop ends there
      {
        y = HEIGHT - FLOOR_HEIGHT - BALL_SIZE;
        g.fillOval ( x, (int)y, BALL_SIZE, BALL_SIZE );
        break;
      }
      
      else
        // If it hasn't, then the ball is drawn and the loop continues
      {
        g.fillOval ( x, (int)y, BALL_SIZE, BALL_SIZE );
      }
      
      dp.sleep( 50 ); 
      // This statement animates the drawing, it will make each frame last .50 sec then relaunch the loop
    }
  }
}