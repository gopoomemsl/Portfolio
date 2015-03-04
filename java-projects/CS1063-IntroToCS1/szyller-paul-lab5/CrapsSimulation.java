// CrapsSimulation.java
// Briana Alderete
// Olumide Sokoya
// Paul Szyller
// Lab 5

import java.util.*;

// This program tries to emulate a game of craps, with simplier rules.
// As long as the user has enough funds, it displays a menu of possible bets and prompts 
// the user for a choice. The user will bet Pass or Don't Pass on the dice rolls and collects
// the appropriate bankroll based on the results of said rolls. If the first roll sets a Point,
// the user also becomes able to place field bets.
public class CrapsSimulation
{
  public static final Random RANDOM = new Random (); // sets up the random object to use during dice rolls
  public static final Scanner CONSOLE = new Scanner ( System.in ); // sets up the console to prompt user input
  public static double bankroll = 25; // sets up the bankroll as a class variable for easier access 
                                      // through the different methods of the program
  public static boolean fieldBet = false; // sets up the fieldBet option as a class variable for easier 
                                          // access through the different methods of the program
  
  
  // This is the main method, it runs a loop that checks if the user has enough funds for a game of craps.
  // If the user has enough funds, the menu will be displayed, the user's choice registered, and a game of 
  // craps will then start if the user did not choose the option to quit the game. If the user chose to end 
  // the game though, or if the user does not have enough funds left, an appropriate message will be displayed 
  // and the program will end.
  public static void main ( String [] args )
  {    
    while ( bankroll >= 2.5 ) // checks if the user has enough funds to play
    {
      displayMenu ();
      int choice = computeChoice ();
      if ( choice == 3 ) // if the user chose to quit
      {        
        System.out.printf ( "Game Over\nYour final bankroll balance is: $%.2f\n", bankroll);
        break;
      }
      else // else a game is started with the user's choice of bet
      {
        playGame ( choice );
      }
    }
    if ( bankroll < 2.5 ) // if the loop is ended because the bankroll falls under 2.5 and not 
                          // because the user picked option 3
    {
      System.out.println ( "Your balance fell below $2.50\nGame Over" );
    }
  }
  
  
  // This method is the method that emulates a game of craps it will deduct the user's bet, 
  // roll the dice, and act according to the results.
  public static void playGame ( int choice )
  {
    bankroll = bankroll - 2.5; // deduct the user's bet
    int dice1 = rollDice (); // roll the dices
    int dice2 = rollDice ();
    int currentRoll = dice1 + dice2;
    System.out.printf ( "Come-out Roll: Shooter rolls a %d (%d, %d).\n", currentRoll, dice1, dice2 );
    
    if ( currentRoll == 7 || currentRoll == 11 ) // if the first roll is a 7 or 11
    {
      System.out.println ( "Come-out Roll is a 7 or 11:  Pass bets WIN.  Don't Pass bets LOSE." );
      passWin ( choice ); // calls on the method to reward a Pass bet
    }
    
    else if ( currentRoll == 2 || currentRoll == 3 || currentRoll == 12 ) // if the first roll is a 2, 3, or 12
    {
      System.out.println ( "Come-out Roll is Craps (2, 3, or 12): Don't Pass bets WIN.  Pass bets LOSE." );
      dontPassWin ( choice ); // calls on the method to reward a Don't Pass bet
    }
    
    else // if the first roll is anything else
    {      
      System.out.printf ( "The point is %d.\n", currentRoll );
      int point = currentRoll; // sets the point
      
      do // This loop will keep rolling the dice until a 7, 12, or the point is rolled, 
         // prompting the user for field bets every time
      {
        makeFieldBet (); // calls on the method to set up an eventual field bet  
        dice1 = rollDice (); // roll the dices
        dice2 = rollDice ();
        currentRoll = dice1 + dice2;
        System.out.printf ( "Shooter rolls a %d (%d, %d).\n", currentRoll, dice1, dice2 );
        computeFieldBet ( currentRoll ); // calls on the method to reward or not a field bet   
      }
      while ( currentRoll != 7 && currentRoll != 12 && currentRoll != point );
      
      if ( currentRoll == point ) // if the user rolls the point again before a 7 or 12
      {
        System.out.println ( "Shooter hits the Point: Pass bets WIN.  Don't Pass bets LOSE." );
        passWin ( choice ); // calls on the method to reward a Pass bet
      }
      
      else if ( currentRoll == 7 ) // if the user rolls a 7 before a 12 or the point
      {
        System.out.println ( "Shooter rolled a 7 before Point: Don't Pass bets WIN.  Pass bets LOSE." );
        dontPassWin ( choice ); // calls on the method to reward a Don't Pass bet
      }
      
      else if ( currentRoll == 12 ) // if the user rolls a 12 before a 7 or the point
      {
        bankroll = bankroll + 2.5; // the user's bet is given back
        System.out.println ( "Shooter rolled a 12 before Point: All bets push.\n" );
      }      
    }        
  }
  
  
  // This method simply displays the main menu
  public static void displayMenu ()
  {
    System.out.printf ( "Craps Simulation\n1. Bet on Pass\n2. Bet on Don't Pass\n" +
                       "3. Stop Playing\nBankroll: $%.2f\nEnter your choice", bankroll );    
  }
  
  
  // This method returns a number between 1 and 6 to emulate a dice roll
  public static int rollDice ()
  {
    int number = RANDOM.nextInt ( 6 ) + 1;
    return number;
  }
  
  
  // This method prompts the user for a choice to return, prompting again and providing an 
  // appropriate message is the user does not input an integer or an integer other than 1, 2, or 3
  public static int computeChoice ()
  {
    while ( !CONSOLE.hasNextInt() ) // loops around until an integer is inputed
    {
      CONSOLE.next ();
      System.out.print ( "You did not input an integer!\nEnter your choice:" );
    }    
    int choice = CONSOLE.nextInt ();
    
    if ( choice == 1 || choice == 2 || choice == 3 ) // if the choice is valid, return the choice
    {
      return choice;
    }
    
    // else if another integer is inputed, a message is displayed and the method calls on 
    // itself again to loop and prompt the user again
    System.out.print ( "This is not a valid choice!\nEnter your choice:" );
    choice = computeChoice (); 
    return choice;
  }
  
  
  // This method rewards a Pass bet in case of a Pass Win
  public static void passWin ( int choice )
  {
    if ( choice == 1 ) // if user bet on Pass
    {
      bankroll = bankroll + 5; // original bet + additional 2.5
      System.out.println ( "You win on your Pass bet.\n" );
    }
    else
    {
      System.out.println ( "You loose on your Don't Pass bet.\n" );
    }
  }
  
  
  // This method rewards a Don't Pass bet in case of a Don't Pass Win
  public static void dontPassWin ( int choice )
  {
    if ( choice == 2 ) // if user bet on Don't Pass
    {
      bankroll = bankroll + 5; // original bet + additional 2.5
      System.out.println ( "You win on your Don't Pass bet.\n" );
    }
    else
    {
      System.out.println ( "You loose on your Pass bet.\n" );
    }      
  }
  
  
  // This method sets up the field bets.
  // If the user has enough funds, and is willing to place a field bet, the 
  // boolean fieldBet will be enabled and the bet deduced from the user's bankroll
  public static void makeFieldBet ()
  {
    if ( bankroll >= 2.5 ) // check funds
    {
      System.out.printf ( "Make a Field bet - Balance $%.2f - (y/n)?", bankroll ); // is the user willing?
      String fieldBetInput = CONSOLE.next ();
      if ( fieldBetInput.equalsIgnoreCase ( "y" ) ) // if input is y or Y
      {
        fieldBet = true; // field bet is enabled
        bankroll = bankroll - 2.5; // bet is taken from bankroll
      }
    }
  }
  
  
  // This method informs the user on the field bet result and rewards the 
  // user if the field bet was successful
  public static void computeFieldBet ( int currentRoll )
  {
    if ( fieldBet ) // if fieldBet was enabled
    {
      if ( currentRoll == 2 || currentRoll == 12 )
      {
        System.out.println ( "Field bets WIN double." );
        bankroll = bankroll + 7.5; // original bet + 2x 2.5
      }
      else if ( currentRoll == 3 || currentRoll == 4 || currentRoll == 9 || currentRoll == 10 || currentRoll == 11 )
      {
        System.out.println ( "Field bets WIN even money." );
        bankroll = bankroll + 5; // original bet + 2.5
      }
      else
      {
        System.out.println ( "Field bets LOOSE." );
      }
      fieldBet = false; // disables fieldBet for future rolls
    }
  }
}