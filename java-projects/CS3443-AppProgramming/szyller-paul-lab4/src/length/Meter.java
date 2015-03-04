package length;

/**
 * A Meter is a Length object in meter units.
 * @author Paul Szyller
 */
public class Meter extends Length
{
	public Meter(double length)
	{
		super(length);
	}
	
	public void add(Length other)
	{
		this.setLength(this.getLength() + (other.toMeters()));
		//original length + new one converted to the class' unit
	}
	
	public String getUnit()
	{
		if (this.getLength() == 1.0)
		{
			return "meter";
		}
		return "meters";
	}
	
	public double toMeters()
	{
		return this.getLength();
	}
}
