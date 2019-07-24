package utility.test;

import static org.junit.Assert.*;

import org.junit.Test;

import utility.UMath;

public class UMathTest
{
	@Test
	public void testClampInBounds()
	{
		assertTrue (UMath.clamp(12.8, 12.4, 12.9) == 12.8);
	}
	
	@Test
	public void testClampAboveBounds()
	{
		assertTrue (UMath.clamp(-1.0, -25.4, -19.9) == -19.9);
	}
	
	@Test
	public void testClampBelowBounds()
	{
		assertTrue (UMath.clamp(5, 12, 745) == 12);
	}

	@Test
	public void testMaxOfDoubles()
	{
		assertTrue (UMath.maxOfDoubles(4, 7) == 7);
		assertTrue (UMath.maxOfDoubles(-2, -4) == -2);
	}

}
