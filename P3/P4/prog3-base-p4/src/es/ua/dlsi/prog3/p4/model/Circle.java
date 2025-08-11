package es.ua.dlsi.prog3.p4.model;

/**
 * This class represents a Circle.
 * It is a Shape2D, so it inherits all the attributes and methods from its superclass.
 * It implements some methods to be able to manage Circle and get/change its particular attributes.
 * @author 
 */
public class Circle extends Shape2D {
	/**
	 * Instance attribute.
	 * It stores a radius for the circle.
	 */
	private double radius;
	
	/**
	 * Default constructor.
	 * It calls the superclass' constructor and then initializes the radius attribute to zero.
	 */
	public Circle() {
		super();
		this.radius = 0;
	}
	
	/**
	 * Constructor with parameters.
	 * It calls the superclass' constructor sending it a coordinate as parameter and then checks if the radius passed as parameter 
	 * is negative (in that case it throws an exception). If everything is correct, it initializes the radius attribute to the one 
	 * received as parameter.
	 * @param coordinate The position of the Shape2D, which is going to be sent to the superclass' constructor.
	 * @param d The radius to initialize the attribute of the instance.
	 */
	public Circle(Coordinate coordinate, double d) {
		super(coordinate);
		if(d<0)
			throw new IllegalArgumentException("Radius can't be negative!");
		this.radius = d;
	}

	/**
	 * Copy constructor.
	 * It calls the superclass' constructor sending it another instance of the same class' position as parameter and then
	 * initializes the radius of the current instance by using the same value of the circle passed as parameter.
	 * @param circle Circle that we want to copy.
	 */
	public Circle(Circle circle) {
		super(circle.getPosition());
		this.radius = circle.getRadius();
	}
	
	/**
	 * Instance method.
	 * This method's objective is to return the radius attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The radius of the instance.
	 */
	public double getRadius() {
		return radius;
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
		this.radius = this.radius * scalingValue;
	}
	
	/**
	 * Instance method.
	 * It is an implementation of the superclass' clone method, which was abstract.
	 * It calls the copy constructor of the instance and then returns this new copy of the instance.
	 * @return The copy of the instance.
	 */
	public Circle clone() {
		return new Circle(this);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return super.toString() + ",radius=" + radius;
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
		Circle other = (Circle) obj;
		return Double.doubleToLongBits(radius) == Double.doubleToLongBits(other.radius);
	}

	
}