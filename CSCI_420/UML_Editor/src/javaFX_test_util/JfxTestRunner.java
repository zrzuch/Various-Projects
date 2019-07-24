package javaFX_test_util;

import java.util.concurrent.CountDownLatch;

import org.junit.runners.BlockJUnit4ClassRunner;
import org.junit.runners.model.InitializationError;

import com.sun.javafx.application.PlatformImpl;

// Credit for this class goes to Brian Blonski. Code can be found
// here: https://gist.github.com/bugabinga/a2703bfce0ca842d0e38
public class JfxTestRunner extends BlockJUnit4ClassRunner
{
  /**
   * Creates a test runner, that initializes the JavaFx runtime.
   *
   * @param klass The class under test.
   * @throws InitializationError if the test class is malformed.
   */
  public JfxTestRunner( final Class<?> klass ) throws InitializationError
  {
    super( klass );
    try
    {
      setupJavaFX();
    }
    catch ( final InterruptedException e )
    {
      throw new InitializationError( "Could not initialize the JavaFx platform." );
    }
  }

  private static void setupJavaFX() throws InterruptedException
  {
    final CountDownLatch latch = new CountDownLatch( 1 );

    // initializes JavaFX environment
    PlatformImpl.startup( () ->
    {
      /* No need to do anything here */
    } );

    latch.countDown();

    latch.await();
  }
}