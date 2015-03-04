import java.util.*;
import java.io.*;
/**
 * This program goes through a text file, then prints the number of number token in that file,
 * the number of non-number token, and the sum of all the number tokens found previously.
 * @author Paul Szyller 
 */
public class Lab1 
{
	/**
	 * The main method starts the java application.
	 * <br>
	 * The program being small enough, everything is contained in the main method.
	 * @param args
	 */
	public static void main(String[] args) 
	{
		//Scanner setup ____________________________________
		Scanner input = null;
		try
		{
			input = new Scanner (new File("data.txt"));
		}
		catch (Exception FileNotFoundExecption)
		{
			System.err.println ("failed to open data.txt");
			System.exit(1);
		}
		//__________________________________________________
		
		
		//Variables ________________________________________
		int nOfDoubles = 0; //double counter
		int nOfOther = 0; //other token counter
		double sum = 0; //running sum of doubles found
		//__________________________________________________
		
		
		while (input.hasNext()) //goes through the file token by token
		{
			String token = input.next(); //store current token in a string variable
			try
			{
				double d = Double.parseDouble(token); //if current token is a number, makes it into a double
				nOfDoubles++; //increase double counter
				sum += d; //add double found to the running sum
			}
			catch (NumberFormatException e)
			{
				nOfOther++; //if the current token cannot be made into a double, increase the other counter
			}
		}
		
		System.out.printf ("%d %d %.1f", nOfDoubles, nOfOther, sum); //prints out results
		input.close(); //close file
	}

}
