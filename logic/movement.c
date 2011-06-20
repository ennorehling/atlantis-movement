#include "../platform.h"
#include <svc/unit.h>
#include <svc/game.h>
#include <svc/region.h>
#include <svc/cursor.h>

void do_movement(void) {
  struct region * r;
  void * rcur;
  icursor * ircur;

  for (rcur = svc.get_regions(&ircur); ircur->get(rcur, 1, (void**)&r); ircur->advance(&rcur, 1)) {
    struct unit * u;
    void * ucur;
    icursor * iucur;
  
    for (ucur = svc.regions->get_units(r, &iucur); iucur->get(ucur, 1, (void**)&u); iucur->advance(&ucur, 1)) {
      struct region * plan[32];
      struct region * here = r;
      int offset, n = -1;
      int steps;
      
      steps = svc.units->get_movement_speed(u);
      for (offset=0; steps>0 && n<0; offset+=32) {
        int i;

        n = svc.units->get_moves(u, plan, offset, 32);
        for (i=0;i!=((n<0)?32:n);++i) {
          struct region * next = plan[i];
          int cost = svc.regions->get_movement_cost(here, next);
          if (cost<0) {
            /* illegal move */
            steps = 0;
            break;
          }
          if (cost>steps) {
            /* journey's end */
            steps = 0;
            break;
          }
          steps -= cost;
          here = next;
        }
      }
      svc.regions->remove_unit(r, u);
      svc.regions->add_unit(here, u);
    }
  }
}
