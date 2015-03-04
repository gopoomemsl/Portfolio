import java.util.*;
import java.io.*;
import length.*;

/**
 * This program takes a input file containing a list of lengths in meters, inches, feet, and yards 
 * and prints them out in a formatted manner.
 * <br>
 * It also calculates and prints the min value, max value, and 2 different sums (starting from the 
 * first or last value) of the values in the input file.
 * @author Paul Szyller
 */
public class Lab4 
{	
	/**
	 * Name of the input file as a String.
	 */
	public static final String INPUT_FILE = "data.txt";
	
	/**
	 * This program's main method sets up a scanner and several lists of Length objects to handle all 
	 * of the values from the input file and the values we are trying to calculate.
	 * <br>
	 * Then, other methods are called to set up the scanner, populate those lists, and print all of 
	 * the desired values. 
	 * @param args
	 */
	public static void main(String[] args) 
	{
		/*---Variables---*/
		Scanner input = setInput();
		ArrayList<Length> listOfLength = new ArrayList<Length>();
		ArrayList<Length> minMaxList = new ArrayList<Length>();
		ArrayList<Length> sumListF2L = new ArrayList<Length>();
		ArrayList<Length> sumListL2F = new ArrayList<Length>();
		/*---------------*/
		
		populateListFromInput(input, listOfLength);
		getMinMaxSum(listOfLength, sumListF2L, sumListL2F, minMaxList);
		printList(listOfLength, sumListF2L, sumListL2F, minMaxList);	
		input.close();
	}
	
	/**
	 * This method simply opens the input file in a Scanner object and returns said Scanner.
	 * @return input Scanner: the Scanner object containing the input file.
	 */
	public static Scanner setInput()
	{
		Scanner input = null;
		try 
		{
			return input = new Scanner(new File(INPUT_FILE));
		} 
		catch (FileNotFoundException exception) 
		{
		    throw new RuntimeException("failed to open " + INPUT_FILE);
		}
	}
	
	/**
	 * This method reads through the values in the input file, create a Length object of appropriate 
	 * unit, and stores it in a list. 
	 * <br>
	 * Although the return type is void, this method store its results in the param listOfLength.
	 * @param input Scanner: the Scanner object containing the input file.
	 * @param listOfLength ArrayList<Length>: the list to store the Length objects created.
	 */
	public static void populateListFromInput(Scanner input, ArrayList<Length> listOfLength)
	{
		while (input.hasNextDouble()) //goes through all the values
		{
		    double value = input.nextDouble(); //store doubles as values
		    String unit = input.next(); //and strings as units
		    Length length = null;
		    
		    //make the Length object into an appropriate unit object
		    if (unit.equalsIgnoreCase("meter") || unit.equalsIgnoreCase("meters")) 
		    {
		    	length = new Meter(value);
		    }
		    else if (unit.equalsIgnoreCase("inch") || unit.equalsIgnoreCase("inches"))
		    {
		    	length = new Inch(value);
		    }
		    else if (unit.equalsIgnoreCase("foot") || unit.equalsIgnoreCase("feet")) 
		    {
		    	length = new Foot(value);
		    }
		    else if (unit.equalsIgnoreCase("yard") || unit.equalsIgnoreCase("yards"))
		    {
		    	length = new Yard(value);
		    }
		    
		    listOfLength.add(length); //add the new Length object to our list
		}
	}
	
	/**
	 * This method calculates the min, mac, and 2 different sums (adding values from first to last 
	 * and from last to first) from the values in a list of Length objects and store the results in 
	 * different ArrayList objects.
	 * <br>
	 * Although the return type is void, this method store its results in the different param.
	 * @param listOfLength ArrayList<Length>: contains the input Length values.
	 * @param sumListF2L ArrayList<Length>: will contain the first sum.
	 * @param sumListL2F ArrayList<Length>: will contain the second sum.
	 * @param minMaxList ArrayList<Length>: will contain the min and max.
	 */
	public static void getMinMaxSum(ArrayList<Length> listOfLength, ArrayList<Length> sumListF2L, 
			ArrayList<Length> sumListL2F, ArrayList<Length> minMaxList)
	{
		Length min = listOfLength.get(0); //start the min value at the first value in the list
		Length max = new Meter(0);
		Meter sumMeter = new Meter(0);
		Inch sumInch = new Inch(0);
		Foot sumFoot = new Foot(0);
		Yard sumYard = new Yard(0);
		
		for(Length l: listOfLength)
		{
			if (l.compareTo(min) == -1) //if the value of l is smaller than the current min
			{
				min = l; //replace the min by l
			}
			
			if (l.compareTo(max) == 1) //if the value of l is larger than the current max
			{
				max = l; //replace the max by l
			}
			
			//add each values in the sums for each units
			sumMeter.add(l);
			sumInch.add(l);
			sumFoot.add(l);
			sumYard.add(l);
		}
		
		//add each new-found values to the appropriate lists
		minMaxList.add(min);
		minMaxList.add(max);
		sumListF2L.add(sumMeter);
		sumListF2L.add(sumInch);
		sumListF2L.add(sumFoot);
		sumListF2L.add(sumYard);
		
		/*---Sum calculated from last to first value---*/
		//put the sums for each units back to 0
		sumMeter = new Meter(0);
		sumInch = new Inch(0);
		sumFoot = new Foot(0);
		sumYard = new Yard(0);
		
		ArrayList<Length> revListOfLength = new ArrayList<Length>(); //create a new list
		revListOfLength.addAll(listOfLength); //copy the existing list of values in the new list
		Collections.reverse(revListOfLength); //reverse the order of the values in the new list
		
		for(Length l: revListOfLength)
		{
			//add each values in the sums for each units
			sumMeter.add(l);
			sumInch.add(l);
			sumFoot.add(l);
			sumYard.add(l);
		}
		
		//add the new-found values to the Last2First list
		sumListL2F.add(sumMeter);
		sumListL2F.add(sumInch);
		sumListL2F.add(sumFoot);
		sumListL2F.add(sumYard);
	}
	
	/**
	 * This method prints all of the desired values in a formatted manner
	 * @param listOfLength ArrayList<Length>: contains the input Length values.
	 * @param sumListF2L ArrayList<Length>: contains the first sum.
	 * @param sumListL2F ArrayList<Length>: contains the second sum.
	 * @param minMaxList ArrayList<Length>: contains the min and max.
	 */
	public static void printList(ArrayList<Length> listOfLength, ArrayList<Length> sumListF2L,
			ArrayList<Length> sumListL2F, ArrayList<Length> minMaxList)
	{
		/*---List of Length objects---*/
		for(Length l: listOfLength)
		{
			System.out.println(l);
		}
		
		/*---Min and max---*/
		System.out.printf("\nMinimum is %s",  minMaxList.get(0));
		System.out.printf("\nMaximum is %s\n", minMaxList.get(1));
		
		/*---Sum from first to last---*/
		System.out.printf("\nSum of Lengths Adding from First to Last\n");
		for(Length l: sumListF2L)
		{
			System.out.println(l);
		}
		
		/*---Sum from last to first---*/
		System.out.printf("\nSum of Lengths Adding from Last to First\n");
		for(Length l: sumListL2F)
		{
			System.out.println(l);
		}
	}
}
