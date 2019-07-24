package interface_elements;

import application.Main;
import interface_elements.SumlToolBar.EditMode;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import uml_elements.UMLContext;

public class SumlWorkspace
{
	private Pane pane;
	private UMLContext container;
	
	/**
	* Constructs the Pane and Container for the SUML application
	*/
	public SumlWorkspace (double width, double height)
	{
		pane = new Pane ();
		pane.setMinWidth(width);
		pane.setMaxWidth(width);
		pane.setMinHeight(height);
		pane.setMaxHeight(height);
		pane.setBackground(new Background (
				new BackgroundFill (Color.WHITE, CornerRadii.EMPTY, Insets.EMPTY)));
		
        EventHandler<MouseEvent> consumeUnlessMouse = e ->
        {
        	if (Main.toolBar.currentEditMode () != EditMode.MOUSE)
        	{
        		e.consume();
        	}
        };

        // Disallow deleting boxes unless in mouse mode
        pane.addEventFilter(MouseEvent.MOUSE_PRESSED, consumeUnlessMouse);
        // Disallow dragging boxes and arrows allowed unless in mouse mode
        pane.addEventFilter(MouseEvent.MOUSE_DRAGGED, consumeUnlessMouse);
        // Centers clicking logic will be based on the current mode we are in
        container = new UMLContext(pane);
        pane.setOnMouseClicked( e ->
        {
        	if (e.getX() > 0 && e.getX() < pane.getWidth() &&
        		e.getY() > 0 && e.getY() < pane.getHeight())
        	{
	        	if (Main.toolBar.currentEditMode() == EditMode.ADD_CLASS)
	        	{
	        		container.addUML(e.getX(), e.getY());
	        		e.consume();
	        	}
	        	else if (Main.toolBar.currentEditMode() == EditMode.ADD_ARROW)
	        	{
	        		container.addArrow(Main.toolBar.currentConnector(), e.getX(), e.getY());
	        		e.consume();
	        	}
        	}
        });
	}
	
	/**
	* Set size for the pane
	*/
	public void setSize (double width, double height)
	{
		pane.setMinSize(width, height);
		pane.setMaxSize(width, height);
		container.width = width;
		container.height = height;
	}
	
	/**
	* Set width for the pane
	*/
	public void setWidth (double width)
	{
		pane.setMinWidth(width);
		pane.setMaxWidth(width);
		container.width = width;
	}
	
	/**
	* Set height for the pane
	*/
	public void setHeight (double height)
	{
		pane.setMinHeight(height);
		pane.setMaxHeight(height);
		container.height = height;
	}

	/**
	* Clears the UML context
	*/
	public void reset()
	{
		container.reset();
		setWidth (Main.DEFAULT_WORKSPACE_WIDTH);
		setHeight (Main.DEFAULT_WORKSPACE_HEIGHT);
	}
	
	/**
	* @return double width of the pane
	*/
	public double getWidth ()
	{
		return pane.getWidth();
	}
	
	/**
	* @return double height of the pane
	*/
	public double getHeight ()
	{
		return pane.getHeight();
	}
	
	/**
	* @return Pane which is the layout for the center of the SUML application
	*/
	public Pane getWorkspace ()
	{
		return pane;
	}

	/**
	* @return String of the UML context
	*/
	public String getContext()
	{
		return container.toString();
	}

	/**
	* Create a new UML context from a String
	*/
	public void create(String context)
	{
		if (context != "")
		{
			container.create(context);
			setWidth(container.width);
			setHeight(container.height);
		}
	}
}