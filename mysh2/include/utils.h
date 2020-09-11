/**********************************************************************
 * Copyright (C) Jaewon Choi <jaewon.james.choi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *********************************************************************/
#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>

#define FREE_2D_ARRAY(n, arr) \
  for (int i = 0; i < (n); ++i) {\
    free((arr)[(i)]);\
  }\
  free((arr));

#endif // UTILS_H_
