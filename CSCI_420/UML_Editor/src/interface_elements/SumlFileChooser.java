package interface_elements;

import javafx.stage.Stage;
import javafx.stage.FileChooser;
import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SumlFileChooser
{
	private FileChooser fileChooser = new FileChooser();
	private Stage stage;

	/**
	* Constructs the FileChooser for the SUML application
	*/
	public SumlFileChooser(Stage stage)
	{
		this.stage = stage;
		fileChooser.setInitialDirectory(new File(System.getProperty("user.home")));
		fileChooser.getExtensionFilters().clear();
		fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("TXT", "*.txt"));
	}

	/**
	* @return String that is scanned from a file
	*/
	public String openFile()
	{
		fileChooser.setTitle("Open File");
		try
		{
			Scanner s = new Scanner(fileChooser.showOpenDialog(stage));
			String contents = s.useDelimiter("\\Z").next();
			s.close();
			return contents;
		}
		// Has to catch all since if the file is null it will send an exception 
		// 		so we want to return ""
		catch (Exception e)
		{
			return "";
		}
	}

	/**
	* Saves context of the String to a file. Will only overwrite if user selects to do so.
	*/
	public void saveFile(String context)
	{
		fileChooser.setTitle("Save File");
		File file = fileChooser.showSaveDialog(stage);
		if (file != null)
		{
			try
			{
				PrintWriter writer = new PrintWriter(file);
				writer.print(context);
				writer.close();
			}
			catch (FileNotFoundException e) 
			{
				System.out.println(e.getMessage());
			}
		}
	}
}