package es.ua.dlsi.prog3.p4.model;

import java.util.ArrayList;

/**
 * This class represents a Canvas.
 * It implements some methods to be able to manage Canvas and get/change its particular attributes.
 * One of its attributes is an arraylist of Shapes2D.
 * @author 
 */
public class Canvas {
	/**
	 * Class attribute.
	 * It is a static attribute (that is, every single instance of this class will have exactly the same value for it) that defines
	 * the default size of a new canvas.
	 */
	public static final float DEFAULT_SIZE = 1000;
	
	/**
	 * Instance attribute.
	 * It stores a title for the canvas.
	 */
	private String title;
	
	/**
	 * Instance attribute.
	 * It stores a width for the canvas.
	 */
	private double width;
	
	/**
	 * Instance attribute.
	 * It stores a height for the canvas.
	 */
	private double height;
	
	/**
	 * Instance attribute.
	 * It stores a list of the shapes for the canvas.
	 */
	private ArrayList<Shape2D> shapes;
	
	/**
	 * Default constructor.
	 * It initializes the attributes to its default values and creates a new empty shape arraylist.
	 */
	public Canvas() {
		title = "default canvas";
		width = DEFAULT_SIZE;
		height = DEFAULT_SIZE;
		shapes = new ArrayList<Shape2D>();
	}
	
	/**
	 * Copy constructor.
	 * It initializes the attributes to the values of the attributes of the canvas passed as parameter, and creates a new empty 
	 * shape arraylist.
	 * @param c The canvas that we want to copy.
	 */
	public Canvas(Canvas c) {
		title = c.title;
		width = c.getWidth();
		height = c.getHeight();
		shapes = new ArrayList<Shape2D>();
	}
	
	/**
	 * Constructor with parameters.
	 * It checks if the parameters are negative (in that case it throws an exception). If everything is correct, it initializes 
	 * the attributes to the values received as parameters and creates a new empty shape arraylist.
	 * @param s Title.
	 * @param d1 Width.
	 * @param d2 Height.
	 */
	public Canvas(String s, double d1, double d2) {
		if(d1 < 0 || d2 < 0)
			throw new IllegalArgumentException("Invalid parameters!");
		title = s;
		width = d1;
		height = d2;
		shapes = new ArrayList<Shape2D>();
	}
	
	/**
	 * Instance method.
	 * Its objective is to add to the shape arraylist a new Shape2D, which is being received as parameter.
	 * This can be done directly without having to call any other method.
	 * @param shape The shape we want to add to the arraylist.
	 */
	public void addShape(Shape2D shape) {
		this.shapes.add(shape);
	}
	
	/**
	 * Instance method.
	 * This method's objective is to return a copy of the current instance. 
	 * For that, it calls its default constructor.
	 * @return A copy of the instance.
	 */
	public Canvas clone() {
		return new Canvas(this);
	}
	
	/**
	 * Instance method.
	 * Its objective is to get the shape stored in the position of the arraylist passed as parameter.
	 * If first has to check if the parameter's value is valid for the arraylist (otherwise it throws an exception) and then
	 * uses the get(int) function of the corresponding class to receive it.
	 * @param shape The position of the shape we want in the arraylist.
	 * @return The shape indicated by the parameter.
	 */
	public Shape2D getShape(int shape) {
		if(shape < 1 || shape > getNumShapes())
			throw new IndexOutOfBoundsException("INVALID INDEX!");
		return shapes.get(shape - 1);
	}

	/**
	 * Instance method.
	 * This method's objective is to return the width attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The width of the instance.
	 */
	public double getWidth() {
		return width;
	}

	/**
	 * Instance method.
	 * This method's objective is to return the height attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The width of the instance.
	 */
	public double getHeight() {
		return height;
	}
	
	/**
	 * Instance method.
	 * This method's objective is to return the number of shapes of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The width of the instance.
	 */
	public int getNumShapes() {
		return shapes.size();
	}
	
	/**
	 * Instance method.
	 * Its objective is to remove the shape stored in the position of the arraylist passed as parameter.
	 * If first has to check if the parameter's value is valid for the arraylist (otherwise it throws an exception) and then
	 * removes the shape, which can be done directly without calling any other method.
	 * @param shape The shape that we want to remove.
	 */
	public void removeShape(int shape) {
		if(shape < 1 || shape > getNumShapes())
			throw new IndexOutOfBoundsException("INVALID INDEX!");
		shapes.remove(shape - 1);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return title + " (" + width + "," + height + ") with " + shapes.size() + " shapes";
	}
}