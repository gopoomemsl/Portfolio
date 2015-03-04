// CurrencyTables.java
// Paul Szyller
// Project 0

import java.util.*;
   
public class CurrencyTables
  // This program prints out a currency conversion table from dollars to six different currencies.
  // The starting value, ending value, and increment for each row of the table are all inputed by the user.
{
  public static final Scanner CONSOLE = new Scanner ( System.in );
  
  // Convertion values:
  public static final double EUR_VALUE = 0.735345;
  // Euro
  public static final double HKD_VALUE = 7.75145;
  // Hong Kong Dollar
  public static final double QAR_VALUE = 3.64070;
  // Qatari Riyal
  public static final double BRL_VALUE = 2.23075;
  // Brazilian Real
  public static final double JMD_VALUE = 111.328;
  // Jamaican Dollar
  public static final double ILS_VALUE = 3.45000;
  // Israeli Shekel
  
  public static void main ( String []  args )
    // This is the main method, it does 3 things:
    //     -prints out the header for the lab
    //     -prompts the user for a start, end, and increment value
    //     -prints a currency conversion table base on the given start, end, and increment values
  {
    System.out.println ( "Project 0 written by PAUL SZYLLER" );
    
    System.out.println ( "Enter start value:" + 
                        "\n(This has to be a positive integer)" );
    int start = CONSOLE.nextInt ();
    
    System.out.println ( "Enter end value:" + 
                        "\n(This has to be a positive integer" + 
                        " greater than the start value)" );
    int end = CONSOLE.nextInt ();
    
    System.out.println ( "Enter increment:" + 
                        "\n(This has to be a positive integer)" );
    int inc = CONSOLE.nextInt ();
    
    printTable ( start, end, inc );
  }
  
  public static void printTable ( int start, int end, int inc )
    // This method prints out the currency conversion table
  {
    // Table title:
    System.out.println ( "Currency conversions for US Dollars" );
    // Column header: 
    System.out.println ( "USD\tEUR\tHKD\tQAR\tBRL\tJMD\tILS" );
    
    for ( int i = start; i <= end; i = i + inc )
    {
      double eur = convertToEur ( i );
      double hkd = convertToHkd ( i );
      double qar = convertToQar ( i );
      double brl = convertToBrl ( i );
      double jmd = convertToJmd ( i );
      double ils = convertToIls ( i );
      // Here we call all the conversion methods
      
      System.out.println ( i + "\t" + 
                          ( int ) eur + "\t" + 
                          ( int ) hkd + "\t" + 
                          ( int ) qar + "\t" + 
                          ( int ) brl + "\t" + 
                          ( int ) jmd + "\t" + 
                          ( int ) ils );
      // This is the main part of the table
    }
  }
  
  public static double convertToEur ( int dollar )
    // This method calculates the conversion to Euros using the class constant EURVALUE and a parameter "dollar",
    // the converted value is then returned to the table method where it is called
  {
    double eur = dollar * EUR_VALUE;
    return eur;
  }
  
  public static double convertToHkd ( int dollar )
    // This method does the same as the last one but for Hong Kong Dollars
  {
    double hkd = dollar * HKD_VALUE;
    return hkd;
  }
  
  public static double convertToQar ( int dollar )
    // This method does the same as the last one but for Qatari Riyals
  {
    double qar = dollar * QAR_VALUE;
    return qar;
  }
  
  public static double convertToBrl ( int dollar )
    // This method does the same as the last one but for Brazilian Reals
  {
    double brl = dollar * BRL_VALUE;
    return brl;
  }
  
  public static double convertToJmd ( int dollar )
    // This method does the same as the last one but for Jamaican Dollars
  {
    double jmd = dollar * JMD_VALUE;
    return jmd;
  }
  
  public static double convertToIls ( int dollar )
    // This method does the same as the last one but for Israeli Shekels
  {
    double ils = dollar * ILS_VALUE;
    return ils;
  }
}