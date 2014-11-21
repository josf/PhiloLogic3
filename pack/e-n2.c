// $Id: e-n2.c,v 2.10 2004/05/28 19:22:02 o Exp $
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

#include <stdio.h>

#include "c.h"

#include "dbspecs0c.h" 

#include "bitpack3.h"

char *GUIDEFILE = "conc.guide";
char *DIRFILE   = "conc.dir"; 

FILE *fp3, *fp4;

 

Z32      lcl_blk_counter = 1;
Z32      conc_counter = 0;
Z32      blk_counter = 0;
N64	 offset = 0;

Z32      frst_hit_flag = 1;
Z32      file_end_flag = 0;

Z32	 j;
 
char str[LINESIZE];            
char str_last[LINESIZE]="sOmEBiZzAreStRinG";
char *s;


void main()
   {

     fp3 = fopen (GUIDEFILE, "w");  /* information about the offsets,
				       block numbers, freqs, etc. 
				    */
     
     fp4 = fopen (DIRFILE, "w");    /* and this one for directories
				       of encoded blocks.   	 
				    */
     
      while ( !file_end_flag )
	{
	  if ( !gets (str) )
	    { 
	      fprintf (fp3, " %d %d\n", conc_counter, lcl_blk_counter);
	    
	      endsymbol_out(); 
	      if (free_space % 32) load();

	      file_end_flag++;
	    }
	  else 
	    {
	      s = index (str, ' ') + 1;
	      str [ s - str - 1 ] = '\0';
	      
	      readhit (s, &l); 


	      if ( strcmp( str, str_last ))   /* this is a new word */
		{
		  if ( !frst_hit_flag ) 
		    {
		      endsymbol_out(); 
	      
		      if (free_space % 32) load();
			    
		      fprintf (fp3, " %d %d\n", conc_counter, lcl_blk_counter);
		    }  

		  strcpy (str_last, str);         

		  offset += ( lcl_blk_counter - 1 ) * BLK_SIZE;
		  offset += word_counter*4 > BLK_SIZE ? BLK_SIZE : word_counter * 4;

		  word_counter = 0;
		  
		  fprintf (fp3, "%s %llu", str, offset);  /* absolute offset */ 
		  
		  fprintf (fp4, "%d", l.i[0] + negs[0]);

		  for ( j = 1; j < FIELDS; j++ )
		    fprintf (fp4, " %d", l.i[j] + negs[j]);

		  fprintf (fp4, "\n");

		  conc_counter = lcl_blk_counter = 1;
		      
		  frst_hit_flag = 0;     

		}
	      else    /* this is still an occurence of the same word; */
		{
		  conc_counter++;
		      
 /*
   Now we will see whether the Encoding has been successfull, i.e.
   whether there was enough space in the block; if not -- we'll simply 
   have to start a new block and dump the current hit into our directory 
   as a first hit for the next block.
 */

		  if ( Encoding (&l) ) 
		    {
		      word_counter = 0;
		      free_space = 32;
		      code_buffer = 0;
		      
		      lcl_blk_counter++;
		      
		      fprintf (fp4, "%d", l.i[0] + negs[0]);

		      for ( j = 1; j < FIELDS; j++ )
			fprintf (fp4, " %d", l.i[j] + negs[j]);
		      
		      fprintf (fp4, "\n");
		    }
		}
	    }

	} /* main encoding loop */
              
     exit(0);                      
                  
  } 


