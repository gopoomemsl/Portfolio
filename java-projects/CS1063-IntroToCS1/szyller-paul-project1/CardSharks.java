// CardSharks.java
// Paul Szyller
// Project 1

import javax.swing.*;
import javax.imageio.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.geom.*;

// This class is responsible for creating and managing the graphical user interface
// and the game functionality for CardSharks.
public class CardSharks extends JFrame implements ActionListener, WindowListener
{
  // Class constants for the width and height of the frame
  public static final int WIDTH = 1150;
  public static final int HEIGHT = 600;
  
  public static final int BETTING_PANEL_WIDTH = 150;
  public static final int NUMBER_OF_CARDS = 8;
  
  // Class constants for the width and height of the cards
  public static final int CARD_WIDTH = 100;
  public static final int CARD_HEIGHT = 144;
  
  public static final int DEFAULT_CREDITS = 200;
  
  // Class constant that represents the default bet
  public static final int BET = 20;
  
  // Array of file names for card images
  public static final String [] cards = {
    "ace_of_diamonds.gif", "2_of_diamonds.gif", "3_of_diamonds.gif", "4_of_diamonds.gif",
    "5_of_diamonds.gif", "6_of_diamonds.gif", "7_of_diamonds.gif", "8_of_diamonds.gif",
    "9_of_diamonds.gif", "10_of_diamonds.gif", "jack_of_diamonds2.gif", "queen_of_diamonds2.gif",
    "king_of_diamonds2.gif", "ace_of_clubs.gif", "2_of_clubs.gif", "3_of_clubs.gif", "4_of_clubs.gif",
    "5_of_clubs.gif", "6_of_clubs.gif", "7_of_clubs.gif", "8_of_clubs.gif", "9_of_clubs.gif", 
    "10_of_clubs.gif", "jack_of_clubs2.gif", "queen_of_clubs2.gif", "king_of_clubs2.gif", "ace_of_hearts.gif", 
    "2_of_hearts.gif", "3_of_hearts.gif", "4_of_hearts.gif", "5_of_hearts.gif", "6_of_hearts.gif",
    "7_of_hearts.gif", "8_of_hearts.gif", "9_of_hearts.gif", "10_of_hearts.gif", "jack_of_hearts2.gif", 
    "queen_of_hearts2.gif", "king_of_hearts2.gif", "ace_of_spades.gif", "2_of_spades.gif",
    "3_of_spades.gif", "4_of_spades.gif", "5_of_spades.gif", "6_of_spades.gif", "7_of_spades.gif", 
    "8_of_spades.gif", "9_of_spades.gif", "10_of_spades.gif", "jack_of_spades2.gif", "queen_of_spades2.gif", 
    "king_of_spades2.gif" };
  // file name for the card back
  public static final String cardBack = "back.gif";
  
  // Class variables for all UI components
  public JPanel scorePanel;
  public JButton playButton;
  public JButton resetButton;
  public JLabel creditsLabel;
  public JTextField creditsTextField;
  
  public JButton betHigherButton;
  public JButton betLowerButton;
  public JButton betTieButton; // A new class variable is declared for the additional button
  public JPanel bettingPanel;
  public JButton takeWinningsButton;
  
  // This array holds a panel of cards
  
  public JPanel cardPanel;
  public JLabel cardPanelLabel;
  public JPanel feedbackPanel;
  public JTextArea feedbackTextArea;
  
  // Shoe object which represents one more sets of playing cards
  public Shoe cardShoe;
  
  // Class variable that keeps track of the bankroll - the default is 200
  public int credits = DEFAULT_CREDITS;
  
  // These class variables maintain the state of the entire game
  
  // Class variable that tells us if the game is in session
  public Boolean gameInSession = false;
  // Class variable that tells us which card we are on. This index also tells us
  // how much to pay out (2^cardPosition).
  public int cardPosition = 0;
  // Class variable that keeps track of the current card value
  public int currentCardValue = -999;
    
  // Main method -- do not change
  public static void main( String [] args )
  {
    new CardSharks();
  }

  // Constructor - buildings the graphical user interface
  public CardSharks()
  {
    super( "Project 1 - Card Sharks by PAUL SZYLLER" ); // title of title bar
    
    // set the layout of the frame
    setSize( WIDTH, HEIGHT );
    setLayout( new BorderLayout() );
    
    // Create the scoreboard panel that displays the user's bankroll
    scorePanel = new JPanel();
    scorePanel.setBackground( Color.WHITE );
    creditsLabel = new JLabel( "Credits: " );
    creditsTextField = new JTextField( 15 );
    creditsTextField.setEditable( false );
    playButton = new JButton( "Play 20 Credits" );
    resetButton = new JButton( "New Simulation" );
    scorePanel.add( resetButton );
    scorePanel.add( creditsLabel );
    scorePanel.add( creditsTextField );
    scorePanel.add( playButton );
    
    // Create the betting buttons
    bettingPanel = new JPanel();
    bettingPanel.setPreferredSize( new Dimension( BETTING_PANEL_WIDTH, 480 ) );
    betHigherButton = new JButton( "Higher" );
    betLowerButton = new JButton( "Lower" );
    betTieButton = new JButton( "   Tie    " ); // This is the new button we added
    takeWinningsButton = new JButton( "Take Winnings" );
    bettingPanel.add( betHigherButton );
    bettingPanel.add( betLowerButton );
    bettingPanel.add( betTieButton ); // Here we add the button to the bettingPanel
    bettingPanel.add( takeWinningsButton );
    
    // Create the card panel
    cardPanel = new JPanel();
    cardPanel.setPreferredSize( new Dimension( WIDTH / 2, 0 ) );
    cardPanel.setBackground( Color.CYAN ); //Changed cards' panel from green to cyan
    cardPanel.setBorder( BorderFactory.createLineBorder( Color.ORANGE, 5 ) ); //Changed the border's color to orange
    cardPanelLabel = new JLabel( "CARDS" );
    cardPanel.add( cardPanelLabel );
    
    // Create the feedback panel that displays the feedback from the game
    feedbackPanel = new JPanel();
    feedbackPanel.setBackground( Color.WHITE );
    feedbackTextArea = new JTextArea( 14, 80 );
    JScrollPane scrollPane = new JScrollPane( feedbackTextArea ); 
    feedbackTextArea.setText( "" );
    feedbackTextArea.setEditable( false );
    feedbackPanel.add( scrollPane );

    // add action listeners
    // All user interface components that expect user input (like pressing a button) needs
    // to have an action listener added to it.  All components that have an action listener
    // added to it will be processed by the actionPerformed() method.
    resetButton.addActionListener( this );
    playButton.addActionListener( this );
    betHigherButton.addActionListener( this );
    betLowerButton.addActionListener( this );
    betTieButton.addActionListener ( this ); // This is the action listener for the new button
    takeWinningsButton.addActionListener( this );
    
    // add all the panels to the main JFrame
    getContentPane().add( scorePanel, BorderLayout.NORTH );
    getContentPane().add( bettingPanel, BorderLayout.EAST );
    getContentPane().add( cardPanel, BorderLayout.CENTER );
    getContentPane().add( feedbackPanel, BorderLayout.SOUTH );
 
    setVisible( true );
    
    // initialize the card Shoe object
    cardShoe = new Shoe();
    
    // update the text field to show the credits
    updateCredits();
    // reset the simulation
    resetSimulation();
    // force the user to click New Simulation before playing
    playButton.setEnabled( false );
  }

  // Processes any button events.  Do not change.
  // When a button on the interface is clicked, it comes to this method.
  // This method determines which button is clicked and calls its respective methods.
  public void actionPerformed( ActionEvent event )
  {
    if( event.getSource().equals( resetButton ) )
    {
      resetSimulation();
    }
    else if( event.getSource().equals( playButton ) )
    {
      startGame();
    }
    else if( event.getSource().equals( betHigherButton ) )
    {
      betHigher();
    }
    else if( event.getSource().equals( betLowerButton ) )
    {
      betLower();
    }
    else if( event.getSource().equals( betTieButton ) ) // This is to link the new button created to our 
                                                        // corresponding method betTie
    {
      betTie();
    }
    else if( event.getSource().equals( takeWinningsButton ) )
    {
      takeWinnings();
    }
  }
    
  // This method takes the card value (0-51) as an int and returns the card's 
  // ordinal rank (0 for 2s to 12 for aces) as another int so that the cards 
  // can later be compared
  public static int getOrdinalRank ( int cardValue )
  {
    return ( cardValue + 12 ) % 13;
  }
  
  // This takes the card value (0-51) as an int and returns a String of the card's 
  // rank for display purposes
  public static String getRankValue ( int cardValue )
  {
    if ( cardValue % 13 == 0 ) // 0, 13, 26, 39 => Aces
    {
     return "A";
    }
    
    else if ( cardValue % 13 == 10 ) // 10, 23, 36, 49 => Jacks
    {
      return "J";
    }
    
    else if ( cardValue % 13 == 11 ) // 11, 24, 37, 50 => Queens
    {
      return "Q";
    }
    
    else if ( cardValue % 13 == 12 ) // 12, 25, 38, 51 => Kings
    {
      return "K";
    }
    
    else // The rest
    {
      return "" + ( cardValue % 13 + 1 );
    }
  }
  
  // This method takes the card value (0-51) as an int and returns a char 
  // representing the card's suit for display purposes
  public static char getCardSuit ( int cardValue )
  {
    if ( cardValue >= 0 && cardValue <= 12 )
    {
      return '\u2666'; // Diamonds
    }
    
    else if ( cardValue >= 13 && cardValue <= 25 )
    {
      return '\u2663'; // Clubs
    }
    
    else if ( cardValue >= 26 && cardValue <= 38 )
    {
      return '\u2665'; // Hearts
    }
    
    else
    {
      return '\u2660'; // Spades
    }
  }
  
  // This method is called when the user presses the HIGHER button, it stores the 
  // current card value in a variable (previousCardValue), then calls the method 
  // revealCard to update the current card value and then compares both. 
  // If the bet is correct and the new card value (or currentCardValue) is higher 
  // than the old one (or previousCardValue), a message is displayed and the method 
  // then checks the current card's position, if it is the last one the game session 
  // ends and the winnings are given to the user. 
  // If the bet is incorrect, than a different message is displayed and the method lose() is called.
  public void betHigher()
  {
    int previousCardValue = currentCardValue;
    revealCard();
    if ( getOrdinalRank ( currentCardValue ) > getOrdinalRank ( previousCardValue ) )
    {
      appendFeedbackText( "You guessed HIGHER correctly!" );
      if ( cardPosition == NUMBER_OF_CARDS )
      {
        takeWinnings ();
        gameInSession = false;
        disableBettingPanel ();
      }
    }
    else
    {
      appendFeedbackText ( "You guessed HIGHER incorrectly! GAME OVER" );
      lose();
    }
  }
  
  // This is the same as the previous method but for the LOWER bet button.
  public void betLower()
  {
    int previousCardValue = currentCardValue;
    revealCard();
    if ( getOrdinalRank ( currentCardValue ) < getOrdinalRank ( previousCardValue ) )
    {
      appendFeedbackText( "You guessed LOWER correctly!" );
      if ( cardPosition == NUMBER_OF_CARDS )
      {
        takeWinnings ();
        gameInSession = false;
        disableBettingPanel ();
      }
    }
    else
    {
      appendFeedbackText ( "You guessed LOWER incorrectly! GAME OVER" );
      lose();
    }
  }
  
  // This is the same as the previous method but for the TIE bet button.
  public void betTie()
  {
    int previousCardValue = currentCardValue;
    revealCard();
    if ( getOrdinalRank ( currentCardValue ) == getOrdinalRank ( previousCardValue ) )
    {
      appendFeedbackText( "You guessed a TIE correctly!" );
      if ( cardPosition == NUMBER_OF_CARDS )
      {
        takeWinnings ();
        gameInSession = false;
        disableBettingPanel ();
      }
    }
    else
    {
      appendFeedbackText ( "You guessed a TIE incorrectly! GAME OVER" );
      lose();
    }
  }
  
  // This method handles the case when the user has won and (taken winnings by choice
  // or because s/he was dealt all the cards).
  public void takeWinnings()
  {
    if( cardPosition > 1 )
    {
      int payout = (int) Math.pow( 2, ( cardPosition - 2 ) ) * BET;
      awardCredits( payout );
      updateCredits();
    
      appendFeedbackText( "WINNER! " + "You won " + payout + " credits in this game. GAME OVER." );
      newGame();
    }
    else
    {
      appendFeedbackText( "You won 0 credits in this game. GAME OVER." );
      newGame();
    }
  }
  
  // This method handles the case when the user has lost. It will check whether or not
  // the user has enough money to continue.
  public void lose()
  {
    // turn off the gameInSession flag
    gameInSession = false;
    
    // if the user does not have enough money to cover the first bet, then the
    // enter simulation is over
    if( credits < BET )
    {
      appendFeedbackText( "You do not have enough credits to play. SIMULATION OVER." );
      // turn off the user interface components
      playButton.setEnabled( false );
      disableBettingPanel();
    }
    else
    {
      // the user lost but still has money to play
      newGame();
    }
  }
  
  
  // This method shows the card in the current position
  public void showCard( int cardValue )
  { 
    // retrieves and loads the image and displays it according to the parameters
      BufferedImage img = null;
      try 
      {
        img = ImageIO.read( new File( "graphics/" + cards[ cardValue ] ) );
      } 
      catch( IOException e ) 
      {
      }
      // assign the graphics context for the card panel
      Graphics g = cardPanel.getGraphics();
      // show based on its cardPosition
      g.drawImage( img, cardPosition * ( CARD_WIDTH + 15 ) + 40, 50, CARD_WIDTH, CARD_HEIGHT, null );
  }
  
  // This method reveals a new card
  public void revealCard()
  {
    // only call this method if the game is in session
    if( gameInSession )
    {
      // deal out a new card from the cardShoe
      currentCardValue = cardShoe.dealCard();
      // call the method to display the card
      showCard( currentCardValue );
      // increase the cardPosition for next time
      cardPosition = cardPosition + 1;
      // Display a message in the feedback message telling the user what card was shown including rank and suit
      appendFeedbackText ( "Your card is the " + getRankValue ( currentCardValue ) + " of " + getCardSuit ( currentCardValue ) );
    }
  }
  
  // This method is used to show the 
  // It assumes that the user had enough money to make a bet
  public void newGame()
  {
    // allow the user to click on the play button
    playButton.setEnabled( true );
    // disable the betting panel--it will be enabled once the user clicks play
    disableBettingPanel();
  }

  // This method is called after the user has clicked on the play button.
  public void startGame()
  {
    // take away the bet
    awardCredits( -BET );
    // update the display
    updateCredits();
    // disable the play button
    playButton.setEnabled( false );
    // set the flag
    gameInSession = true;
    // enable the betting buttons
    enableBettingPanel();
    // clear the feedback
    clearFeedbackText();
    // set a message to say it's a new game
    appendFeedbackText( "##### NEW GAME #####" );
    // reset the card position
    cardPosition = 0;
    // draw the backs of the cards
    drawBacks();
    // reveal the first card
    revealCard();
  }
  
  // Reset the game
  public void resetSimulation()
  {
    // draw the backs of the cards
    drawBacks();
    // disable the betting panel (until the user plays).
    disableBettingPanel();
    // reset the credits
    credits = DEFAULT_CREDITS;
    // update the credits display
    updateCredits();
    // reset the card position to 0 
    cardPosition = 0;
    // enable the play button
    playButton.setEnabled( true );
    // clear the feedback text
    clearFeedbackText();
    // add a message saying that this is a new simulation
    appendFeedbackText( "-------------- New Simulation --------------" );
  }

    // This method draws the back of five cards.  Do not change.
  public void drawBacks()
  { 
    // retrieves and loads the image and displays it according to the parameters
    BufferedImage img = null;
    try 
    {
      img = ImageIO.read( new File( "graphics/" + cardBack ) );
    } 
    catch( IOException e ) 
    {
    }
    // assign the graphics context for the card panel
    Graphics g = cardPanel.getGraphics();
    
    for( int i = 0; i < NUMBER_OF_CARDS; i = i + 1 )
    {
      g.drawImage( img, i * ( CARD_WIDTH + 15 ) + 40, 50, CARD_WIDTH, CARD_HEIGHT, null );
      
      if( i > 0 )
      {
        int value = (int) Math.pow( 2, ( i - 1 ) );
        g.drawString( "x" + value, i * ( CARD_WIDTH + 15 ) + 80, CARD_HEIGHT + 75 );
      }
    }
  }
  
  // This method enables all the buttons in the betting panel so the user can 
  // click on them. This is useful for when the user is playing the game.
  public void enableBettingPanel()
  {
    betHigherButton.setEnabled( true );
    betLowerButton.setEnabled( true );
    betTieButton.setEnabled( true ); // enable the TIE button
    takeWinningsButton.setEnabled( true );
  }
  
  // This method disables all the buttons in the betting panel so the user cannot 
  // click on them. This is useful for when the user is not in the middle of a game.
  public void disableBettingPanel()
  {
    betHigherButton.setEnabled( false );
    betLowerButton.setEnabled( false );
    betTieButton.setEnabled( false ); // disable the TIE button
    takeWinningsButton.setEnabled( false );
  }
    
  // This method awards an amount of credits won. If you are deducting credits,
  // then pass in a negative number
  // You should also manually update the credits display. Do not change.
  public void awardCredits( int amount )
  {
    credits = credits + amount;
  }
  
  // This method awards the amount in the Bankroll textbox. Do not change.
  public void updateCredits()
  {
    creditsTextField.setText( "" + credits );
  }
  
  // These methods are used to control the feedback text box at the bottom of the
  // screen. You must use these methods, but do not change these methods. 
  
  // This method APPENDS the text in the feedback text box. A new line is entered
  // every time this method is called.  
  public void appendFeedbackText( String text )
  {
    String temp = feedbackTextArea.getText() + text + "\n";
    feedbackTextArea.setText( temp );
  }
  
  // This method clears the feedback text box.  It should be called every time
  // a new hand is dealt.  
  public void clearFeedbackText()
  {
    feedbackTextArea.setText( "" );
  }
  
  // IGNORE EVERYTHING BELOW THIS COMMENT
  
  // WindowListener methods - do not change
  public void windowActivated( WindowEvent we )
  {
  }
  
  public void windowDeactivated( WindowEvent we )
  {
  }
  
  public void windowClosing( WindowEvent we )
  {
    setVisible( false );
    System.exit( 0 );
  }
  
  public void windowClosed( WindowEvent we )
  {
  }
  
  public void windowDeiconified( WindowEvent we )
  {
  }
  
  public void windowIconified( WindowEvent we )
  {
  }
  
  public void windowOpened( WindowEvent we )
  {
  }
}