// Filename: graphicsPipe.cxx
// Created by:  mike (09Jan97)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#include "graphicsPipe.h"
#include "graphicsWindow.h"
#include "graphicsBuffer.h"
#include "config_display.h"
#include "mutexHolder.h"

TypeHandle GraphicsPipe::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::Constructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
GraphicsPipe::
GraphicsPipe() :
  _lock("GraphicsPipe")
{
  // Initially, we assume the GraphicsPipe is valid.  A derived class
  // should set this to false if it determines otherwise.
  _is_valid = true;

  // A derived class must indicate the kinds of GraphicsOutput objects
  // it can create.
  _supported_types = 0;

  _display_width = 0;
  _display_height = 0;
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::Copy Constructor
//       Access: Private
//  Description: Don't try to copy GraphicsPipes.
////////////////////////////////////////////////////////////////////
GraphicsPipe::
GraphicsPipe(const GraphicsPipe &) {
  _is_valid = false;
  nassertv(false);
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::Copy Assignment Operator
//       Access: Private
//  Description: Don't try to copy GraphicsPipes.
////////////////////////////////////////////////////////////////////
void GraphicsPipe::
operator = (const GraphicsPipe &) {
  nassertv(false);
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::Destructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
GraphicsPipe::
~GraphicsPipe() {
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::get_preferred_window_thread
//       Access: Public, Virtual
//  Description: Returns an indication of the thread in which this
//               GraphicsPipe requires its window processing to be
//               performed: typically either the app thread (e.g. X)
//               or the draw thread (Windows).
////////////////////////////////////////////////////////////////////
GraphicsPipe::PreferredWindowThread 
GraphicsPipe::get_preferred_window_thread() const {
  return PWT_draw;
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::make_device
//       Access: Public, Virtual
//  Description: Creates a new device for the pipe. Only DirectX uses
//               this device, for other api's it is NULL.
////////////////////////////////////////////////////////////////////
PT(GraphicsDevice) GraphicsPipe::
make_device(void *scrn) {
  display_cat.error() 
    << "make_device() unimplemented by " << get_type() << "\n";
  return NULL;
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::close_gsg
//       Access: Protected, Virtual
//  Description: This will be called in the draw thread (the same
//               thread in which the GSG was created via make_gsg,
//               above) to close the indicated GSG and free its
//               associated graphics objects just before it is
//               destructed.  This method exists to provide a hook for
//               the graphics pipe to do any necessary cleanup, if
//               any.
////////////////////////////////////////////////////////////////////
void GraphicsPipe::
close_gsg(GraphicsStateGuardian *gsg) {
  if (gsg != (GraphicsStateGuardian *)NULL) {
    gsg->close_gsg();
  }
}

////////////////////////////////////////////////////////////////////
//     Function: GraphicsPipe::make_output
//       Access: Protected, Virtual
//  Description: Creates a new window on the pipe, if possible.
////////////////////////////////////////////////////////////////////
PT(GraphicsOutput) GraphicsPipe::
make_output(const string &name,
            const FrameBufferProperties &fb_prop,
            const WindowProperties &win_prop,
            int flags,
            GraphicsStateGuardian *gsg,
            GraphicsOutput *host,
            int retry,
            bool &precertify) {
  display_cat.error()
    << get_type() << " cannot create buffers or windows.\n";
  return NULL;
}

