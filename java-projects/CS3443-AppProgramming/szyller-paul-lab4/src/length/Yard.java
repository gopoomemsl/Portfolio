package length;

/**
 * A Yard is a Length object in yard units.
 * @author Paul Szyller
 */
public class Yard extends Length
{
	public static final double METERS_PER_YARD = 0.9144;
	
	public Yard(double length)
	{
		super(length);
	}
	
	public void add(Length other)
	{
		this.setLength(this.getLength() + ((other.toMeters()) / METERS_PER_YARD));
		//original length + new one converted to the class' unit
	}
	
	public String getUnit()
	{
		if (this.getLength() == 1.0)
		{
			return "yard";
		}
		return "yards";
	}
	
	public double toMeters()
	{
		return (this.getLength() * METERS_PER_YARD);
	}
}