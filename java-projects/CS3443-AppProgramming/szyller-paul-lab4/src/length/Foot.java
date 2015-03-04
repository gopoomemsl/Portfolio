package length;

/**
 * A Foot is a Length object in foot units.
 * @author Paul Szyller
 */
public class Foot extends Length
{
	public static final double METERS_PER_FOOT = 0.3048;
	
	public Foot(double length)
	{
		super(length);
	}
	
	public void add(Length other)
	{
		this.setLength(this.getLength() + ((other.toMeters()) / METERS_PER_FOOT));
		//original length + new one converted to the class' unit
	}
	
	public String getUnit()
	{
		if (this.getLength() == 1.0)
		{
			return "foot";
		}
		return "feet";
	}
	
	public double toMeters()
	{
		return (this.getLength() * METERS_PER_FOOT);
	}
}