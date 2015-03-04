import java.util.*;
import java.awt.*;

public class Fireworks
{
  public static final Scanner CONSOLE = new Scanner ( System.in );
  public static final Random RANDOM = new Random ();
  public static final int WIDTH = 900;
  public static final int HEIGHT = 450;
  public static final int NUMBER_OF_SPARKS = 100;
  public static final int SPARK_WIDTH = 2;
  public static final int VELOCITY_RANGE = 50;
  
  public static void main ( String [] args )
  {
    int choice = 0;
    while ( choice < 1 || choice > 8 )
    {
      System.out.println ( "How many fireworks do you want to see? (1-8)" );
      choice = CONSOLE.nextInt();
    }
    
    Point [] positions = new Point [choice];
    Point [] initialVelocities = new Point [NUMBER_OF_SPARKS];
    Color [] colors = new Color [] { Color.RED, Color.GREEN, Color.MAGENTA };
    
    initializePositions ( positions );
    initializeInitialVelocity ( initialVelocities );
    
    DrawingPanel dp = new DrawingPanel ( WIDTH, HEIGHT );
    Graphics g = dp.getGraphics ();
    
    drawBackground ( g );
    startShow ( g, dp, positions, initialVelocities, colors );
    
  }
  
  public static void startShow ( Graphics g, DrawingPanel dp, Point [] positions, 
                                Point [] initialVelocities, Color [] colors )
  {
    double x = 0;
    double y = 0;
    for ( int i = 0; i < positions.length; i = i + 1 )
    {
      for ( double j = 0; j <= 10; j = j + .5 )
      {
        for ( int k = 0; k < initialVelocities.length; k = k + 1 )
        {
          x = positions[ i ].x + initialVelocities[ k ].x * j;
          y = positions[ i ].y + initialVelocities[ k ].y * j + .5 * 9.8 * j * j; 
          g.setColor ( colors [ i % 3 ] );
          g.fillOval ( (int)x, (int)y, SPARK_WIDTH, SPARK_WIDTH );
        }
        dp.sleep( 50 );
        drawBackground ( g );
      }
      dp.sleep( 100 ); 
      drawBackground ( g );
    }
  }
  
  public static void drawBackground ( Graphics g )
  {
    g.setColor ( Color.BLACK );
    g.fillRect ( 0, 0, WIDTH, HEIGHT );
  }
  
  public static void initializeInitialVelocity ( Point [] initialVelocities )
  {
    for ( int i = 0; i < initialVelocities.length; i = i + 1 )
    {
      int startX = -1 * VELOCITY_RANGE / 2;
      int startY = -1 * VELOCITY_RANGE;
      initialVelocities[i] = new Point ( RANDOM.nextInt ( VELOCITY_RANGE + 1 ) + startX, 
                                        RANDOM.nextInt ( VELOCITY_RANGE + 1 ) + startY );
    }
  }
  
  public static void initializePositions ( Point [] positions )
  {
    for ( int i = 0; i < positions.length; i = i + 1 )
    {
      positions[i] = new Point ( RANDOM.nextInt (401) + 200, RANDOM.nextInt (201) + 150 );
    }
  }
}