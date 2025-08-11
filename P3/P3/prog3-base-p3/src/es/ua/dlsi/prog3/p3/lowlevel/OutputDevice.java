package es.ua.dlsi.prog3.p3.lowlevel;

import java.nio.BufferUnderflowException;

/**
 * This class represents an output device.
 * It also implements some methods to get data from the associated
 * channel of this device.
 * @author 
 */
public class OutputDevice extends IODevice {
	/**
	 * Constructor.
	 * It creates a new OutputDevice instance.
	 * For that, it calls the constructor of the parent class, IODevice, sending it an int parameter.
	 * @param bufferSize The size of the buffer.
	 */
	protected OutputDevice(int bufferSize) {
		super(bufferSize);
	}
	
	/**
	 * Instance method.
	 * Its objective is to get all the data stored in the channel associated to the OutputDevice. For that, it uses the
	 * getChannel() function of the parent class in order to know which channel it is going to get the data from, and then
	 * it calls output(), a function from the superparent class Channel, to return all the data.
	 * @return All the data in the associated channel.
	 */
	protected byte receiveFromChannel() {
		return getChannel().output();
	}
	
	/**
	 * Instance method.
	 * This method has to return the number of bytes of data from the associated channel corresponding to the number passed as
	 * parameter. For that, it first gets the channel using getChannel, as specified before. Then it checks if the channel has data
	 * and if the parameter is not zero, if one of these conditions is not satisfied it returns a byte array of length 0. Then,
	 * it checks if the parameter's value is inside the specified range, and if not, it throws an exception. Finally, if everyting
	 * is correct, it creates a byte array with the size specified in the parameter, and calls the output() method until the array
	 * is full of data; then it returns it.
	 * @param num_bytes The number of bytes of data that we want to get.
	 * @return An array with the data bytes.
	 */
	protected byte[] get(int num_bytes) {
		Channel channel = getChannel();
		if(!(channel.hasData()) || num_bytes == 0) {
			return new byte[0];
		}
		if(num_bytes < 0 || num_bytes > getBufferSize()) {
			throw new IllegalArgumentException("Invalid parameter");
		}
		byte[] list = new byte[num_bytes];
		for(int i = 0; i < num_bytes; i++) {
			list[i] = channel.output();
		}
		return list;
	}
	
	/**
	 * DON'T TOUCH THIS METHOD!!! The earth will collapse on itself if you ever think of doing it!
	 * 
	 * Reads a string from the channel. 
	 * 
	 * The channel MUST contain a string of characteres encoded as
	 * 
	 * 
	 * [length][A-Ba-b0-9]+
	 * 
	 * which means that the first byte is the string length, and the rest of bytes are the actual string 
	 * 
	 * 
	 * @return the string read, as an String object, or an empty if there is no data in the channel 
	 * @throws BufferUnderflowException if the channel becomes empty before the whole string is read, i.e. the data in the channel is corrupted
	 * @throws IllegalStateException if there is no channel associated to this device 
	 */
	protected String readStoredString() {
		byte[] data = null;
		char[] string = null;
		data = get(1);
		if (data.length != 1) 
			return "";
		int string_length = data[0];		
		data = get(string_length);
		if (data.length != string_length)
			throw new BufferUnderflowException();
		string = new char[string_length];
		for (int i=0; i < string_length; i++)
			string[i] = (char) data[i];
		return String.valueOf(string);
	}
}
