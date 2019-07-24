/**
 * To use JavaFX objects, JavaFX must be initialized, and
 * all controls must be modified by the thread that initialized JavaFX
 * internally. So we must force JUnit to run on the same thread as the one
 * created by JavaFX.
 */
package javaFX_test_util;