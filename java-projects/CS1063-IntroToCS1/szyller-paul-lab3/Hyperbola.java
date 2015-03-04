// Hyperbola.java
// Paul Szyller
// Lab 3


import java.awt.*; 
import java.util.*;
// Those are the imports to use the DrawingPanel functions and the Scanner and Random classes.

public class Hyperbola
  // This program draws 5 concentric circles each in a different 
  // shade of gray, a hyperbola with each line a different color, 
  // and signs the drawing with my name.
{
  //Class constants:
  public static final int WIDTH = 600; //Width of the DrawingPanel
  public static final int HEIGHT = 600; //Height of the DrawingPanel
  public static final int N_CIRCLES = 5; //Number of concentric circles
  public static final Random RANDOM = new Random ();
  public static final Scanner CONSOLE = new Scanner ( System.in ); 
  
  public static void main( String [] args )
    // This is the main method, it prompts the user for the number of pixels to use 
    // as intervals between each lines of the hyperbola, sets up the DrawingPanel and 
    // Graphics variables, then calls the other methods to make the drawing.
  {
    System.out.println ( "What interval should be used for the hyperbola?" + 
                        "\n(in pixels)" );
    int interval = CONSOLE.nextInt ();
    
    DrawingPanel dp = new DrawingPanel( WIDTH, HEIGHT );
    Graphics g = dp.getGraphics();
    
    drawCircles ( g );
    drawHyperbola ( g, interval );
    drawText ( g );
  }
  
  public static void drawCircles ( Graphics g )
    // This method draws a number of concentric circle (based on the class constant N_CIRCLES).
    // The circles are drawn in different shades of gray going from darker on the outside to 
    // lighter in the inside.
  {
    for ( int i = 0; i < N_CIRCLES; i = i + 1 )
    {
      int cInc = 10; //Color increment
      int grayValue = 128 + cInc * i; //Base value of 128 + increments
      Color c = new Color ( grayValue, grayValue, grayValue ); //R=G=B for grays
      g.setColor ( c );
      
      int sInc = 20; //Size increment
      g.fillOval ( sInc * i, sInc * i, WIDTH - 2 * sInc * i, HEIGHT - 2 * sInc * i);
    }
  }
  
  public static void drawHyperbola ( Graphics g, int interval )
    // This method draws the Hyperbola with a random color for every line.
    // We get the random color by calling the method randomizeColor.
  {
    int numberOfLines = HEIGHT / 2 / interval;
    for ( int i = 0; i <= numberOfLines; i = i + 1 )
    {
      //Top Left Quadrant
      Color c = randomizeColor ();
      g.setColor ( c );            
      g.drawLine ( i * interval, HEIGHT / 2, WIDTH / 2, HEIGHT / 2 - i * interval );
      
      //Top Right Quadrant
      c = randomizeColor ();
      g.setColor ( c );
      g.drawLine ( WIDTH / 2, i * interval, WIDTH / 2 + i * interval, HEIGHT / 2 );
      
      //Bottom Left Quadrant
      c = randomizeColor ();
      g.setColor ( c );
      g.drawLine ( WIDTH / 2, HEIGHT / 2 + i * interval, i * interval, HEIGHT / 2 );
      
      //Bottom Right Quadrant
      c = randomizeColor ();
      g.setColor ( c );
      g.drawLine ( WIDTH / 2 + i * interval, HEIGHT / 2, WIDTH / 2, HEIGHT - i * interval );
      // The color is randomized between each line instead of once per loop so as 
      // to look more random and not have the same colors repeating 4 times.
    }
  }
  
  public static Color randomizeColor ()
    // This is the method called by the hyperbola method to randomize the color
    // It gets 3 random values and apply them to a color for the values of red, green, 
    // and blue each. The new color created is then returned.
  {
    int randomRed = RANDOM.nextInt ( 256 );
    int randomGreen = RANDOM.nextInt ( 256 );
    int randomBlue = RANDOM.nextInt ( 256 );
    Color c = new Color ( randomRed, randomGreen, randomBlue );
    return c;
  }
  
  public static void drawText ( Graphics g )
    // This last method simply draws a string stating the assignement's and my name
    // in the lower left hand corner of the DrawingPanel.
  {
    g.setColor ( Color.RED );
    g.drawString ( "Lab 3 by PAUL SZYLLER", 10, HEIGHT - 10 ); 
  }
}