package uml_elements.test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import javafx.collections.ObservableList;
import javafx.scene.Node;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Rectangle;

import uml_elements.UMLContainer;
import javaFX_test_util.JfxTestRunner;


@RunWith (JfxTestRunner.class)
public class UMLContainerTest
{

	private Pane layout;
	private UMLContainer umlContainer;
	
	@Before
	public void setUpLayout ()
	{
		layout = new Pane ();
		umlContainer = new UMLContainer (layout);
	}
	
	@Test
	public void testIsEmptyAfterCtor()
	{
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testAddForRectangle()
	{
		umlContainer.add(40, 40);
		
		int rectCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Rectangle)
			{
				++rectCount;
			}
		}
		assertTrue (rectCount == 1);
	}
	
	@Test
	public void testAddForTextAreas()
	{
		umlContainer.add(32, 109);
		
		int textCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof TextArea)
			{
				++textCount;
			}
		}
		assertTrue (textCount == 3);
	}
	
	@Test
	public void testRemove()
	{
		umlContainer.add(0, 0);
		assertTrue (!layout.getChildren().isEmpty());
		umlContainer.remove(0);
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testClear()
	{
		umlContainer.add(0, 0);
		umlContainer.add(2, 25);
		assertTrue (!layout.getChildren().isEmpty());
		umlContainer.clear();
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testInitialeSize()
	{
		assertTrue (umlContainer.size() == 0);
	}
	
	@Test
	public void testSizeAfterAdds()
	{
		umlContainer.add(0, 0);
		assertTrue (umlContainer.size() == 1);
		umlContainer.add(2, 2);
		assertTrue (umlContainer.size() == 2);
	}
	
	@Test
	public void testSizeAfterRemove()
	{
		umlContainer.add(0, 0);
		umlContainer.remove(0);
		assertTrue (umlContainer.size() == 0);
	}
	
	@Test
	public void testSizeAfterClear()
	{
		umlContainer.add(0, 0);
		umlContainer.add(0, 0);
		umlContainer.clear();
		assertTrue (umlContainer.size() == 0);
	}
	
	@Test
	public void testToString()
	{
		umlContainer.add(0, 0);
		umlContainer.add(0, 0);
		
		TextArea t00 = umlContainer.topAt (0);
		t00.setText("testingTop");
		TextArea t01 = umlContainer.midAt (0);
		t01.setText("testing1\n\nmoreTest!");
		
		TextArea t10 = umlContainer.topAt (1);
		t10.setText("\n");
		TextArea t12 = umlContainer.btmAt (1);
		t12.setText("super\nduper\n");

		assertTrue (umlContainer.toString().equals(
				"0.0 0.0\n" +
			    "[\n" +
				"testingTop\n" +
			    "]\n" +
				"[\n" +
			    "testing1\n" +
				"\n" +
			    "moreTest!\n" +
			    "]\n" +
				"[\n" +
			    "\n" +
				"]\n" +
			    
			    "0.0 0.0\n" +
			    "[\n" +
			    "\n" +
			    "]\n" +
				"[\n" +
			    "\n" +
			    "]\n" +
				"[\n" +
			    "super\n" +
				"duper\n" +
				"]\n"
		));
	}

}
