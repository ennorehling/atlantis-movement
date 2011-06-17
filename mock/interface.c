#include "interface.h"
#include <svc/unit.h>
#include <svc/region.h>
#include "unit.h"

struct iunit mock_units = {
  &u_create,
  &u_id,
  &u_region,
  &u_region_set
};

struct iregion mock_regions = {
  &r_create,
};
