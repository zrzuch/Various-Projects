package utility;

public class UMath {
	
    /**
    * @return double within min <= x <= max
    */
    public static double clamp(double x, double min, double max)
    {
        if ( x < min || max < min) return min;
        if ( x > max ) return max;
        return x;
    }
    
    /**
    * @return double max
    */
    public static double maxOfDoubles( double d1 , double d2 )
    {
        if ( d1 >= d2 ) return d1;
        else            return d2;
    }
}
