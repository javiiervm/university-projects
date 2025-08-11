
package es.ua.dlsi.prog3.p1;

import java.util.ArrayList;

/**
 * SummaryStatistics class from practice 1 (Subject: Programming 3)
 * @author 
 */

/** This class is designed to calculate summary statistics such as the average, maximum,
 * and minimum of a set of integer values. It uses an ArrayList to store the values and 
 * allows users to add new values or retrieve statistical information about the data set.
 * Each instance of this class is assigned a unique ID, which increments with each new object created.
 * The class is not immutable since values can be added after creation.
 */
public class SummaryStatistics {
    /** Class attribute.
     * Keeps track of the next available ID for each new instance of the class. It is initialized to 1 
     * and increments with each new object created, to make sure two different objects will never have
     * the same identifier. Since every instance will share the value of this variable, it is defined
     * as static.
     */
    private static int NEXT_ID = 1;

    /** Instance attribute.
     * Stores the unique identifier of the object, based on the NEXT_ID static attribute's value.
     * Obviously, since this variable is unique, it can't be shared with other instances so it is not
     * defined as static, unlike NEXT_ID.
     */
    private int id;

    /** Instance attribute.
     * An ArrayList that stores the values added to this object. It represents the data set for 
     * which the statistics (average, min, max) are calculated. As we will see later, new values
     * can be added through the add method. Plus, every instance will have different values, so it
     * is not defined as static either.
     */
    private ArrayList<Integer> values;

    /** Default constructor.
     * This constructor initializes the object with an empty list of values and assigns a unique ID 
     * to the object. In addition, it increases the NEXT_ID variable in one unit, to make sure the 
     * next instance will have a different identifier.
     */
    public SummaryStatistics() {
        this.id = NEXT_ID;
        NEXT_ID = NEXT_ID + 1;
        this.values = new ArrayList<>(); // Initializes the values list
    }

    /** Parameterized constructor.
     * This constructor initializes the object with a pre-existing list of values and assigns a unique ID.
     * For that, it copies the ArrayList passed as parameter (defensive copy). As well as with the 
     * default constructor, it increases NEXT_ID in one unit, for the same reason mentioned above.
     * @param values the ArrayList of integer values to be stored in the object.
     */
    public SummaryStatistics(ArrayList<Integer> values) {
        this.id = NEXT_ID;
        NEXT_ID = NEXT_ID + 1;
        this.values = new ArrayList<>(values);
    }

    /** Copy constructor.
     * Creates a new object by copying the ID and values from an existing SummaryStatistics object. Then
     * it copies the ArrayList of the object passed as parameter into a new ArrayList (defensive copy)
     * and stores it in the values variable of our current object.
     * @param statistics the object to be copied.
     */
    public SummaryStatistics(SummaryStatistics statistics) {
        this.id = statistics.id;
        this.values = new ArrayList<>(statistics.values);
    }

    /** Instance method.
     * Adds to the object's list of values the value passed as parameter. In this case it is not necessary
     * to copy anything so it adds it directly to the object.
     * @param value the value to be added to the list.
     */
    public void add(int value) {
        this.values.add(value);
    }
    
    /** Instance method.
     * Returns the unique identifier (ID) of this SummaryStatistics object. Remember that each object
     * has a distinct ID, assigned when the object is created. In this case it is not necessary to copy
     * anything.
     * @return the unique ID of the object as an integer.
     */
    public int getId() {
        return this.id;
    }


    /** Instance method.
     * Calculates and returns the average of the values stored in the object. 
     * For that, it first checks if the values are empty, in that case it returns null. Otherwise,
     * it uses a for loop to iterate over all the ArrayList and add each value to the average variable,
     * finally it divides the average and the ArrayList size (remember that the average of a set of
     * numbers is their sum divided by the total number of elements in the set). Finally it returns
     * this value.
     * @return the average value as an Integer, or null if the list is empty.
     */
   public Integer getAverage() {
        if (values.isEmpty())
            return null;
        int average = 0;
        for (int i = 0; i < this.values.size(); i++)
            average = average + this.values.get(i);
        average = average / this.values.size();
        return average;
    }

    /** Instance method.
     * Finds and returns the maximum value from the list. 
     * If no values are present, it returns null. Otherwise, it initializes the max value in the first
     * one from the ArrayList, after that it uses a for loop to iterate over all the list and if it
     * finds a number greater than the one stored in the max value, than it changes max for the value
     * it has just found, so when the iterations end the maximum value will be stored in max, which is
     * returned.
     * @return the maximum value as an Integer, or null if the list is empty.
     */
    public Integer getMax() {
        if (values.isEmpty())
            return null;
        int max = this.values.get(0); // Initialize with the first value in the list
        for (int i = 1; i < this.values.size(); i++)
            if (max < this.values.get(i))
                max = this.values.get(i);
        return max;
    }

    /** Instance method.
     * Finds and returns the minimum value from the list. 
     * If no values are present, it returns null. Otherwise, it initializes the min value in the first
     * one from the ArrayList, after that it uses a for loop to iterate over all the list and if it
     * finds a number smaller than the one stored in the min value, than it changes min for the value
     * it has just found, so when the iterations end the smallest value will be stored in min, which is
     * returned.
     * @return the minimum value as an Integer, or null if the list is empty.
     */
    public Integer getMin() {
        if (values.isEmpty())
            return null;
        int min = this.values.get(0); // Initialize with the first value in the list
        for (int i = 1; i < this.values.size(); i++)
            if (min > this.values.get(i))
                min = this.values.get(i);
        return min;
    }

    /** Instance method.
     * Returns the size of the ArrayList, representing the number of values stored in the object.
     * For that, it is not necessary to copy anything, it just returns the size since there is no
     * risk of the ArrayList's content to be modified.
     * @return the size of the list as an integer.
     */
    public int getSize() {
        return this.values.size();
    }

    /** Static method.
     * Returns the number of instances that have been created so far by checking the value of NEXT_ID.
     * It is important to take into account that NEXT_ID will store the value of the next object, that is,
     * it hasn't been created yet. For that reason, in order to know how much objects we have created
     * so far, it has to return its value - 1.
     * @return the total number of instances created as an integer.
     */
    public static int COUNT_INSTANCES() {
        return NEXT_ID - 1;
    }
}
