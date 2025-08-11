package es.ua.dlsi.prog3.p4.model;

import java.util.Objects;

/**
 * This class represents a 2D figure.
 * It is an abstract class, that is, it is not meant to be used to create instances of this class. Its objective is for their
 * subclasses to use its methods.
 * It implements some methods to be able to manage the 2D figures that are going to be drawn.
 * @author 
 */
public abstract class Shape2D {
	/**
	 * Instance attribute.
	 * It stores a position for the 2D shape, which is a Coordinate data type (x,y).
	 */
	private Coordinate position;
	
	/**
	 * Default constructor.
	 * It initializes the position attribute calling the default constructor of its class.
	 */
	protected Shape2D() {
		this.position = new Coordinate();
	}
	
	/**
	 * Constructor with parameters.
	 * It initializes the position attribute calling the constructor with parameters of its class, and sends it the position
	 * received as parameter.
	 * @param position Position that is going to be used to initialize the attribute.
	 */
	protected Shape2D(Coordinate position) {
		this.position = new Coordinate(position);
	}
	
	/**
	 * Copy constructor.
	 * It initializes the position attribute by using the position attribute of the shape instance passed as
	 * parameter.
	 * @param shape The shape which we want to copy.
	 */
	protected Shape2D(Shape2D shape) {
		this.position = shape.position;
	}

	/**
	 * Instance method.
	 * This method's objective is to return the position attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The instance's position.
	 */
	public Coordinate getPosition() {
		return position;
	}
	
	/**
	 * Instance method.
	 * This method's objective is to move the 2D shape from its current position to a new one. In order to do that, it first
	 * has to check if the new position passed as parameter is not null (if it is, it returns the current position of the instance).
	 * Then, it stores the current position of the instance in a new variable which returns at the end, and then it changes the
	 * instance's position to the one specified in the parameter.
	 * @param newPosition The new position for the instance.
	 * @return The old position of the instance.
	 */
	public Coordinate move(Coordinate newPosition) {
		if(newPosition==null)
			return position;
		Coordinate oldPos = new Coordinate(this.position);
		this.position = newPosition;
		return oldPos;
	}
	
	/**
	 * Instance attribute.
	 * This method has to return a copy of the current Shape2D instance but changing its position. For that, it first stores the
	 * current position of the instance in a variable, then changes the position to the one passed as parameter and creates a copy
	 * of the instance. After that, it changes the position of the current instance to the old one, and finally it returns the
	 * copy.
	 * @param position The new position for the copy.
	 * @return The copy of the instance.
	 */
	public Shape2D clone(Coordinate position) {
		Coordinate lastPosition = this.position;
		this.position = new Coordinate(position);
		Shape2D shapeCopy = this;
		this.position = lastPosition;
		return shapeCopy;
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Shape2D other = (Shape2D) obj;
		return Objects.equals(position, other.position);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return "(" + position.getX() + "," + position.getY() + ")";
	}

	/**
	 * Instance method.
	 * This is an abstract method that is declared here to be used by the subclasses of this class.
	 * Its objective is to scale the 2D shape using the scaling percentage passed as parameter.
	 * @param d The scaling percentage that is going to be used.
	 */
	public abstract void scale(double d);
	
	/**
	 * Instance method.
	 * This is an abstract method that is declared here to be used by the subclasses of this class.
	 * Its objective is to clone (copy) the current instance.
	 * @return A copy of the Shape2D.
	 */
	public abstract Shape2D clone();
}