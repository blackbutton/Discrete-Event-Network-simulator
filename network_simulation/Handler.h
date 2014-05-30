

#ifndef __HANDLER_H__
#define __HANDLER_H__		

#include "CommonDefs.h"

class Event;
class Handler {
 public:
  virtual void Handle(Event*, Time_t) = 0;
};

#endif

