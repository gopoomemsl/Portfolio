/**
 * This class will allow us to create a DateRange object.
 * <br>
 * A DateRange object contains a start Date, an end Date, and a compareValue based on the Date.compareTo() between the start and end Date.
 * @author Paul Szyller
 */
public class DateRange 
{
	private Date start; //start of the range
	private Date end; //end of the range
	public int compareValue; //determines the chronology between the start and end of the range
	
	/**
	 * Constructor method for the DateRange object.
	 */
	public DateRange (Date startDate, Date endDate)
	{
		start = startDate;
		end = endDate;
		compareValue = start.compareTo(end);
	}
	
	/**
	 * A toString method for the DateRange object, it returns a String in the form "DateRange: start Date - end Date".
	 */
	public String toString()
	{
		return ("DateRange: " + start.toString() + " - " + end.toString()); //returns a formated String
	}
	
}
