package length;

/**
 * A Inch is a Length object in inch units.
 * @author Paul Szyller
 */
public class Inch extends Length
{
	public static final double METERS_PER_INCH = 0.0254;
	
	public Inch(double length)
	{
		super(length);
	}
	
	public void add(Length other)
	{
		this.setLength(this.getLength() + ((other.toMeters()) / METERS_PER_INCH));
		//original length + new one converted to the class' unit
	}
	
	public String getUnit()
	{
		if (this.getLength() == 1.0)
		{
			return "inch";
		}
		return "inches";
	}
	
	public double toMeters()
	{
		return (this.getLength() * METERS_PER_INCH);
	}
}