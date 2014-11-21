// $Id: unpack.h,v 2.10 2004/05/28 19:22:04 o Exp $
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

#include "../../pack/dbspecs2.h"

struct   hit_st
         {
           Z32 obj[FIELDS];
         };

typedef  struct hit_st hit;


extern hit* lookup ();
extern hit* gethits ();

extern hit* unpack ();
extern hit* directory ();
extern hit* decompress ();


