import java.io.*;
import java.util.*;

/**
 * This program goes through a text file containing a list of dates formated in different ways.
 * <br>
 * It then prints out each date in a formated way, and prints out a date range if the second date is later than the first one.
 * @author Paul Szyller
 */
public class Lab3 
{
	/**
	 * The main method starts the Java application.
	 * <br>
	 * It creates a Scanner object for the file "dates.txt", goes through the file and puts each line in a Date object.
	 * <br>
	 * It then prints the Date object and the DateRange object if the current Date is later than the previous one.
	 * @param args
	 */
	public static void main(String[] args) 
	{
		//Scanner setup ____________________________________
		Scanner input = null;
		try
		{
			input = new Scanner (new File("dates.txt"));
		}
		catch (Exception FileNotFoundExecption)
		{
			System.err.println ("failed to open dates.txt");
			System.exit(1);
		}
		//__________________________________________________
				
		//Variables ________________________________________
		String line; //a variable to store each line scanned from the dates.txt document
		Date date; //a Date object to send the data from String line in
		Date prevDate = null;
		//__________________________________________________
		
		while (input.hasNextLine()) //goes through the file
		{
			line = input.nextLine(); //stores each line in a String
			date = new Date(line); //creates a Date object with the info from the String line
			System.out.println(date); //prints the Date object
			
			if (!(date.toString().equals("Invalid Date"))) //if the last date isn't invalid
			{
				if (prevDate != null) //if it isn't the first date
				{
					DateRange dateRange = new DateRange(prevDate, date); //create a DateRange object with the new date and the previous one
					if (dateRange.compareValue < 0) //if the new one is later than the previous one
					{
						System.out.println(dateRange); //print dateRange
					}
				}
				prevDate = date; //set the current date to be the previous date in the next loop
			}
		}
		
		input.close(); //close the file after usage
	}
}
