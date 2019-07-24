package interface_elements;

import application.Main;
import javafx.geometry.Insets;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public final class SumlMenuBar
{
	private MenuBar menuBar;
	
	/**
	* Constructs the MenuBar for the SUML application
	*/
	public SumlMenuBar(Stage owner)
	{
		menuBar = new MenuBar ();
		
		Menu fileMenu = new Menu ("File");
        Menu editMenu = new Menu ("Edit");
        MenuItem changeWorkspaceSizeMenuItem = new MenuItem ("Change Workspace Size");
        changeWorkspaceSizeMenuItem.setOnAction(e ->
        {
        	WorkspaceSizePopup changeWorkspaceSizePopup = new WorkspaceSizePopup (owner, Main.workspace);
        	changeWorkspaceSizePopup.show ();
        });
        editMenu.getItems().add(changeWorkspaceSizeMenuItem);

        MenuItem newMenuItem = new MenuItem ("New");
        newMenuItem.setOnAction(e ->
        {
        	Main.workspace.reset();
        });

        MenuItem saveMenuItem = new MenuItem ("Save");
        saveMenuItem.setOnAction(e ->
        {
        	Main.fileChooser.saveFile(Main.workspace.getContext());
        });

        MenuItem openMenuItem = new MenuItem ("Open");
        openMenuItem.setOnAction(e ->
        {
        	Main.workspace.create(Main.fileChooser.openFile());
        });

        fileMenu.getItems().addAll(newMenuItem, saveMenuItem, openMenuItem);
        // Setting up menuBar formatting
        menuBar.setBackground(new Background (
        		new BackgroundFill (Color.SILVER, CornerRadii.EMPTY, Insets.EMPTY)));
        menuBar.getMenus().addAll (fileMenu, editMenu);
	}

	/**
	* @return MenuBar the menu along the top of the screen (file and edit)
	*/
	public MenuBar getMenuBar()
	{
		return menuBar;
	}
}
