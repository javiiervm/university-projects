package es.ua.dlsi.prog3.p4.model;

/**
 * This class represents an AbstractPolygon.
 * It is a Shape2D, so it inherits all the attributes and methods from its superclass.
 * It implements some methods to be able to manage AbstractPolygon and get/change its particular attributes.
 * @author 
 */
public abstract class AbstractPolygon extends Shape2D {
	/**
	 * Instance attribute.
	 * It stores a rotation angle for the AbstractPolygon.
	 */
	private double angle;
	
	/**
	 * Default constructor.
	 * It calls the superclass' constructor and then initializes the attribute to zero.
	 */
	protected AbstractPolygon() {
		super();
		this.angle = 0;
	}
	
	/**
	 * Constructor with parameters.
	 * It calls the superclass' constructor sending it a coordinate and then it initializes the attribute angle to the 
	 * value received as parameters.
	 * @param coordinate Position of the new instance.
	 * @param d Angle of the new instance.
	 */
	protected AbstractPolygon(Coordinate coordinate, double d) {
		super(coordinate);
		this.angle = d;
	}

	/**
	 * Copy constructor.
	 * It calls the superclass' constructor sending it another instance of the same class' position and then
	 * initializes the andle of the current instance by using the same value of the AbstractPolygon passed as parameter.
	 * @param polygon Polygon that we want to copy.
	 */
	protected AbstractPolygon(AbstractPolygon polygon) {
		super(polygon.getPosition());
		this.angle = polygon.getAngle();
	}
	
	/**
	 * Instance method.
	 * This method's objective is to return the angle attribute of the current instance. It can be returned directly, it
	 * is not necessary to perform any defensive copy.
	 * @return The rotation angle of the instance.
	 */
	public double getAngle() {
		return angle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return super.toString() + ",angle=" + angle;
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
		AbstractPolygon other = (AbstractPolygon) obj;
		return Double.doubleToLongBits(angle) == Double.doubleToLongBits(other.angle);
	}
	
	/**
	 * Instance method.
	 * Its objective is to change the rotation angle of the current instance.
	 * For that, it first checks if the received parameter is a valid angle (it can't be less than -360 or more than 360). If there
	 * is any error it throws an exception, otherwise it has to check if the new number is a valid angle (between 0 and 360).
	 * If it is not inside that range, it adds/substracts the difference between 360 and that new number to obtain a valid angle,
	 * then it assigns it to the instance's angle.
	 * @param d Degrees that are going to be added to the angle.
	 */
	public void rotate(double d) {
		if(d < -360.0 || d >= 360.0)
			throw new IllegalArgumentException("INVALID ANGLE");
		double newAngle = this.getAngle() + d;
		while(newAngle < 0 || newAngle > 360) {
			if(newAngle < 0)
				newAngle = 360 + newAngle;
			if(newAngle > 360)
				newAngle = 360 - newAngle;
		}
		this.angle = newAngle;
	}
}