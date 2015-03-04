// Coins.java
// Paul Szyller
// Lab 1

import java.util.*;

public class Coins
  /* This program has 3 functions:
       -it prompts the user for his/her name and use the input in the header
       -it prompts the user for the number of each type of coin the user has, 
        calculates the total value, and prints out that value.
       -it prompts the user for a monetary value to be converted into numbers of quarters, dimes, nickels, and pennies
  */
{
  public static final Scanner CONSOLE = new Scanner( System.in );
  
  public static void main ( String [] args )
    // This is the main method, it is only used here to call the other methods.
  {
    printHeader ();
    calculateTotalValue ();
    calculateNumberOfCoins ();
  }
  
  
  
  public static void printHeader ()
    // This method prompts the user for his/her name, then prints out an appropriate header.
  {
    System.out.print ( "Enter your name." ); 
    String name = CONSOLE.next();
    System.out.println ( "Lab 1 written by " + name );
  }
  
  
  
  public static void calculateTotalValue ()
    // This method prompts the user for the number of each kind of coin that he/she possesses, 
    // calculates the total value those coins add up to, and print out that value.
  {
    System.out.print ( "How many quarters do you have?" );
    int quarters = CONSOLE.nextInt();
    
    System.out.print ( "How many dimes do you have?" );
    int dimes = CONSOLE.nextInt();
    
    System.out.print ( "How many nickels do you have?" );
    int nickels = CONSOLE.nextInt();
    
    System.out.print ( "How many pennies do you have?" );
    int pennies = CONSOLE.nextInt();
    
    int coins = quarters + dimes + nickels + pennies;
    // This is the total number of coins.
    double total = .25 * quarters + .10 * dimes + .05 * nickels + .01 * pennies;
    // This is the total value of all added coins.
    
    System.out.println ( "Number of quarters: " + quarters + 
                        "\nNumber of dimes: " + dimes + 
                        "\nNumber of nickels: " + nickels + 
                        "\nNumber of pennies: " + pennies + 
                        "\nFor a total number of coins of: " + coins + 
                        "\nThe total value of your coins is: $" + total );
   }
  
  
  
  public static void calculateNumberOfCoins ()
    // This method prompts the user for a monetary value, 
    // then determines the amount of each coins needed to ad up to that value, and print out that value.
  {
    System.out.print ( "Enter a monetary value to be converted into coins." + 
                      "\n(decimal number with exactly two decimal places)" );
    double value = CONSOLE.nextDouble();
    
    double cents = value * 100;
    // This is the total amount of cents in the given monetary value.
    int quarters = (int) cents / 25;
    // This is the number of quarters needed to match the given monetary value.
    
    int remainingCoins1 = (int) cents % 25;
    // This is the remaining amount of cents after having calculated the required number of quarters.
    int dimes = remainingCoins1 / 10;
    // This is the number of dimes needed to match the given monetary value.
    
    int remainingCoins2 = remainingCoins1 % 10;
    // This is the remaining amount of cents after having calculated the required number of dimes.
    int nickels = remainingCoins2 / 5;
    // This is the number of nickels needed to match the given monetary value.
    
    int pennies = remainingCoins2 % 5;
    // This is the remaining amount of cents (or pennies) after having calculated the required number of nickels.
    
    System.out.println ( "$" + value + " can be obtain with " + 
                        quarters + " quarter(s), " + 
                        dimes + " dime(s), " + 
                        nickels + " nickel(s), and " + 
                        pennies + " pennie(s)." );
  }
}