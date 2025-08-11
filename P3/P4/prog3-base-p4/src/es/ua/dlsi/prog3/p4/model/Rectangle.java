package es.ua.dlsi.prog3.p4.model;

/**
 * This class represents a Rectangle.
 * It is an AbstractPolygon, so it inherits all the attributes and methods from its superclass.
 * It implements some methods to be able to manage Rectangle and get/change its particular attributes.
 * @author 
 */
public class Rectangle extends AbstractPolygon {
	/**
	 * Instance attribute.
	 * It stores a length for the rectangle.
	 */
	private double length;
	
	/**
	 * Instance attribute.
	 * It stores a width for the rectangle.
	 */
	private double width;
	
	/**
	 * Default constructor.
	 * It calls the superclass' constructor and then initializes the attributes to zero.
	 */
	public Rectangle() {
		super();
		this.length = 0;
		this.width = 0;
	}
	
	/**
	 * Constructor with parameters.
	 * It calls the superclass' constructor sending it a coordinate and rotation angle as parameters and then checks if the rest of
	 * parameters are negative (in that case it throws an exception). If everything is correct, it initializes the attributes to the 
	 * values received as parameters.
	 * @param coordinate Position of the new instance.
	 * @param d1 Angle of the new instance.
	 * @param d2 Length of the new instance.
	 * @param d3 Width of the new instance.
	 */
	public Rectangle(Coordinate coordinate, double d1, double d2, double d3) {
		super(coordinate, d1);
		if(d2 < 0 || d3 < 0)
			throw new IllegalArgumentException("INVALID PARAMETERS!");
		this.length = d2;
		this.width = d3;
	}
	
	/**
	 * Copy constructor.
	 * It calls the superclass' constructor sending it another instance of the same class' position and angle as parameters and then
	 * initializes the length and width of the current instance by using the same values of the rectangle passed as parameter.
	 * @param r Rectangle that we want to copy.
	 */
	public Rectangle(Rectangle r) {
		super(r.getPosition(), r.getAngle());
		this.length = r.getLength();
		this.width = r.getWidth();
	}

	/**
	 * Instance method.
	 * This method's objective is to return the length attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The length of the instance.
	 */
	public double getLength() {
		return length;
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
	 * It is an implementation of the superclass' scale method, which was abstract.
	 * It receives a scaling percentage, checks if it is negative (in that case it throws an exception) and then divides it by
	 * 100 and multiplies the attribute's values by this number to resize them.
	 * @param d The scaling percentage that is going to be used.
	 */
	public void scale(double d) {
		if(d <= 0)
			throw new IllegalArgumentException("Invalid percentage!");
		double scalingValue = d/100;	// We convert the scaling percentage into a value between 0 and 1
		this.length = this.length * scalingValue;
		this.width = this.width * scalingValue;
	}
	
	/**
	 * Instance method.
	 * It is an implementation of the superclass' clone method, which was abstract.
	 * It calls the copy constructor of the instance and then returns this new copy of the instance.
	 * @return The copy of the instance.
	 */
	public Rectangle clone() {
		return new Rectangle(this);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return super.toString() + ",length=" + length + ",width=" + width;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!super.equals(obj))
			return false;
		if (getClass() != obj.getClass())
			return false;
		Rectangle other = (Rectangle) obj;
		return Double.doubleToLongBits(length) == Double.doubleToLongBits(other.length)
				&& Double.doubleToLongBits(width) == Double.doubleToLongBits(other.width);
	}
}