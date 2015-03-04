// Combination.java
// Paul Szyller
// Lab 2

import java.util.*;

public class Combination
  // This program calculates the Binomial Coefficient and the number of Permutations for two inputed numbers
{
  public static final Scanner CONSOLE = new Scanner ( System.in );
  
  public static void main ( String [] args )
    // This is the main method, here it is only used to call other methods
  {
    printHeader ();
    printCalculations ();    
  }
  
  public static void printHeader ()
    // This method very simply prints the header of the lab
  {
    System.out.println ( "Lab 2 written by Paul Szyller" );
  }
  
  public static void printCalculations ()
    // This method prompts the user for the two numbers used through the lab
    // This method then prints out the calculations returned from the other methods
  {    
    System.out.println ( "Enter a value for n:" + 
                        "\n( This has to be a positive integer )" );
    int n = CONSOLE.nextInt ();
    
    System.out.println ( "Enter a value for k:" + 
                        "\n( This has to be a positive integer )" );
    int k = CONSOLE.nextInt ();
    
    double nCk = calculateBinomialCoeff ( n, k );
    System.out.println ( n + "C" + k + " is: " + nCk );
    
    double nPk = calculatePermutations ( n, k );
    System.out.println ( n + "P" + k + " is: " + nPk );
  }
  
  public static int calculateFactorial ( int number )
    // This method calculates the factorial of a given number ( number! )
  {
    int factorial = 1;
    for ( int i = number; i > 0; i = i - 1)
    {
      factorial = factorial * i;
    }
    return factorial;
  }
  
  public static double calculateBinomialCoeff ( int n, int k )
    // This method calculates the binomial coefficient for numbers n and k
  {    
    int fn = calculateFactorial ( n );
    // n!
    int fk = calculateFactorial ( k );
    // k!
    
    int part1 = n - k;
    int part2 = calculateFactorial ( part1 );
    // (n - k)!
    double denom = fk * part2;
    // k! * (n - k)!
    
    double nCk = fn / denom;
    // n! / ( k! * (n - k)! )
    return nCk;
  }
  
  public static double calculatePermutations ( int n, int k )
    // This method calculates the number of permutations for numbers n and k
  {    
    int fn = calculateFactorial ( n );
    // n!
    
    int part1 = n - k;
    int part2 = calculateFactorial ( part1 );
    // (n - k)!
    
    double nPk = fn / part2;
    // n! / (n - k)!
    return nPk;    
  }
}