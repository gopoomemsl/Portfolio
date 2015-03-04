import java.util.*;
/**
 * This class will allow us to create a Date object.
 * <br>
 * A Date object contains a day, a month (both in Integer form and in String form), and a year.
 * @author Paul Szyller
 */
public class Date implements Comparable<Date> 
{
	private Integer day;
	private Integer month; //month number
	private String monthString; //month String
	private Integer year;
	
	/**
	 * Constructor method for the Date object.
	 * <br>
	 * It takes a String representing a date, finds the day, month, and year, and stores them in the object's variables.
	 * @param line A String sent from the scanner in the main class representing a date.
	 */
	public Date (String line)
	{
		Scanner tokens = new Scanner(line); //create a Scanner to go through the line String
		String temp; //creates a temp String
		temp = tokens.next(); //stores the first token from the String line in the temp String
		setMonth(temp); //set the month and monthString variables according to the temp token
		
		temp = tokens.next(); //stores the next token in temp
		temp = temp.substring(0, (temp.length() - 1)); //removes the last character from the token (",")
		day = Integer.parseInt(temp); //changes the temp token in an int and stores it in the day variable
		year = tokens.nextInt(); //store the last token in the year variable
		
		tokens.close();	//closes the Scanner after usage
	}
	
	/**
	 * This method takes a monthToken which can be written in many forms and converts it to a formated String for the name of the month,
	 * it also adds the month number to the month variable.
	 * @param monthToken A String token representing a month, it can be written different ways.
	 */
	private void setMonth(String monthToken)
	{
		if (monthToken.substring(0, 3).toLowerCase().compareTo("jan") == 0) //if the 3 first letters match the begining of a month
		{
			month = 1; //change the month variable to the month's number
			monthString = "January"; //change the monthString variable to a formated name of the month
		}		
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("feb") == 0)
		{
			month = 2;
			monthString = "February";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("mar") == 0)
		{
			month = 3;
			monthString = "March";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("apr") == 0)
		{
			month = 4;
			monthString = "April";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("may") == 0)
		{
			month = 5;
			monthString = "May";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("jun") == 0)
		{
			month = 6;
			monthString = "June";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("jul") == 0)
		{
			month = 7;
			monthString = "July";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("aug") == 0)
		{
			month = 8;
			monthString = "August";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("sep") == 0)
		{
			month = 9;
			monthString = "September";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("oct") == 0)
		{
			month = 10;
			monthString = "October";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("nov") == 0)
		{
			month = 11;
			monthString = "November";
		}
		else if (monthToken.substring(0, 3).toLowerCase().compareTo("dec") == 0)
		{
			month = 12;
			monthString = "December";
		}
	}
	
	/**
	 * A compareTo method for the Date class, it compares Date objects based on the chronology of dates (year, then month, then day).
	 */
	@Override
	public int compareTo(Date other)
	{
		if (this.year.compareTo(other.year) != 0) //if the years aren't the same
		{
			return this.year.compareTo(other.year); //uses the dates' year to compare
		}
		
		if (this.month.compareTo(other.month) != 0) //if the months aren't the same
		{
			return this.month.compareTo(other.month); //uses the dates' month to compare
		}
		
		return this.day.compareTo(other.day); //uses the dates' day to compare
	}
	
	/**
	 * A toString method for the Date class, it returns a String in the form "Date: month day, year".
	 */
	public String toString()
	{
		if (day > 31 || ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) || (month == 2 && day > 28))
		//if the day doesn't exist in the calendar
		{
			return ("Invalid Date");
		}
		return ("Date: " + monthString + " " + day +", " + year); //returns a formated String representing the Date
	}
}
