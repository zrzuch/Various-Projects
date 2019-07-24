package uml_elements.test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import javafx.collections.ObservableList;
import javafx.scene.Node;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Polygon;
import uml_elements.ArrowContainer;
import javaFX_test_util.JfxTestRunner;


@RunWith (JfxTestRunner.class)
public class ArrowContainerTest
{

	private Pane layout;
	private ArrowContainer arrContainer;
	
	@Before
	public void setUpLayout ()
	{
		layout = new Pane ();
		arrContainer = new ArrowContainer (layout);
	}
	
	@Test
	public void testIsEmptyAfterCtor()
	{
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testAddAssociationForSolidLine()
	{
		arrContainer.add("Association", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 0);
	}
	
	@Test
	public void testAddAssociationForOpenTriangle()
	{
		arrContainer.add("Association", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 2);
		assertTrue (p.getPoints().size() == 6);
		assertTrue (p.getFill() == Color.TRANSPARENT);
	}
	
	@Test
	public void testAddDependencyForDashedLine()
	{
		arrContainer.add("Dependency", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 2);
	}
	
	@Test
	public void testAddDependencyForOpenTriangle()
	{
		arrContainer.add("Dependency", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 2);
		assertTrue (p.getPoints().size() == 6);
		assertTrue (p.getFill() == Color.TRANSPARENT);
	}
	
	@Test
	public void testAddGeneralizationForSolidLine()
	{
		arrContainer.add("Generalization", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 0);
	}
	
	@Test
	public void testAddGeneralizationForClosedTriangle()
	{
		arrContainer.add("Generalization", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 0);
		assertTrue (p.getPoints().size() == 6);
		assertTrue (p.getFill() == Color.TRANSPARENT);
	}
	
	@Test
	public void testAddRealizationForDashedLine()
	{
		arrContainer.add("Realization", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 2);
	}
	
	@Test
	public void testAddRealizationForClosedTriangle()
	{
		arrContainer.add("Realization", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 0);
		assertTrue (p.getPoints().size() == 6);
		assertTrue (p.getFill() == Color.TRANSPARENT);
	}
	
	@Test
	public void testAddAggregationForSolidLine()
	{
		arrContainer.add("Aggregation", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 0);
	}
	
	@Test
	public void testAddAggregationForTransparentDiamond()
	{
		arrContainer.add("Aggregation", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 0);
		assertTrue (p.getPoints().size() == 8);
		assertTrue (p.getFill() == Color.TRANSPARENT);
	}
	
	@Test
	public void testAddCompositionForSolidLine()
	{
		arrContainer.add("Composition", 40, 40);
		
		Line l = null;
		int lineCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Line)
			{
				l = (Line) children.get(i);
				++lineCount;
			}
		}
		assertTrue (lineCount == 1);
		assertTrue (l.getStrokeDashArray().size() == 0);
	}
	
	@Test
	public void testAddCompositionForBlackDiamond()
	{
		arrContainer.add("Composition", 40, 40);
		
		Polygon p = null;
		int polyCount = 0;
		ObservableList<Node> children = layout.getChildren(); 
		for (int i = 0; i < children.size(); ++i)
		{
			if (children.get(i) instanceof Polygon)
			{
				p = (Polygon) children.get(i);
				++polyCount;
			}
		}
		assertTrue (polyCount == 1);
		assertTrue (p.getStrokeDashArray().size() == 0);
		assertTrue (p.getPoints().size() == 8);
		assertTrue (p.getFill() == Color.BLACK);
	}
	
	@Test
	public void testRemove()
	{
		arrContainer.add("Association", 0, 0);
		assertTrue (!layout.getChildren().isEmpty());
		arrContainer.remove(0);
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testClear()
	{
		arrContainer.add("Association", 0, 0);
		arrContainer.add("Realization", 0, 0);
		assertTrue (!layout.getChildren().isEmpty());
		arrContainer.clear();
		assertTrue (layout.getChildren().isEmpty());
	}
	
	@Test
	public void testToString()
	{
		arrContainer.add("Dependency", 0, 0);
		arrContainer.add("Realization", 0, 0);
		arrContainer.add("Association", 0, 0);
		arrContainer.add("Generalization", 0, 0);
		arrContainer.add("Association", 0, 0);
		
		assertTrue (arrContainer.toString().equals(
			"0.0 0.0 50.0 0.0 Dependency\n" +
			"0.0 0.0 50.0 0.0 Realization\n" +
			"0.0 0.0 50.0 0.0 Association\n" +
			"0.0 0.0 50.0 0.0 Generalization\n" +
			"0.0 0.0 50.0 0.0 Association\n"
		));
	}
}
