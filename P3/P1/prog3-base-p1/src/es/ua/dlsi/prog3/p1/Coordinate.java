
package es.ua.dlsi.prog3.p1;

import java.util.Arrays;

/** Coordinate class from practice 1 (Subject: Programming 3)
 * @author 
 */

/** This class is designed to represent a set of numerical components that define a point in a 
 * multi-dimensional space. It uses an array of components to store all the dimensions of each object.
 * To create a new object it is possible to use an array of components or another object, in order to 
 * copy it. In addition, this class allows to get the components or the dimensions of the object,
 * plus it can compare two objects and say if they are equal or not.
 * In order to make this class immutable, it is declared as 'final', all its attributes are private
 * and it doesn't have any setter method, so once you create an object it can't be changed. In addition,
 * it uses defensive copy when an object returns its components.
 */
public final class Coordinate {
	/** Instance attribute.
	 * It is an array that stores the components of the object, that means, each coordinate of the
	 * n-dimensional space point. Its content can be set by a parameter that is passed to the
	 * constructor or by copying other object's.
	 */
	private final double[] components;
	
	/** Constructor.
	 * It receives an array of coordinates for the point, and creates a new object storing that array
	 * in the attribute 'components' of the object. For that, it first checks the array passed as a 
	 * parameter to determine if it is null or has length 0. In both cases, that means there is no 
	 * content in the array, so it creates a 0-dimensional coordinate. Otherwise, it copies the array's
	 * content.
	 * @param components array with the components of the object that is going to be created.
	 */
	public Coordinate(double[] components) {
    	if (components == null || components.length == 0)
    	    this.components = new double[0];
    	else
    	    this.components = Arrays.copyOf(components, components.length);
    }

    /** Copy constructor.
     * It receives an object of the same class (Coordinate) as a parameter and creates a new one with 
     * the same components, that is, it copies the object passed as parameter in a new one. It uses
     * defensive copy since it uses a copy of the array of the object passed as parameter.
     * @param c object that is going to be copied.
     */
    public Coordinate(Coordinate c) {
        this.components = Arrays.copyOf(c.components, c.components.length);
    }

    /** Instance method.
     * Its objective is to return the components of the object, but in order to protect that object
     * it uses defensive copy, that is, it returns a copy of the component array and not directly the
     * array itself.
     * @return it returns a copy of the components array.
     */
    public double[] getComponents() {
    	return Arrays.copyOf(this.components, this.components.length);
    }

    /** Instance method.
     * Its objective is to return the number of dimensions, that is, the length of the components 
     * array of the object. In this case, since it is returning just the length of the array, it is
     * not necessary to copy anything because values are not going to be modified.
	 * @return the number of dimensions.
     */
    public int getDimensions() {
        return components.length;
    }

    /** Instance method.
     * This method returns a hash code value for the object, which is kind of an identifier for 
     * each object. It computes the hash code based on the contents of the 'components' array. 
     * The 'prime' multiplier ensures that objects with different content have different hash codes.
     * @return it returns an integer representing the hash code of the object.
     */
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + Arrays.hashCode(components);
		return result;
	}

    /** Instance method.
     * This method checks whether the current object is equal or not to another object of the same class.
     * It first checks if the passed object is null or if it belongs to a different class,
     * returning false in these cases since, obviously, that would mean it is not equal to ours. 
     * Then it compares the reference of the current object with the reference of the passed object, 
     * returning true if they are the same, because that would mean the passed object is a reference
     * to ours. 
     * Finally, it checks if both objects have the same 'components' array, returning
     * true in case both arrays are the same, or false otherwise.
     * @param obj the object to compare with the current one.
     * @return true if the objects are equal, false otherwise.
     */
	public boolean equals(Object obj) {
		if (obj == null || getClass() != obj.getClass())
			return false;
		if (this == obj)
			return true;
		Coordinate other = (Coordinate) obj;
		return Arrays.equals(components, other.components);
	}
}