/* 
 * The Shoe class manages all the playing cards functionality
 * There are 6 decks of cards (52 x 6 = 312 cards) in the shoe. This class
 * will handle shuffling, reshuffling when necessary, and dealing out cards.
 */
public class Shoe
{
  // This variable keeps track of where in the card stack we are
  // in the card shoe. It is referred to as the card counting variable
  // throughout this class.  
  public int shoeIndex = 0;
 
  // The number of decks in the shoe
  public static final int NUMBER_OF_DECKS = 1;
  
  // There should always be 52 cards in a playing deck
  public static final int NUMBER_OF_CARDS = 52;
  
  // This variable is an array of card values, and represents the entire
  // shoe of cards
  public int [] shoe = new int[ NUMBER_OF_DECKS * NUMBER_OF_CARDS ];
  /*
  // This is an array of file names for the playing card graphics
  public String [] cardGraphics = new String[ "ace_of_diamonds.svg", "2_of_diamonds.svg",
                      "3_of_diamonds.svg", "4_of_diamonds.svg",
                      "5_of_diamonds.svg", "6_of_diamonds.svg",
                      "7_of_diamonds.svg", "8_of_diamonds.svg",
                      "9_of_diamonds.svg", "10_of_diamonds.svg",
                      "jack_of_diamonds.svg", "queen_of_diamonds.svg",
                      "king_of_diamonds.svg", 
                      "ace_of_clubs.svg", "2_of_clubs.svg",
                      "3_of_clubs.svg", "4_of_clubs.svg",
                      "5_of_clubs.svg", "6_of_clubs.svg",
                      "7_of_clubs.svg", "8_of_clubs.svg",
                      "9_of_clubs.svg", "10_of_clubs.svg",
                      "jack_of_clubs.svg", "queen_of_clubs.svg",
                      "king_of_clubs.svg", 
                      "ace_of_hearts.svg", "2_of_hearts.svg",
                      "3_of_hearts.svg", "4_of_hearts.svg",
                      "5_of_hearts.svg", "6_of_hearts.svg",
                      "7_of_hearts.svg", "8_of_hearts.svg",
                      "9_of_hearts.svg", "10_of_hearts.svg",
                      "jack_of_hearts.svg", "queen_of_hearts.svg",
                      "king_of_hearts.svg", 
                      "ace_of_spades.svg", "2_of_spades.svg",
                      "3_of_spades.svg", "4_of_spades.svg",
                      "5_of_spades.svg", "6_of_spades.svg",
                      "7_of_spades.svg", "8_of_spades.svg",
                      "9_of_spades.svg", "10_of_spades.svg",
                      "jack_of_spades.svg", "queen_of_spades.svg",
                      "king_of_spades.svg"  ];
  */
  
  // Constructor
  public Shoe()
  {
    this.initShoe();
    this.shuffleShoe();
    //this.fakeShoe();
  }
  
  // For testing purposes
  public void fakeShoe()
  {
    int [] x = { 0, 7, 0, 7, 
      24, 21, 31, 43, 
      50, 51, 50, 51, 5, 6,
      50, 51, 10, 6, 2,
    1,1,1,1,1,1};
    this.shoe = x;
  }
  
  // This method initializes the shoe by adding cards (in order)
  // Another method is needed to randomize (shuffle) the cards
  public void initShoe()
  {
    int totalCards = NUMBER_OF_DECKS * NUMBER_OF_CARDS;
    for( int i = 0; i < totalCards; i = i + 1 )
    {
     this.shoe[ i ] = i % NUMBER_OF_CARDS; 
    }
 
    this.shoeIndex = 0;
  }

  // This method shuffles the cards by randomizing the contents of the shoe
  // and resets the shoeIndex.  This method essentially restarts the game!
  public void shuffleShoe()
  {
    // This code is adapted from 
    // http://www.hardcode.nl/subcategory_1/article_317-array-shuffle-function
    int length = this.shoe.length;
    int i = length;
    while( i-- > 0 )
    {
      int p = (int) ( Math.random() * length );
      int t = this.shoe[ i ];
      this.shoe[ i ] = this.shoe[ p ];
      this.shoe[ p ] = t;
    }
    
    this.shoeIndex = 0;
  }
  
  // This method deals out a card and moves the shoeIndex up by one.  
  // It returns the card index (0 through 51,inclusive) NOT the actual value of the card
  public int dealCard()
  {
    // check to see if there are enough cards in the deck
    // cards will only be dealt if there are still cards
    // the programmer should always check to see what how many cards
    // are left and manually shuffle the shoe.
    if( shoeIndex >= this.shoe.length )
    {
      // shuffle the deck when the last card is reached
      this.shuffleShoe();
    }
    
    int currentCard = this.shoe[ shoeIndex ];
    // Advance the shoe index by one
    this.shoeIndex = this.shoeIndex + 1;
    return currentCard;
    
  }
  
  // This method returns the shoe index
  public int getShoeIndex()
  {
    return this.shoeIndex;
  }
  
  // This method prints out the shoe's values.  The values range from 0 to 51 inclusive.
  public void printShoe()
  {
    int totalCards = NUMBER_OF_DECKS * NUMBER_OF_CARDS;
    
    System.out.println( "HERE: " + this.shoe.length) ;
    for( int i = 0; i < totalCards; i = i + 1 )
    {
      System.out.print( i + ": " + this.shoe[ i ] + "\t" );
    }
    
    System.out.print( "\nNumber of cards in shoe: " + totalCards );
    System.out.print( "\nCurrent shoe index: " + this.shoeIndex + "\n" );
  }
}