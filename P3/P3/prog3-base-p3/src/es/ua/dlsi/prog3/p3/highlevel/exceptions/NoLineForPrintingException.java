package es.ua.dlsi.prog3.p3.highlevel.exceptions;

/**
 * This class is created to manage an exception declared by the user, that means, it doesn't exist outside this project.
 * This exception is thrown when LinePrinter wasn't able to read any string from the channel. 
 * It doesn't print any error message, throwing the exception is enough.
 * @author 
 */
public class NoLineForPrintingException extends Exception {
	/**
	 * Constructor.
	 * It calls the constructor of the parent class, Exception.
	 * It doesn't receive any parameter.
	 */
	public NoLineForPrintingException() {
		super();
	}
}