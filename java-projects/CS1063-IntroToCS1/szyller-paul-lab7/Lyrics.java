// Lyrics.java
// Paul Szyller
// Lab 7

public class Lyrics
  //This class prints out the lyrics to the song "Carry On Wayward Son" by Kansas.
{
  public static void main ( String [] args )
  {
    printHeader ();    
    printChorus ();
    printVerse1 ();
    printVerse2 ();
    printChorus ();
    printVerse3 ();
  }
  
  public static void printHeader ()
    //This method prints out the header to the lab.
  {
    System.out.print ( "Lab 7 written by Paul Szyller\n" + 
                      "\"Carry On Wayward Son\" by Kansas\n" + 
                      "Lyrics from " + 
                      "http://www.azlyrics.com/lyrics/kansas/carryonwaywardson.html\n\n" );
  }
  
  public static void printVerse1 ()
    //This method prints out the first verse to the song.
  {
    System.out.println ( "Ah\n\n" + 
                        "Once I rose above the noise and confusion\n" + 
                        "Just to get a glimpse beyond this illusion\n" + 
                        "I was soaring ever higher, but I flew too high\n" );
  }
  
  public static void printVerse2 ()
    //This method prints out the second verse to the song.
  {
    System.out.println ( "Though my eyes could see I still was a blind man\n" + 
                        "Though my mind could think I still was a mad man\n" + 
                        "I hear the voices when I'm dreaming,\n" +
                        "I can hear them say\n" );
  }
  
  public static void printVerse3 ()
    //This method prints out the third verse to the song.
  {
    System.out.println ( "Masquerading as a man with a reason\n" + 
                        "My charade is the event of the season\n" + 
                        "And if I claim to be a wise man,\n" +
                        "Well, it surely means that I don't know" );
  }
  
  public static void printChorus ()
    //This method prints out the Chorus.
  {
    System.out.println ( "\tCarry on my wayward son,\n" + 
                        "\tThere'll be peace when you are done\n" + 
                        "\tLay your weary head to rest\n" + 
                        "\tDon't you cry no more\n" );
  }
}