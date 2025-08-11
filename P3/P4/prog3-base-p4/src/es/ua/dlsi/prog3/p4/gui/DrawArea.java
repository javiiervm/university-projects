/**
 * 
 */
package es.ua.dlsi.prog3.p4.gui;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JComponent;

import es.ua.dlsi.prog3.p4.model.Circle;
import es.ua.dlsi.prog3.p4.model.Coordinate;
import es.ua.dlsi.prog3.p4.model.Shape2D;
import es.ua.dlsi.prog3.p4.model.Rectangle;
import es.ua.dlsi.prog3.p4.model.Square;
 
/**
* Component for drawing !
*
* @author sylsau
* (See http://www.ssaurel.com/blog/learn-how-to-make-a-swing-painting-and-drawing-application/)
*
*/
public class DrawArea extends JComponent {
 
  // Image in which we're going to draw
  private Image image;
  // Graphics2D object ==> used to draw on
  private Graphics2D g2;
  // Mouse coordinates
  private int currentX, currentY, oldX, oldY;
  
  boolean circlesFilled=false;
  boolean rectsFilled=false;
 
  List<Shape2D> figures;
  Class<?> selectedFigure;
  
  /**
   * Constructor for DrawArea
   * adds MouseListeners for  pressed and released nuttons
   */
  public DrawArea() {
	  figures = new ArrayList<>();
	  selectedFigure = Circle.class;

	  setDoubleBuffered(false);


	  addMouseListener(new MouseAdapter() {
		  public void mousePressed(MouseEvent e) {
			  // save coord x,y when mouse is pressed
			  oldX = e.getX();
			  oldY = e.getY();
		  }
	  });

	  addMouseListener(new MouseAdapter() {
		  public void mouseReleased(MouseEvent e) {
			  currentX = e.getX();
			  currentY = e.getY();
			  // create new Shape2D
			  Shape2D shape = Shape2DFactory.createShape2D(selectedFigure, new Coordinate(oldX, oldY), new Coordinate(currentX, currentY)); 
			  figures.add(shape);
			  // draw the figure
			  g2.draw(Shape2DFactory.createShape(shape));
			  // refresh draw area to repaint
			  repaint();
		  }
	  });
  }
  
  /**
   * Paints the draw area in the provided graphics device
   * @param g graphic device
   */
  protected void paintComponent(Graphics g) {
    if (image == null) {
      // image to draw null ==> we create
      image = createImage(getSize().width, getSize().height);
      g2 = (Graphics2D) image.getGraphics();
      // enable antialiasing
      g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
      g2.setPaint(Color.black);
      g2.setStroke(new BasicStroke(3));
      // clear draw area
      clear();
    }
 
    g.drawImage(image, 0, 0, null);
  }
 
  /**
   * clear the drawing area
   */
  public void clear() {
	figures.clear();
    g2.setPaint(Color.white);
    // draw white on entire draw area to clear
    g2.fillRect(0, 0, getSize().width, getSize().height);
    g2.setPaint(Color.black);
    repaint();
  }

  /**
   * Set the figure to draw to a circle
   */
  public void drawCircle() {
//    g2.setPaint(Color.black);
	  selectedFigure=Circle.class;
  }

  /**
   * Set the figure to draw to a square
   */
  public void drawSquare() {
	  selectedFigure=Square.class;
  }
 
  /**
   * Set the figure to draw to a rectangle
   */
  public void drawRectangle() {
	  selectedFigure=Rectangle.class;
  }
  
  /**
   * A Shape2D factory
   */
  static class Shape2DFactory {
		
	  /**
	   * creates shapes to draw
	   * 
	   * @param c the type of shape to draw
	   * @param origin bounding box origin coordinate
	   * @param destination bounding box destination coordinate
	   * @return a shape to be drawn
	   */
		public static Shape2D createShape2D(Class<?> c, Coordinate origin, Coordinate destination)  {
			Shape2D d;
			Object[] objects=null;
			
			// I need a switch... >:-(
			if (c == Circle.class) {
				// Compute circle radius
				Coordinate r = destination.subtract(origin);
				double xr = r.getX();
				double yr = r.getY();
				double radius = Math.sqrt( xr*xr + yr*yr );
				objects = new Object[] { origin, radius };
			} else if (c == Rectangle.class) {
				// Compute length and width
				double l = Math.abs(destination.getX() - origin.getX());
				double w = Math.abs(destination.getY() - origin.getY());
				Coordinate position = Shape2DFactory.computeRectanglePosition(origin, destination);
				objects = new Object[] { position, 0.0, l, w };
				
			} else if (c == Square.class) {
				// Compute position and side length
				double side = Math.min(Math.abs(destination.getY()-origin.getY()), Math.abs(destination.getX()-origin.getX()));
				double l = destination.getX() - origin.getX();
				double w = destination.getY() - origin.getY();
				Coordinate position = Shape2DFactory.computeSquarePosition(origin, destination);
				objects = new Object[] { position, 0.0, side };
			}
			try {
				if (objects==null)
					d = (Shape2D) c.newInstance();
				else {
					// objects contains ctor arguments
					Class<?>[] paramTypes = new Class<?>[objects.length];				
					for (int i=0; i < objects.length; i++) {
						paramTypes[i] = objects[i].getClass() == Double.class ? double.class : objects[i].getClass();
					}
					Constructor<?> ctor = c.getConstructor(paramTypes);
					d = (Shape2D) ctor.newInstance(objects);
				}
				return d;
			} catch (ClassCastException e) {
				throw new IllegalArgumentException("Unknown shape: "+c.getSimpleName(), e); 
			} catch (InstantiationException | IllegalAccessException | NoSuchMethodException | SecurityException | IllegalArgumentException | InvocationTargetException e) {
				throw new IllegalArgumentException("Can not instantiate shape: "+ c.getSimpleName(),e);
			}
		}
		
		
		private static Coordinate computeRectanglePosition(Coordinate origin, Coordinate destination) {
			Coordinate position;
			Coordinate aux = destination.subtract(origin);
			if (aux.getX() >= 0) {
				if (aux.getY()>=0)
					position = origin;
				else
					position = new Coordinate(origin.getX(),destination.getY());
			} else {
				if (aux.getY()>=0)
					position = new Coordinate(destination.getX(), origin.getY());
				else
					position = destination;
			}
			return position;
		}

		private static Coordinate computeSquarePosition(Coordinate origin, Coordinate destination) {
			double side = Math.min(Math.abs(destination.getY()-origin.getY()), Math.abs(destination.getX()-origin.getX()));
			Coordinate position;
			Coordinate aux = destination.subtract(origin);
			if (aux.getX() >= 0) {
				if (aux.getY()>=0)
					position = origin;
				else
					position = new Coordinate(origin.getX(),origin.getY()-side);
			} else {
				if (aux.getY()>=0)
					position = new Coordinate(origin.getX()-side, origin.getY());
				else
					position = new Coordinate(origin.getX()-side, origin.getY()-side);
			}
			return position;
		}
		
		private static Shape createShape(Shape2D figure) {
			Shape shape=null;
		
			if (figure instanceof Circle) {
				Circle circle = (Circle)figure;
				double boundingBoxOrigin_x = figure.getPosition().getX()-circle.getRadius();
				double boundingBoxOrigin_y = figure.getPosition().getY()-circle.getRadius();
				shape = new Ellipse2D.Double(boundingBoxOrigin_x, boundingBoxOrigin_y, circle.getRadius()*2, circle.getRadius()*2);
			}
			if (figure instanceof Rectangle) {
				Rectangle rectangle = (Rectangle)figure;
				shape = new Rectangle2D.Double(figure.getPosition().getX(), figure.getPosition().getY(), rectangle.getLength(), rectangle.getWidth());
			}
			if (figure instanceof Square) {
				Square square = (Square)figure;
				shape = new Rectangle2D.Double(figure.getPosition().getX(), figure.getPosition().getY(), square.getSide(), square.getSide());
			}
			
			return shape;
		}

	}

  /**
   * Fill circles in the drawing area with a color
   */
  public void fillCircles() {
	  Shape shape;
	  for (Shape2D figure : figures) {
		  if (figure instanceof Circle) {
			  shape = Shape2DFactory.createShape(figure);
			  g2.setPaint(Color.black);
			  g2.draw(shape);
			  g2.setPaint(circlesFilled ? Color.white : Color.red);
			  g2.fill(shape);
		  }
	  }
	  circlesFilled = !circlesFilled;
	  g2.setPaint(Color.black);
	  repaint();
  }

  /**
   * Fill rectangles and swaures in the drawing area with a color
   */
  public void fillRects() {
	  Shape shape;
	  for (Shape2D figure : figures) {
		  if (figure instanceof Rectangle || figure instanceof Square) {
			  shape = Shape2DFactory.createShape(figure);
			  g2.setPaint(Color.black);
			  g2.draw(shape);
			  g2.setPaint(rectsFilled ? Color.white : Color.orange);
			  g2.fill(shape);
		  }
	  }
	  rectsFilled = !rectsFilled;
	  g2.setPaint(Color.black);
	  repaint();  }

}
