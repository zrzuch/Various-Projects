package uml_elements;

import javafx.scene.layout.Pane;
import uml_elements.ArrowContainer;
import uml_elements.UMLContainer;
import java.util.Scanner;
import java.util.Vector;

public class UMLContext
{
	private UMLContainer classes;
	private ArrowContainer arrows;
	public double width;
	public double height;

	/**
	* Constructs the containers
	*/
	public UMLContext(Pane pane)
	{
		classes = new UMLContainer(pane);
		arrows = new ArrowContainer(pane);
		width = pane.getMaxWidth();
		height = pane.getMaxHeight();
	}

	/**
	* Adds a default Arrow to the Pane of the desired arrowType and at point x and y
	*/
	public void addArrow(String arrowType, double x, double y)
	{
		arrows.add(arrowType, x, y);
	}

	/**
	* Adds an Arrow to the Pane of the desired arrowType and from point begin to end
	*/
	public void addArrow(String arrowType, double beginX, double beginY, double endX, double endY)
	{
		arrows.add(arrowType, beginX, beginY, endX, endY);
	}

	/**
	* Adds a UMLLayout to the Pane at coordinates x and y
	*/
	public void addUML(double x, double y)
	{
		classes.add(x,y);
	}

	/**
	* Clears its containers
	*/
	public void reset()
	{
		arrows.clear();
		classes.clear();
	}

	/**
	* @return String which is the String of the arrows and classes combined
	*/
	public String toString()
	{
		return width + " " + height + "\n" + arrows.toString() + classes.toString();
	}

	/**
	* Resets and adds UMLLayouts and Arrows to their containers based on a String
	*/
	public void create(String context)
	{
		reset();
		if (!context.equals(""))
		{
			int i = 0;
			Scanner scanner = new Scanner(context);
			double params[] = new double[4];
			String arrowType = "";
			Scanner lineScanner = new Scanner(scanner.nextLine());
			
			width = lineScanner.nextDouble ();
			height = lineScanner.nextDouble ();

			// Begin Processing Arrow Data
			while (scanner.hasNextLine())
			{
				lineScanner = new Scanner(scanner.nextLine());
				for (i = 0; i < 4; ++i)
				{
					if (lineScanner.hasNextDouble()) 
					{
						params[i] = lineScanner.nextDouble();
					}
					else 
					{
						break;
					}
				}
				if (lineScanner.hasNext())
				{
					arrowType = lineScanner.next();
					++i;
					addArrow(arrowType, params[0], params[1], params[2], params[3]);
				}
				else 
				{
					break;
				}
			}

			// Begin Processing UML Data
			if (i == 2)
			{
				do
				{
					Vector<String> linesTop = new Vector<String>();
					Vector<String> linesMid = new Vector<String>();
					Vector<String> linesBtm = new Vector<String>();
					addUML(params[0], params[1]);
					String line = scanner.nextLine();
					if (scanner.hasNextLine() && line.equals("["))
					{
						do
						{
							line = scanner.nextLine();
							if (!line.equals("]"))
							{
								linesTop.add(line);
							}
							else
							{
								if (scanner.hasNextLine())
								{
									line = scanner.nextLine();
								}
								if (linesTop.size() > 0)
								{
									String content = linesTop.elementAt(0);
									for (int ind = 1; ind < linesTop.size(); ++ind)
									{
										content += "\n" + linesTop.elementAt(ind);
									}
									classes.topAt(classes.size() - 1).setText(content);
								}
								break;
							}
						}
						while (scanner.hasNextLine());
					}
					else
					{
						break;
					}

					if (scanner.hasNextLine() && line.equals("["))
					{
						do
						{
							line = scanner.nextLine();
							if (!line.equals("]"))
							{
								linesMid.add(line);
							}
							else
							{
								if (scanner.hasNextLine())
								{
									line = scanner.nextLine();
								}
								if (linesMid.size() > 0)
								{
									String content = linesMid.elementAt(0);
									for (int ind = 1; ind < linesMid.size(); ++ind)
									{
										content += "\n" + linesMid.elementAt(ind);
									}
									classes.midAt(classes.size() - 1).setText(content);
								}
								break;
							}
						}
						while (scanner.hasNextLine());
					}
					else
					{
						break;
					}

					if (scanner.hasNextLine() && line.equals("["))
					{
						do
						{
							line = scanner.nextLine();
							if (!line.equals("]"))
							{
								linesBtm.add(line);
							}
							else
							{
								if (linesBtm.size() > 0)
								{
									String content = linesBtm.elementAt(0);
									for (int ind = 1; ind < linesBtm.size(); ++ind)
									{
										content += "\n" + linesBtm.elementAt(ind);
									}
									classes.btmAt(classes.size() - 1).setText(content);
								}	
								break;
							}
						}
						while (scanner.hasNextLine());
					}
					else
					{
						break;
					}

					// Get Next Positions
					if (scanner.hasNextLine())
					{
						lineScanner = new Scanner(scanner.nextLine());
						if (lineScanner.hasNext())
						{
							for (i = 0; i < 2; ++i)
							{
								params[i] = lineScanner.nextDouble();
							}
						}
						else
						{
							break;
						}

						if (i != 2)
						{
							break;
						}
					}
				} 
				while (scanner.hasNextLine());
			}
			lineScanner.close();
			scanner.close();
		}
	}
}