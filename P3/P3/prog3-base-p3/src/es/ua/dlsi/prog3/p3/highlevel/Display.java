package es.ua.dlsi.prog3.p3.highlevel;

import java.nio.BufferUnderflowException;

import es.ua.dlsi.prog3.p3.lowlevel.OutputDevice;

/**
 * This class represents a Display device, which is an OutputDevice, so it extends the OutputDevice class and inherits
 * all its attributes and methods. 
 * It also implements some methods to manage the device's properties.
 * @author 
 */
public class Display extends OutputDevice {
	/**
	 * Instance attribute.
	 * It stores the number of rows and columns that the display's matrix is going to have.
	 */
	private int pixel_rows;
	
	/**
	 * Instance attribute.
	 * It represents the matrix of the display.
	 */
	private byte[][] display;
	
	/**
	 * Constructor with parameters.
	 * It receives a parameter that represents the number of rows and columns the matrix is going to have, it first calls
	 * the parent class' constructor passing as parameter N*N*2 (to create an array with the final size of the matrix) and then
	 * initializes the attributes of the instance.
	 * @param N The number of rows and columns.
	 */
	public Display(int N) {
		super(N*N*2);
		this.pixel_rows = N;
		this.display = new byte[N][N];
	}
	
	/**
	 * Instance method.
	 * It's objective is to provide the size of the display, that is, the size of the matrix. In order to do so, it returns the
	 * value of the pixel_rows attribute of the instance. It is not necessary to perform any defensive copy since there is no
	 * risk of the data to be modified, so it returns the attribute directly.
	 * @return The pixel_rows attribute's value.
	 */
	public int getDisplaySize() {
		return this.pixel_rows;
	}
	
	/**
	 * Instance method.
	 * Its objective is to update the value of the bytes of the matrix in the display, that is, "refresh" them. In order to do so, 
	 * it first creates a value for the x coordinate and another for the y coordinate of each cell of the matrix. It then uses a
	 * while loop that first checks if there is still data in the channel (otherwise the loop breaks), then it gets the x and y coordinates
	 * and checks if their values are inside the specified range. If there is any error, it throws an exception.
	 * After that, it updates the matrix's corresponding byte to 1, it activates it.
	 * Finally, it creates a new matrix array and iterates over the initial matrix to copy it, byte by byte, and then it returns this
	 * new matrix. Since it is a copy and not the original one, there is no risk of the data being modified.
	 * @return A copy of the updated matrix.
	 * @throws IllegalStateException If the device has no associated channel.
	 * @throws BufferUnderflowException If there are not enough bytes in the channel (at least two).
	 * @throws IndexOutOfBoundsException If the (x,y) coordinates read from the buffer don't correspond to some pixel on the screen.
	 */
	public byte[][] refresh() throws IllegalStateException, BufferUnderflowException, IndexOutOfBoundsException {
		byte x, y;
		byte[][] copyMatrix = new byte[pixel_rows][pixel_rows];
		while(true) {
			if(!(getChannel().hasData()))
				break;
			x = receiveFromChannel();
			y = receiveFromChannel();
			if((int)x < 0 || (int)x > pixel_rows)
				throw new IndexOutOfBoundsException("Invalid X parameter");
			if((int)x < 0 || (int)x > pixel_rows)
				throw new IndexOutOfBoundsException("Invalid Y parameter");
			display[x][y] = (byte)1;
		}
		for(int i = 0; i < pixel_rows; i++)
			for(int j = 0; j < pixel_rows; j++)
				copyMatrix[i][j] = display[i][j];
		return copyMatrix;
	}
	
	/**
	 * Instance method.
	 * Its objective is to clear all the data of the matrix, that is, to disable every activated byte in the display. In order
	 * to do so, it iterates over every single byte of the matrix (row and column) and sets to 0 the value of the corresponding
	 * cell of the matrix.
	 */
	public void clear() {
		for(int i = 0; i < pixel_rows; i++)
			for(int j = 0; j < pixel_rows; j++)
				this.display[i][j] = 0;
	}
}