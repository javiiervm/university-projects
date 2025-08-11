package es.ua.dlsi.prog3.p4.model;

/**
 * This class represents a Shape2DFactory.
 * It implements a methods to be able to create a Shape2D.
 * @author 
 */
public class Shape2DFactory {
	/**
	 * Instance method.
	 * It receives a string as a parameter, it uses the startsWith() string method to check if that string starts with
	 * "Circle", "Rectangle" or "Square", and if so, it calls the corresponding default constructor and returns the created
	 * Shape2D, otherwise it throws an exception.
	 * @param s The string which contains the name of the figure.
	 * @return The figure created.
	 */
	public static Shape2D createShape2D(String s) {
		Shape2D shape = null;
		if(s.startsWith("Circle"))
			shape = new Circle();
		else if (s.startsWith("Rectangle"))
			shape = new Rectangle();
		else if (s.startsWith("Square"))
			shape = new Square();
		else
			throw new IllegalArgumentException("INVALID FIGURE TYPE!"); 
		return shape;
	}
}