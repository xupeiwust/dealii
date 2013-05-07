//----------------------------  chunk_sparse_matrix_iterator_03.cc  ---------------------------
//    $Id$
//    Version: $Name$ 
//
//    Copyright (C) 2004, 2005, 2013 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------  chunk_sparse_matrix_iterator_03.cc  ---------------------------


// test setting some elements and reading them back from a non-const chunk
// matrix iterator

#include "../tests.h"
#include <deal.II/lac/chunk_sparse_matrix.h>    
#include <fstream>
#include <iomanip>


void test (const unsigned int chunk_size)
{
  deallog << "Chunk size: " << chunk_size << std::endl;
  ChunkSparsityPattern sp (5,5,3,chunk_size);
  for (unsigned int i=0; i<5; ++i)
    for (unsigned int j=0; j<5; ++j)
      if (((i+2*j+1) % 3 == 0)
          ||
          (i==j))
        sp.add (i,j);
  sp.compress ();

  ChunkSparseMatrix<double> m(sp);
  for (unsigned int i=0; i<5; ++i)
    for (unsigned int j=0; j<5; ++j)
      if (((i+2*j+1) % 3 == 0)
          ||
          (i==j))
        m.set (i,j, i*j);
  
  ChunkSparseMatrix<double>::iterator i = m.begin();
  for (; i!=m.end(); ++i)
    {
      deallog << i->row() << ' ' << i->column() << ' '
              << i->value() << std::endl;
      if (((i->row()+2*i->column()+1) % 3 == 0)
          ||
          (i->row()==i->column()))
        {
          Assert (std::fabs(i->value() - i->row()*i->column()) < 1e-14,
                  ExcInternalError());
        }
      else
        Assert (i->value() == 0, ExcInternalError());
    }

  deallog << "OK" << std::endl;
}



int main ()
{
  std::ofstream logfile("chunk_sparse_matrix_iterator_03/output");
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);

  try
    {
      const unsigned int chunk_sizes[] = { 1, 2, 4, 5, 7 };
      for (unsigned int i=0;
	   i<sizeof(chunk_sizes)/sizeof(chunk_sizes[0]);
	   ++i)
	test (chunk_sizes[i]);
    }
  catch (std::exception &exc)
    {
      deallog << std::endl << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      deallog << "Exception on processing: " << std::endl
		<< exc.what() << std::endl
		<< "Aborting!" << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      
      return 1;
    }
  catch (...) 
    {
      deallog << std::endl << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      deallog << "Unknown exception!" << std::endl
		<< "Aborting!" << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      return 1;
    };
}
