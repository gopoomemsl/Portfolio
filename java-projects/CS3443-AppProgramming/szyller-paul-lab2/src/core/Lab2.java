package core;
import java.util.*;
import java.io.*;
/**
 * This program goes through a text file representing a list of students and their grades, store the data
 * in an array of Grades objects, calculates for each student avg, median, max grade, and min grade, and 
 * prints out all of those data in a formated way.
 * @author Paul Szyller
 */
public class Lab2 
{
	/**
	 * The main method starts the java application.
	 * <br>
	 * This method sets up a new Scanner, scans every data in the file "data.txt", and stores everything in
	 * a Grades array.
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
		
		//Variables_________________________________________
		Grades[] students = new Grades[2]; //array with a Grades object for each student
		int numOfStudents = 0; //number of students added to the array
		//__________________________________________________
		
		while (input.hasNext()) //goes through the file
		{
			String name = input.next(); //first token of a student's block of lines in data.txt is going to be his/her name
			students = addStudent(students, name, numOfStudents++); //create a new Grades object for student "name" in the students array and updates the number of students
					
			while (input.hasNextInt()) //goes through the grades of each students
			{
				int grade = input.nextInt();
				students[numOfStudents - 1].insertGrade(grade); //insert each grades in the grades array contained in each Grades object
			}
		}
		
		printGrades(students, numOfStudents); //prints everything in a formated way
		input.close(); //close the file after usage
	}
	
	/**
	 * This method creates a new Grades object for student "name" in the students array.
	 * @param students Array of Grades objects.
	 * @param name Name of the student to create a Grades object for.
	 * @param numOfStudents Current number of students in the students array.
	 * @return The updated students array.
	 */
	public static Grades[] addStudent(Grades[] students, String name, int numOfStudents)
	{
		//resize________________________________________________________
		if (numOfStudents >= students.length) //If the array is full
		{
			Grades[] newArray = new Grades[students.length*2]; //Create a new array twice the size of existing one
			
			for (int i = 0; i < students.length; i++)
			{
				newArray[i] = students[i]; //Copy each value from old array to new
			}
			
			students = newArray; //Replaces old array with new one
		}
		//_______________________________________________________________
		
		students[numOfStudents] = new Grades(name); //Calls the constructor to insert a new Grades object in the array for student "name"
		return students;
	}
	
	/**
	 * Method from the lab2 rubric, prints out a student's data.
	 * @param grades The Grades object corresponding to the student whose data are being printed.
	 */
	public static void testGrades(Grades grades) 
	{
	    System.out.println(grades.toString()); 
	    System.out.printf("\tName:    %s\n", grades.getName());
	    System.out.printf("\tLength:  %d\n", grades.length());
	    System.out.printf("\tAverage: %.2f\n", grades.average());
	    System.out.printf("\tMedian:  %.1f\n", grades.median());
	    System.out.printf("\tMaximum: %d\n", grades.maximum());
	    System.out.printf("\tMininum: %d\n", grades.minimum());
	}
	
	/**
	 * Method to print the final formated list of students and their data.
	 * @param students Array of Grades object.
	 * @param numberOfStudents Current number of students.
	 */
	public static void printGrades(Grades[] students, int numberOfStudents)
	{
		for (int i = 0; i < numberOfStudents; i++) //goes through the students array
		{
			testGrades(students[i]); //prints data for each student using the formated method from the rubric
		}			
	}
}
