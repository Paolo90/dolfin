// Copyright (C) 2003 Johan Hoffman and Anders Logg.
// Licensed under the GNU GPL Version 2.

#ifndef __FUNCTION_LIST_H
#define __FUNCTION_LIST_H

#include <dolfin/FunctionPointer.h>
#include <dolfin/Array.h>
#include <dolfin/ShapeFunction.h>
#include <dolfin/ElementFunction.h>

namespace dolfin {
  
  class Map;
  
  class FunctionList {
  public:
    
    FunctionList();
    
    // Addition of functions
    static int add(function f);
    
    // Specification of derivatives wrt reference coordinates
    static void set(int id,
		    FunctionSpace::ElementFunction ddX,
		    FunctionSpace::ElementFunction ddY,
		    FunctionSpace::ElementFunction ddZ,
		    FunctionSpace::ElementFunction ddT);
    
    // Update derivatives with current map
    static void update(const FunctionSpace::ShapeFunction& v, const Map& map);
	 
    // Size of list
    static unsigned int size();
    
    // Evaluation
    static real eval(int id, real x, real y, real z, real t);
    
    // Derivatives wrt real coordinates
    static const FunctionSpace::ElementFunction& ddx(int id);
    static const FunctionSpace::ElementFunction& ddy(int id);
    static const FunctionSpace::ElementFunction& ddz(int id);
    static const FunctionSpace::ElementFunction& ddt(int id);
    
    // Derivatives wrt reference coordinates
    static const FunctionSpace::ElementFunction& ddX(int id);
    static const FunctionSpace::ElementFunction& ddY(int id);
    static const FunctionSpace::ElementFunction& ddZ(int id);
    static const FunctionSpace::ElementFunction& ddT(int id);
    
  private:
    
    class FunctionData {
    public:
      
      FunctionData();
      FunctionData(function f);
      
      // 
      void operator= (int zero);
      bool operator! () const;
      
      function f; // Function pointer
      
      FunctionSpace::ElementFunction ddx; // Derivative wrt dx
      FunctionSpace::ElementFunction ddy; // Derivative wrt dy
      FunctionSpace::ElementFunction ddz; // Derivative wrt dz
      FunctionSpace::ElementFunction ddt; // Derivative wrt dt
      
      FunctionSpace::ElementFunction ddX; // Derivative wrt dX
      FunctionSpace::ElementFunction ddY; // Derivative wrt dY
      FunctionSpace::ElementFunction ddZ; // Derivative wrt dZ
      FunctionSpace::ElementFunction ddT; // Derivative wrt dT
    };
    
    static void init();
    
    static Array<FunctionData> list;
    static int _size;
    static bool initialised;
    
  };
  
}

#endif
