package es.ua.dlsi.prog3.p3.highlevel;

import java.nio.BufferUnderflowException;

import es.ua.dlsi.prog3.p3.highlevel.exceptions.NoLineForPrintingException;
import es.ua.dlsi.prog3.p3.lowlevel.OutputDevice;

/**
 * This class represents a LinePrinter device, which is an OutputDevice, so it extends the OutputDevice class and inherits
 * all its attributes and methods. 
 * It also implements some methods to manage the device's properties.
 * @author 
 */
public class LinePrinter extends OutputDevice {
	/*
	 * Instance attribute.
	 * It is a static attribute (that is, every single instance of this class will have exactly the same value for it) that defines
	 * the maximum length that a text line can have.
	 */
	private static final int MAX_LINE_LENGTH = 80;
	
	/**
	 * Constructor.
	 * It creates a new LinePrinter instance.
	 * For that, it calls the constructor of the parent class, OutputDevice, and sends it as parameter the value of
	 * MAX_LINE_LENGTH plus one.
	 */
	public LinePrinter() {
		super(MAX_LINE_LENGTH + 1);
	}
	
	/**
	 * Instance method.
	 * The objective of this method is to print the data read as a string. In order to do so, it first calls the readStoredString() 
	 * from the parent class. In case the read string's length is 0 or there is a BufferUnderFlowException captured in the process,
	 * it throws another exception.
	 * Otherwise it returns the read string.
	 * @return The string of data read.
	 * @throws NoLineForPrintingException If no data could be read.
	 */
	public String printLine() throws NoLineForPrintingException {
		try {
			String read = readStoredString();
			if(read.length()==0)
				throw new NoLineForPrintingException();
			return read;
		} catch (BufferUnderflowException e) {
			throw new NoLineForPrintingException();
		}
	}
}