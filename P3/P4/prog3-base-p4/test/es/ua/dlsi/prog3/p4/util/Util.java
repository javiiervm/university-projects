package es.ua.dlsi.prog3.p4.util;

import static org.junit.Assert.fail;

import java.lang.reflect.Field;

public class Util {

	/**
	 * This method uses reflection to access to a private attribute of an object
	 * 
	 * @param o object to whose attributes we want to access
	 * @param attr name of the attribute whose value is to be accessed
	 * @return the value of the attribute
	 * @throws Exception 
	 */
	public static Object getAttributeValue(Object o, String attr) throws Exception  {
		Class<?> clazz = o.getClass();
		while (clazz != null)
		try {
			Field f = clazz.getDeclaredField(attr);
			f.setAccessible(true);
			return f.get(o);
		} catch (IllegalArgumentException | IllegalAccessException | NoSuchFieldException | SecurityException e) {
			if (e instanceof NoSuchFieldException) 
				clazz = clazz.getSuperclass();
			else // no way...
				throw new Exception("Can't get attribute value", e);
		}
		// not found...
		throw new Exception("Can't find attribute "+attr);
	}
	
	public static boolean compareStrings(String a, String b) {
		String aa = a.toLowerCase().replaceAll("\\s+", "").replace('s', 'z');
		String bb = b.toLowerCase().replaceAll("\\s+", "").replace('s', 'z');
		
		return aa.equals(bb);
	}
	
	public static boolean containsString(String str, String substr) {
		String str2 = str.toLowerCase().replaceAll("\\s+", "").replace('s', 'z');
		String substr2 = substr.toLowerCase().replaceAll("\\s+", "").replace('s', 'z');
		
		return str2.contains(substr2);
	}
}
