import java.util.*;

/**
 * A DualHashMap is a HashMap implementation of the DualMap class.
 * It maintains two HashMap variables and implements the functions put, 
 * remove, get, and reverseGet.
 * 
 * @author Paul Szyller
 */
public class DualHashMap<K, V> implements DualMap<K, V>
{
	private HashMap<K, V> map1;
	private HashMap<V, K> map2;
	
	/**
	 * The DualHashMap constructor creates two new HashMap variables.
	 */
	public DualHashMap()
	{
		map1 = new HashMap<K, V>();
		map2 = new HashMap<V, K>();
	}
	
	/**
	 * Inserts a key and corresponding value into the DualHashMap, 
	 * if either the key, the value, or both is already contained 
	 * in the DualHashMap, the old association(s) will be removed.
	 */
	public void put(K key, V value)
	{
		if (map1.containsKey(key) || map2.containsKey(value))
		{
			this.remove(key, value);
		}
		map1.put(key, value);
		map2.put(value, key);
	}
	
	/**
	 * This method removes the mapping(s) for the desired key and value.
	 */
	public void remove(K key, V value)
	{
		map2.remove(map1.get(key));
		map1.remove(key);
		
		//if key and value are not mapped together
		if (map2.containsKey(value))
		{
			map1.remove(map2.get(value));
			map2.remove(value);
		}		
	}
	
	/**
	 * Returns the value associated with the desired key.
	 */
	public V get(K key)
	{
		return map1.get(key);
	}
	
	/**
	 * Returns the key associated with the desired value.
	 */
	public K reverseGet(V value)
	{
		return map2.get(value);
	}
}
