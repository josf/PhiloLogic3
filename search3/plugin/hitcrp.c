// $Id: hitcrp.c,v 2.11 2004/05/28 19:22:08 o Exp $
// philologic 2.8 -- TEI XML/SGML Full-text database engine
// Copyright (C) 2004 University of Chicago
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Affero General Public License as published by
// Affero, Inc.; either version 1 of the License, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// Affero General Public License for more details.
// 
// You should have received a copy of the Affero General Public License
// along with this program; if not, write to Affero, Inc.,
// 510 Third Street, Suite 225, San Francisco, CA 94107 USA.

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef HITDEF_H
  #include "hitdef.h"
#endif

#ifndef HITCMP_H
  #include "hitcmp.h"
#endif

#ifndef HITCRP_H
  #include "hitcrp.h"
#endif

extern Z32 h2h_cmp_cooc(Z32 *, Z32 *, hitdef *, Z32);
extern Z32 m2m_cmp_cooc(Z32 *, Z32 *, hitdef *, Z32);
extern Z32 h_size_cooc(hitdef *, N8);

Z32 hit_crp_args ( hitdef *h, Z32 *m, Z32 *f, Z8 *arg, Z8 *crpfile )
{
  Z8  *c;
  FILE *cfp;
  Z32 ret;
  Z32 success; 

  struct stat  cstat;

  *f = atol ( arg ); 

  if ( !*f ) 
    return -1; 

  (void) stat(crpfile, &cstat);


  if ( cfp = fopen(crpfile, "r") )
    {
      ret = cstat.st_size / (sizeof(Z32)*(*f)); 
      success = fread (m, sizeof(Z32), ret*(*f), cfp);

      fclose(cfp);
    }
  else
    return -1; 
  
  h->levels->context = *f; 

  /*h->levels->h2h_cmp_func =    (*h2h_cmp_cooc);*/
  h->levels->h2m_cmp_func =    (*h2h_cmp_cooc);
  /*h->levels->m2m_cmp_func =    (*m2m_cmp_cooc);*/
 
  /*h->levels->cntxt_cmp_func =  (*h2h_cmp_cooc);*/
 
  /*  h->levels->hitsize_func =    (*h_size_cooc); */
 
  h->levels->distance = 0;
  /*h->levels->n_real   = 0;*/
 
  h->levels->opt      = NULL;

  return ret; 
}




