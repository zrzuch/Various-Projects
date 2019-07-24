package interface_elements;

import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.VPos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class WorkspaceSizePopup
{
	private Stage stage;
	
	final private int textFieldWidth = 100;
	
	/**
	* Construct a window that allows the user to change the workspace size
	*/
	public WorkspaceSizePopup (Stage owner, SumlWorkspace workspace)
	{
		stage = new Stage ();
		GridPane pane = new GridPane ();
		Scene scene = new Scene (pane);
		
		Text widthLabel = new Text ("Width:");
		GridPane.setConstraints(widthLabel, 0, 0);
		
		TextField widthField = new TextField ();
		widthField.setMaxWidth(textFieldWidth);
		widthField.setText(Double.toString(workspace.getWidth()));
		GridPane.setConstraints(widthField, 1, 0);
		
		Text heightLabel = new Text ("Height:");
		GridPane.setConstraints(heightLabel, 2, 0);
		
		TextField heightField = new TextField ();
		heightField.setMaxWidth(textFieldWidth);
		heightField.setText(Double.toString(workspace.getHeight()));
		GridPane.setConstraints(heightField, 3, 0);
		
		Button submit = new Button ("Submit");
		GridPane.setConstraints(submit, 3, 1, 1, 1, HPos.RIGHT, VPos.CENTER);
		submit.setOnAction(e ->
		{
			double width = workspace.getWidth();
			double height = workspace.getHeight();
			try
		    {
				width = Double.valueOf(widthField.getText()).doubleValue();
	    	} 
	    	catch (NumberFormatException nfe)
			{
	           System.out.println ("Could not parse workspace width.");
			}
			try
			{
				height = Double.valueOf(heightField.getText()).doubleValue();
			} 
			catch (NumberFormatException nfe)
			{
	           System.out.println ("Could not parse workspace height.");
			}
			workspace.setSize(width, height);
			close ();
		});
		
		pane.setOnKeyPressed(e ->
		{
			if (e.getCode() == KeyCode.ENTER)
			{
				submit.fire();
			}
		});
		
		pane.setPadding(new Insets (15));
		pane.setHgap(20);
		pane.setVgap(10);
		pane.getChildren().addAll(widthLabel, widthField, heightLabel, heightField, submit);
		
		stage.setScene(scene);
		stage.initOwner(owner);
		stage.initModality(Modality.WINDOW_MODAL);
		stage.setTitle("Change Workspace Size");
		stage.setResizable(false);
	}
	
	/**
	* Show the stage
	*/
	public void show ()
	{
		stage.show();
	}
	
	/**
	* Close the stage
	*/
	public void close ()
	{
		stage.close();
	}
	
}
