
import java.awt.*;
import java.util.ArrayList;

/**
 * The DemoModel class holds the information that is used by the GUI.
 * Ask yourself the question, what data would be needed to recreate
 * the state of the GUI?  This data is what should be stored in the
 * model.
 * <p>
 * The instance variables are from Fig. 14.34.
 * <br>
 * This is modified by Paul Szyller to add color functionality to 
 * the drawing area in accordance to lab 5 of CS3443.
 * @author Tom Bylander
 * @author Paul Szyller
 */
public class DemoModel {
    /** 
     * The number of points 
     */
	private int pointCount;

	/** 
	 * An ArrayList of all the points drawn
	 * <br>
	 * Changed from an array to an ArrayList to avoid out of bound errors
	 */
	private ArrayList<Point> points;
	
	/** 
	 * The color selected by the user 
	 */
	private Color selectedColor;
	
	/**
	 * An ArrayList containing the color of each point drawn
	 * <br>
	 * The color at any index correspond to the point at the same index
	 */
	private ArrayList<Color> colors;
	
	/**
	 * The constructor has been changed to initialize the new ArrayList objects
	 */
	public DemoModel() {
		pointCount = 0;
		points = new ArrayList<Point>();
		selectedColor = Color.CYAN;
		colors = new ArrayList<Color>();
	}
	
	/**
	 * Add a Point to the points ArrayList and the current selected color to the 
	 * corresponding index in the color ArrayList.
	 * @param point the Point to be added to points.
	 */
	public void addPoint(Point point) {
		points.add(point);
		pointCount++;
		colors.add(selectedColor);
	}
	
	/**
	 * Returns point at index i.
	 * Returns null if no such point exists.
	 * <br>
	 * Changed to use an ArrayList instead of an array of Points.
	 * @param i
	 */
	public Point getPoint(int i) {
		if (i >= 0 && i < pointCount) {
			Point returnPoint = points.get(i);
			return returnPoint;
		}
		return null;
	}
	
	/**
	 * Returns color at index i.
	 * Returns null if no such color exists.
	 * @param i
	 */
	public Color getColor(int i) {
		if (i >= 0 && i < pointCount) {
			Color returnColor = colors.get(i);
			return returnColor;
		}
		return null;
	}
	
	/**
	 * Store the color that the user selected.
	 * @param color the color selected by the user
	 */
	public void setSelectedColor(Color color) {
		selectedColor = color;
	}
	
	/**
	 * @return the color selected by the user
	 */
	public Color getSelectedColor() {
		return selectedColor;
	}
}
