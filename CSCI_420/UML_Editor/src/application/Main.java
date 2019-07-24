package application;

import interface_elements.SumlMenuBar;
import interface_elements.SumlToolBar;
import interface_elements.SumlWorkspace;
import interface_elements.SumlFileChooser;
import javafx.application.Application;
import javafx.scene.Cursor;
import javafx.scene.Scene;
import javafx.scene.control.ScrollPane;
import javafx.stage.Stage;
import javafx.scene.layout.VBox;
import javafx.scene.layout.BorderPane;
import javafx.geometry.Insets;
import javafx.scene.paint.Color;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;

public class Main extends Application 
{	
    public static double window_width = 1200;
    public static double window_height = 900;
    
    public static final double DEFAULT_WORKSPACE_WIDTH = 2000;
    public static final double DEFAULT_WORKSPACE_HEIGHT = 1000;

    public static Scene scene;
    public static Stage window;
    
    public static SumlMenuBar menuBar;
    public static SumlToolBar toolBar;
    public static SumlWorkspace workspace;
    public static SumlFileChooser fileChooser;

    public static ScrollPane workspaceViewport;

    public static void main(String[] args)
    {
        launch(args);
    }

    /**
    * Start is a method that is inherited from Application
    * that will be run after the initial window is setup, and
    * functions as the pseudo main function for JavaFX applications
    */
    @Override
    public void start(Stage primaryStage) throws Exception 
    {
        window = primaryStage;
        BorderPane layout = new BorderPane();
		scene = new Scene(layout, window_width, window_height);
        // Fixes cursor bug where the cursor stays in hand mode if dragging the arrow head past
        // the edge of the screen and letting go outside of the window and then returning.
        // Kinda hacky.
        scene.setOnMouseEntered(e -> {
        	workspaceViewport.setCursor(Cursor.DEFAULT);
        });
        fileChooser = new SumlFileChooser(window);
        
        menuBar = new SumlMenuBar (window);
        toolBar = new SumlToolBar ();

        VBox top = new VBox ();
        top.getChildren().addAll(menuBar.getMenuBar(), toolBar.getToolBar());
        
        workspaceViewport = new ScrollPane ();
        workspaceViewport.setPannable(true);
        workspaceViewport.setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        workspaceViewport.setVbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        workspaceViewport.setStyle("-fx-background:#555555; -fx-focus-color:transparent;");
        
        workspace = new SumlWorkspace (DEFAULT_WORKSPACE_WIDTH, DEFAULT_WORKSPACE_HEIGHT);
        workspaceViewport.setContent(workspace.getWorkspace());
        
        layout.setBackground(new Background(new BackgroundFill(Color.DARKGREY, CornerRadii.EMPTY, Insets.EMPTY)));
        layout.setTop(top);
        layout.setCenter(workspaceViewport);
        
        window.setScene(scene);
        window.setTitle("Simple UML");
        window.show();
    }
}