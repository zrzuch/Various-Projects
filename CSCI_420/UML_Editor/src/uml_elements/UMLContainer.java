package uml_elements;

import java.util.Vector;
import javafx.scene.layout.Pane;
import javafx.scene.control.TextArea;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import utility.UMath;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import application.Main;
import interface_elements.SumlToolBar.EditMode;

public class UMLContainer
{
	private Vector<UMLLayout> classes = new Vector<UMLLayout>();
    private Pane layout;

    /**
    * Constructs a UMLContainer with the pane
    */
    public UMLContainer(Pane layout)
    {
    	this.layout = layout;
    }

    /**
    * Add a default UML at (x,y) to the vector
    */
	public void add(double x, double y)
	{
		UMLLayout uml = new UMLLayout(classes.size(), x, y);
		layout.getChildren().addAll(uml.cell, uml.top, uml.mid, uml.btm);
		classes.add(uml);
	}

	/**
	* Remove indexed UMLLayout from the vector
	*/
	public void remove(int index)
	{
		int initSize = classes.size() - 1;
		removeFromLayout(index);
		classes.remove(index);
		if (index < initSize)
		{
			for (int i = 0; i < classes.size(); ++i)
			{
				classes.elementAt(i).index = i;
			} 
		}
	}

	/**
	* Clear the vector and remove all UMLLayouts in the vector from the pane
	*/
	public void clear()
	{
		for (int i = 0; i < classes.size(); ++i)
		{
			removeFromLayout(i);
		}
		classes.clear();
	}

	/**
	* @return int size of the container
 	*/
	public int size()
	{
		return classes.size();
	}

	/**
	* @return TextArea top of indexed UMLLayout
	*/
	public TextArea topAt(int index)
	{
		return classes.elementAt(index).top;
	}

	/**
	* @return TextArea mid of indexed UMLLayout
	*/
	public TextArea midAt(int index)
	{
		return classes.elementAt(index).mid;
	}

	/**
	* @return TextArea bottom of indexed UMLLayout
	*/
	public TextArea btmAt(int index)
	{
		return classes.elementAt(index).btm;
	}

	/**
	* Remove indexed UMLLayout from the pane
	*/
	private void removeFromLayout(int index)
	{
		layout.getChildren().removeAll(classes.elementAt(index).cell, 
			classes.elementAt(index).top, classes.elementAt(index).mid, 
			classes.elementAt(index).btm);
	}

	/**
	* @return String representation of the container
	*/
	public String toString()
	{
		String str = "";
		UMLLayout uml;
		for (int i = 0; i < classes.size(); ++i)
		{
			uml = classes.elementAt(i);
			str += uml.x + " " + uml.y
				+ "\n[\n" 
				+ uml.top.getText().trim().replaceAll("\n", System.getProperty("line.separator"))
				+ "\n]\n[\n"
				+ uml.mid.getText().trim().replaceAll("\n", System.getProperty("line.separator"))
				+ "\n]\n[\n"
				+ uml.btm.getText().trim().replaceAll("\n", System.getProperty("line.separator")) 
				+ "\n]\n";
		}
		return str;
	}

	// Private class is used since an UMLLayout cannot be constructed without a container
	private class UMLLayout
	{
	    public double x;
	    public double y;

	    private double X_MIN = 0;
	    private double Y_MIN = 0;

	    private double orgX;
	    private double orgY;

	    private final static double barHeight = 15;
	    private final static double borderThickness = 3;
	    private final static double mWidth = 100;
	    private double width1 = 100;
	    private double width2 = 100;
	    private double width3 = 100;

	    private final static double mHeight = 30;
	    private double height1 = 30;
	    private double height2 = 30;
	    private double height3 = 30;
	    
	    private double rectWidth = width1 + (borderThickness * 2);
	    private double rectHeight = barHeight + height1
	    		                  + height2 + height3
	    		                  + (borderThickness * 2);

	    public TextArea top = new TextArea();
	    public TextArea mid = new TextArea();
	    public TextArea btm = new TextArea();
	    public Rectangle cell;
	    private Text currText = new Text();

	    public int index;

		/**
	    * Constructs a UMLLayout with a pane and specified x and y positions
	    */
	    public UMLLayout(int index, double x, double y)
	    {
	    	this.index = index;
	        this.x = x;
	        this.y = y;
	        init();
	    }

	    /**
	    * Updates and sets X position for all elements
	    */
	    public void setX(double x)
	    {
	    	this.x = UMath.clamp(x, X_MIN, getMaxX());
	        setXInLayout();
	    }

	    /**
	    * Updates and sets Y position for all elements
	    */
	    public void setY(double y)
	    {
	    	this.y = UMath.clamp(y, Y_MIN, getMaxY());
	        setYInLayout();
	    }

	    /**
	    * Updates and sets X and Y position for all elements
	    */
	    public void setPosition(double x, double y)
	    {
	    	setX (x);
	    	setY (y);
	    }
	    
	    public void clampToBounds ()
	    {
	    	setX (x);
	    	setY (y);
	    }

	    /**
	     * Returns the maximum allowed x in the given layout
	     * @return max x
	     */
	    public double getMaxX()
	    {
	    	return layout.getWidth() - getMaxWidth() - (borderThickness * 2);
	    }
	    
	    /**
	     * Returns the maximum allowed y in the given layout
	     * @return max y
	     */
	    public double getMaxY()
	    {
	    	return layout.getHeight() - getMaxHeight() - (borderThickness * 2);
	    }

	    /**
	    * Moves current UMLLayout to the front of the layout
	    */
	    public void moveToFront()
	    {
	        cell.toFront();
	        top.toFront();
	        mid.toFront();
	        btm.toFront();
	    }

	    /**
	    * Set X position
	    */
	    private void setXInLayout()
	    {
	        cell.setX(x);
	        top.setLayoutX(x + borderThickness);
	        mid.setLayoutX(x + borderThickness);
	        btm.setLayoutX(x + borderThickness);
	    }

	    /**
	    * Set Y position
	    */
	    private void setYInLayout()
	    {
	        cell.setY(y);
	        top.setLayoutY(y + barHeight + borderThickness);
	        mid.setLayoutY(y + height1 + barHeight + borderThickness);
	        btm.setLayoutY(y + height2 + height1 + barHeight + borderThickness);
	    }

	    /**
	    * Updates the widths 
	    */
	    private void updateWidths()
	    {
	        cell.setWidth(getMaxWidth() + (borderThickness * 2));
	        top.setPrefWidth(getMaxWidth());
	        mid.setPrefWidth(getMaxWidth());
	        btm.setPrefWidth(getMaxWidth());
	    }

	    private double getMaxHeight()
	    {
	        return barHeight + height1 + height2 + height3;
	    }

	    /**
	    * gets the max width so that the widths of the textareas coincide
	    * @return double maxWidth
	    */
	    private double getMaxWidth()
	    {
	        return UMath.maxOfDoubles(width1, UMath.maxOfDoubles(width2, width3));
	    }

	    /**
	    * private method that is called to initialize the 
	    * objects of the class and setup the event behavior
	    */
	    private void init()
	    {	
	        currText.setFont(Font.font("Verdana", FontWeight.NORMAL, 12));
	        top.setFont(Font.font("Verdana", FontWeight.NORMAL, 12));
	        mid.setFont(Font.font("Verdana", FontWeight.NORMAL, 12));
	        btm.setFont(Font.font("Verdana", FontWeight.NORMAL, 12));

	        cell = new Rectangle(x,y,rectWidth,rectHeight);
	        cell.setArcWidth(8);
	        cell.setArcHeight(8);
	        cell.setOnMouseClicked(e -> 
	        {
	            if (Main.toolBar.currentEditMode() == EditMode.DELETE_MODE)
	            {
	                remove(index);
	            }
	        });
	        cell.setOnMousePressed(e -> 
	        {
	            orgX = UMath.clamp(e.getX(), X_MIN, getMaxX());
	            orgY = UMath.clamp(e.getY(), Y_MIN, getMaxY());
	            moveToFront();
	            e.consume();
	        });
	        cell.setOnMouseDragged(e -> 
	        {
	            double translateX = e.getX() - orgX;
	            double translateY = e.getY() - orgY;

	            orgX = UMath.clamp(e.getX(), X_MIN, getMaxX());
	            orgY = UMath.clamp(e.getY(), Y_MIN, getMaxY());

	            setX (x + translateX);
	            setY (y + translateY);

	            e.consume();
	        });

	        top.setMinWidth( mWidth );
	        top.setPrefWidth( width1 );
	        top.setMinHeight( mHeight );
	        top.setPrefHeight( height1 );
	        top.textProperty().addListener((str, oldValue, newValue) ->
	        {
	            currText.setText(top.getText());

	            width1 = UMath.maxOfDoubles(mWidth, currText.getLayoutBounds().getWidth() + 20);
	            updateWidths();

	            height1 = UMath.maxOfDoubles(mHeight, currText.getLayoutBounds().getHeight() * 1.08 + 10);
	            top.setPrefHeight(height1);
	            cell.setHeight(getMaxHeight() + (borderThickness * 2));

	            clampToBounds ();

	            moveToFront();
	        });

	        mid.setMinWidth( mWidth );
	        mid.setPrefWidth( width2 );
	        mid.setMinHeight( mHeight );
	        mid.setPrefHeight( height2 );
	        mid.textProperty().addListener((str, oldValue, newValue) ->
	        {
	            currText.setText(mid.getText());

	            width2 = UMath.maxOfDoubles(mWidth, currText.getLayoutBounds().getWidth() + 20);
	            updateWidths();

	            height2 = UMath.maxOfDoubles(mHeight, currText.getLayoutBounds().getHeight() * 1.08 + 10);
	            mid.setPrefHeight(height2);
	            cell.setHeight(getMaxHeight() + (borderThickness * 2));

	            clampToBounds ();

	            moveToFront();
	        });

	        btm.setMinWidth( mWidth );
	        btm.setPrefWidth( width3 );
	        btm.setMinHeight( mHeight );
	        btm.setPrefHeight( height3 );
	        btm.textProperty().addListener((str, oldValue, newValue) ->
	        {
	            currText.setText(btm.getText());

	            width3 = UMath.maxOfDoubles(mWidth, currText.getLayoutBounds().getWidth() + 20);
	            updateWidths();

	            height3 = UMath.maxOfDoubles(mHeight, currText.getLayoutBounds().getHeight() * 1.08 + 10);
	            btm.setPrefHeight(height3);
	            cell.setHeight(getMaxHeight() + (borderThickness * 2));
	            
	            clampToBounds ();

	            moveToFront();
	        });
	        
	        layout.widthProperty().addListener( (obs, oldValue, newValue) ->
	        {
	        	setX(x);
	        });
	        layout.heightProperty().addListener( (obs, oldValue, newValue) ->
	        {
	        	setY(y);
	        });

	        clampToBounds ();
	    }
	}
}