/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package gov.nasa.gsfc.ccmc;

public class Position {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Position(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Position obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CCMCJNI.delete_Position(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setC0(float value) {
    CCMCJNI.Position_c0_set(swigCPtr, this, value);
  }

  public float getC0() {
    return CCMCJNI.Position_c0_get(swigCPtr, this);
  }

  public void setC1(float value) {
    CCMCJNI.Position_c1_set(swigCPtr, this, value);
  }

  public float getC1() {
    return CCMCJNI.Position_c1_get(swigCPtr, this);
  }

  public void setC2(float value) {
    CCMCJNI.Position_c2_set(swigCPtr, this, value);
  }

  public float getC2() {
    return CCMCJNI.Position_c2_get(swigCPtr, this);
  }

  public Position() {
    this(CCMCJNI.new_Position(), true);
  }

}
