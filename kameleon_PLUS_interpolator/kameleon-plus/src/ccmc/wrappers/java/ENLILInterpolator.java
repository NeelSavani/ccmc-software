/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package gov.nasa.gsfc.ccmc;

public class ENLILInterpolator extends Interpolator {
  private long swigCPtr;

  protected ENLILInterpolator(long cPtr, boolean cMemoryOwn) {
    super(CCMCJNI.ENLILInterpolator_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ENLILInterpolator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CCMCJNI.delete_ENLILInterpolator(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ENLILInterpolator(Model model) {
    this(CCMCJNI.new_ENLILInterpolator(Model.getCPtr(model), model), true);
  }

  public float interpolate(String variable, float r, float lat, float lon) {
    return CCMCJNI.ENLILInterpolator_interpolate__SWIG_0(swigCPtr, this, variable, r, lat, lon);
  }

  public float interpolate(String variable, float r, float lat, float lon, SWIGTYPE_p_float dr, SWIGTYPE_p_float dlat, SWIGTYPE_p_float dlon) {
    return CCMCJNI.ENLILInterpolator_interpolate__SWIG_1(swigCPtr, this, variable, r, lat, lon, SWIGTYPE_p_float.getCPtr(dr), SWIGTYPE_p_float.getCPtr(dlat), SWIGTYPE_p_float.getCPtr(dlon));
  }

  public float interpolate(int variableID, float r, float lat, float lon) {
    return CCMCJNI.ENLILInterpolator_interpolate__SWIG_2(swigCPtr, this, variableID, r, lat, lon);
  }

  public float interpolate(int variableID, float r, float lat, float lon, SWIGTYPE_p_float dr, SWIGTYPE_p_float dlat, SWIGTYPE_p_float dlon) {
    return CCMCJNI.ENLILInterpolator_interpolate__SWIG_3(swigCPtr, this, variableID, r, lat, lon, SWIGTYPE_p_float.getCPtr(dr), SWIGTYPE_p_float.getCPtr(dlat), SWIGTYPE_p_float.getCPtr(dlon));
  }

}
