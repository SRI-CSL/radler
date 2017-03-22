/*
 * Created on Oct, 2014
 * @author: Léonard Gérard leonard.gerard@sri.com
 *
 * Single entry point to RADL libraries
 */

#pragma once

// Other headers of the RADL library
#include "radl_time.h"
#include "radl_flags.h"

// Internal definitions (not to meant to be used by users)
#include "radl__lib.h"


/* Pointer to the current RADL node description */
#define RADL_THIS RADL_MODULE->RADL_NODE_NAME

/* To be used like printf */
#define RADL_PRINT(...)  RADL__PRINT_HELPER(__VA_ARGS__, "")
