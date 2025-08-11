package es.ua.dlsi.prog3.p4.model;

/**
 * This class represents a Square.
 * It is an AbstractPolygon, so it inherits all the attributes and methods from its superclass.
 * It implements some methods to be able to manage Square and get/change its particular attributes.
 * @author 
 */
public class Square extends AbstractPolygon {
	/**
	 * Instance attribute.
	 * It stores a side for the square.
	 */
	private double side;
	
	/**
	 * Default constructor.
	 * It calls the superclass' constructor and then initializes the side to zero.
	 */
	public Square() {
		super();
		this.side = 0;
	}
	
	/**
	 * Constructor with parameters.
	 * It calls the superclass' constructor sending it a coordinate and rotation angle as parameters and then checks if the rest of
	 * parameters are negative (in that case it throws an exception). If everything is correct, it initializes the attributes to the 
	 * values received as parameters.
	 * @param coordinate Position of the new instance.
	 * @param d1 Angle of the new instance.
	 * @param d2 Side of the new instance.
	 */
	public Square(Coordinate coordinate, double d1, double d2) {
		super(coordinate, d1);
		if(d2 < 0)
			throw new IllegalArgumentException("INVALID PARAMETER!");
		this.side = d2;
	}

	/**
	 * Copy constructor.
	 * It calls the superclass' constructor sending it another instance of the same class' position and angle as parameters and then
	 * initializes the side of the current instance by using the same values of the square passed as parameter.
	 * @param square Square that we want to copy.
	 */
	public Square(Square square) {
		super(square.getPosition(), square.getAngle());
		this.side = square.getSide();
	}

	/**
	 * Instance method.
	 * This method's objective is to return the side attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The width of the instance.
	 */
	public double getSide() {
		return side;
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
		this.side = this.side * scalingValue;
	}
	
	/**
	 * Instance method.
	 * It is an implementation of the superclass' clone method, which was abstract.
	 * It calls the copy constructor of the instance and then returns this new copy of the instance.
	 * @return The copy of the instance.
	 */
	public Square clone() {
		return new Square(this);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return super.toString() + ",side=" + side;
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
		Square other = (Square) obj;
		return Double.doubleToLongBits(side) == Double.doubleToLongBits(other.side);
	}
}