package interface_elements;

import javafx.geometry.Insets;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ToggleButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.control.Tooltip;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import uml_elements.ArrowContainer;

public class SumlToolBar
{
	public static enum EditMode {
		MOUSE, ADD_CLASS, ADD_ARROW, DELETE_MODE
	}
	private EditMode currentMode = EditMode.MOUSE;
	
	private HBox toolBar;
	
	private ToggleGroup editingModes;
	private ToggleButton mouseModeButton, addClassModeButton, addArrowModeButton, deleteModeButton;
	private ChoiceBox<String> arrowTypeSelector;
	
	private String currentConnector = ArrowContainer.ArrowType[0];
	
    /**
    * Constructs a HBox with additional ToggleGroup Functionality
    */
	public SumlToolBar() 
    {
		toolBar = new HBox ();
		
        // Set up toolBar formatting
        toolBar.setPadding( new Insets(5));
        toolBar.setSpacing(10);
        toolBar.setBackground(new Background (
    		new BackgroundFill (Color.LIGHTGREY, CornerRadii.EMPTY, Insets.EMPTY)));
        toolBar.setBorder(new Border (new BorderStroke (
        		Color.GREY, Color.GREY, Color.GREY, Color.GREY,
        		BorderStrokeStyle.SOLID, BorderStrokeStyle.NONE, BorderStrokeStyle.SOLID,
        		BorderStrokeStyle.NONE, CornerRadii.EMPTY, BorderStroke.THIN, Insets.EMPTY)));
        
        editingModes = new ToggleGroup ();
        
        // Set up the 'mouse mode' ToggleButton
        ImageView mouseModeImage = new ImageView(new Image ("mouse.png"));
        mouseModeImage.setFitWidth(20);
        mouseModeImage.setFitHeight(20);
        
        mouseModeButton = new ToggleButton("", mouseModeImage);
        mouseModeButton.setToggleGroup(editingModes);
        mouseModeButton.setTooltip(new Tooltip ("Mouse mode"));
        mouseModeButton.setSelected(true);
        mouseModeButton.setOnMouseClicked(e ->
        {
        	mouseModeButton.setSelected(true);
        	currentMode = EditMode.MOUSE;
        });
        
        // Set up the 'delete mode' ToggleButton
        ImageView deleteModeImage = new ImageView(new Image ("RedX.png"));
        deleteModeImage.setFitWidth(22);
        deleteModeImage.setFitHeight(22);
        
        deleteModeButton = new ToggleButton ("", deleteModeImage);
        deleteModeButton.setToggleGroup(editingModes);
        deleteModeButton.setTooltip(new Tooltip ("Delete UML Element"));
        deleteModeButton.setOnMouseClicked(e ->
        {
            deleteModeButton.setSelected(true);
            currentMode = EditMode.DELETE_MODE;
        });
        
        // Set up the 'add class mode' ToggleButton
        ImageView addClassModeImage = new ImageView(new Image ("AddClass.png"));
        addClassModeImage.setFitWidth (20);
        addClassModeImage.setFitHeight (20);
        
        addClassModeButton = new ToggleButton ("", addClassModeImage);
        addClassModeButton.setToggleGroup(editingModes);
        addClassModeButton.setTooltip(new Tooltip ("Add class mode"));
        addClassModeButton.setOnMouseClicked(e ->
        {
        	addClassModeButton.setSelected(true);
        	currentMode = EditMode.ADD_CLASS;
        });
        
        // Set up the 'add arrow mode' ToggleButton
        ImageView addArrowModeImage = new ImageView(new Image ("AddArrow.png"));
        addArrowModeImage.setFitWidth (22);
        addArrowModeImage.setFitHeight (22);
        
        addArrowModeButton = new ToggleButton ("", addArrowModeImage);
        addArrowModeButton.setToggleGroup(editingModes);
        addArrowModeButton.setTooltip(new Tooltip ("Add arrow mode"));
        addArrowModeButton.setOnMouseClicked(e ->
        {
        	addArrowModeButton.setSelected(true);
        	currentMode = EditMode.ADD_ARROW;
        });
        
        // Set up the connectorSelector ChoiceBox
        arrowTypeSelector = new ChoiceBox<>();
        arrowTypeSelector.getItems().addAll(ArrowContainer.ArrowType);
        arrowTypeSelector.setValue( ArrowContainer.ArrowType[0] );
        arrowTypeSelector.getSelectionModel().selectedItemProperty()
            .addListener(( v, oldValue, newValue ) -> 
        {
            if ( oldValue != newValue ) currentConnector = newValue;
        });
        arrowTypeSelector.setPrefHeight(20);
        arrowTypeSelector.setTooltip(new Tooltip ("Arrow type"));
        
        toolBar.getChildren().addAll(mouseModeButton, deleteModeButton, addClassModeButton,
        		addArrowModeButton, arrowTypeSelector);
	}
	
    /**
    * @return HBox that holds the tool bar buttons and choice box
    */
	public HBox getToolBar ()
	{
		return toolBar;
	}
	
    /**
    * @return String of current connector
    */
	public String currentConnector ()
	{
		return currentConnector;
	}
	
    /**
    * @return EditMode current toggle mode enum
    */
	public EditMode currentEditMode ()
	{
		return currentMode;
	}
}
