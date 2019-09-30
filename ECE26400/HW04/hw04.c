// There are some parts in the file that you need to modify, Please do
// not modify everything

// Modify only between the block which mentions what to modiy
// ===== DO NOT MODIFY BELOW THIS ======
#include "hw04.h"
  
void cleanup (FILE * fpin)
{
  fclose (fpin);
}  

// read the data, return true if success, false if fail
bool readData (FILE * fpin, DataPoint * *dp, int nval, int dim)
{
  int niter, diter;
  for (niter = 0; niter < nval; niter++)
    {
      for (diter = 0; diter < dim; diter++)
	{
	  if (fscanf (fpin, "%d", &dp[niter]->data[diter]) == 0)
	    {
	      return false;
	    }
	}
    }
  return true;
}

 
// write the output centroids to the file
// check for all the NULL before calling this function, it does not check
void writeCentroids (const char *filename, Centroid * *centroids, int kval)
{
  FILE * fpout = fopen (filename, "w");
  if (fpout == NULL)
    {
      fprintf (stderr, "File %s, cannot be open\n", filename);
      exit (1);
    }
  int kiter;
  // sort the centroids for ease of grading
  qsort (centroids, kval, sizeof (Centroid *), Centroid_cmp);
  for (kiter = 0; kiter < kval; kiter++)
    {
      Centroid_print (centroids[kiter], fpout);
    }
  fclose (fpout);
}

  
//===== DO NOT MODIFY ABOVE THIS ======

// Complete the below functions only, do not modify any other function.
  
#ifdef TEST_DIST
long long int
distance (const DataPoint * datapoint, const Centroid * centroid)
{
	int diter=0;
	long long int sum=0;
	int dim=datapoint->dimension;
	long long int tmp=0;
	
	// For each dimension, square difference
	for(diter=0;diter<dim;diter++)
	{
		tmp=((centroid->data[diter]) - (datapoint->data[diter]));
		sum += (tmp*tmp);
	}
	return sum;
}

#endif	
   
#ifdef TEST_CLOSESTCENTROID
int closestCentroid (int kval, DataPoint * datapoint, Centroid * *centroids)
{
	
  	int mindex;
  	int MAX_KVAL = kval;
  	long long int c_dis = 0;
  	long long int p_dis = 0;
  	int kiter=1;

	// Check if the prev > current centroid in iteration
  	p_dis = distance(datapoint,centroids[0]);
  	mindex = 0;
  	for(kiter=1;kiter<MAX_KVAL;kiter++)
  	{
	  	c_dis = distance(datapoint,centroids[kiter]);
	 	if((long long int)c_dis < (long long int)p_dis)
	  	{
			// If true, change the min to return
		 	mindex = kiter;
		  	p_dis = c_dis;
	  	}
  	}  
  	return mindex;
}
#endif	
    
#ifdef TEST_KMEAN
void kmean (int kval, int nval, DataPoint * *datapoints, Centroid * *centroids)
{
	int MAX_KVAL = kval;
	int kiter = 0;
	int niter = 0;
	int convergence = -1;
	int prev_cluster;
	int closest_centroid;
	

	// Reset all centroids
	for(kiter=0;kiter<MAX_KVAL;kiter++)
	{
		Centroid_reset(centroids[kiter]);
	}

	// Assign datapoints to random centroid cluster
	for(niter=0;niter<nval;niter++)
	{
		int clu = rand() % kval;
		datapoints[niter]->cluster = clu;
		Centroid_addPoint(centroids[clu],datapoints[niter]);
	}

	// Find centroid centers
	for(kiter=0;kiter<MAX_KVAL;kiter++)
	{	
		Centroid_findCenter(centroids[kiter]);
	}

	while(convergence != 0)
	{	
		// For each data point, find the index of the closest centroid
		convergence = 0;
		for(niter=0;niter<nval;niter++)
		{
			prev_cluster = datapoints[niter]->cluster;
			closest_centroid = closestCentroid(kval,datapoints[niter],centroids);	
			if((int)prev_cluster != (int)closest_centroid)
			{
				datapoints[niter]->cluster = closest_centroid;
				convergence += 1;
			}
		}

		// Reset all centroids
		for(kiter=0;kiter<MAX_KVAL;kiter++)
		{
			Centroid_reset(centroids[kiter]);
		}

		// Go through each datapoint again and add this datapoint to its centroid
		for(niter=0;niter<nval;niter++)
		{	
			Centroid_addPoint(centroids[datapoints[niter]->cluster],datapoints[niter]);
		}
		
		// Find updated centers
		for(kiter=0;kiter<MAX_KVAL;kiter++)
		{	
			Centroid_findCenter(centroids[kiter]);
		}
	}
	return;
}
#endif	
  
/*===== DO NOT MODIFY BELOW THIS ======*/ 
int
main (int argc, char * *argv)
{
  
  // argv[1]: name of input file
  // argv[2]: value of k/ number of centroids
  // argv[3]: name of output file
  if (argc < 4)
    {
      fprintf (stderr, "argc is %d, not 4\n", argc);
      return EXIT_FAILURE;
    }

  // opening file to read the data points from
  FILE * fpin = fopen (argv[1], "r");
  if (fpin == NULL)
    {
      fprintf (stderr, "fopen %s fail\n", argv[1]);
      return EXIT_FAILURE;
    }
   
  // convert long to int
  int kval = (int) strtol (argv[2], NULL, 10);
  if (kval <= 0)
    {
      fprintf (stderr, "kval is %d, must be positive\n", kval);
      return EXIT_FAILURE;
    }
  // control the random number sequence
  int randseed = 1729;	// any integer will do, DO NOT CHANGE
  srand (randseed);
    
  // getting number of datapoints
  int nval;
  fscanf (fpin, "%d", &nval);
  if (nval < kval)
    {
      fprintf (stderr, "nval= %d must be greater than kval = %d\n", nval,
	       kval);
      cleanup (fpin);
      return EXIT_FAILURE;
    }
   
  // getting dimensions of the data from the file
  int dim;
  fscanf (fpin, "%d", &dim);
  if (dim < 2)
    {
      fprintf (stderr, "nval= %d must be greater than kval = %d\n", nval,
	       kval);
      cleanup (fpin);
      return EXIT_FAILURE;
    }
    
  // allocate memory for the data points
  DataPoint * *datapoint_array = DataPoint_createArray (nval, dim);
  if (datapoint_array == NULL)
    {
      printf ("Error in creating datapoint array\n");
      cleanup (fpin);
      return EXIT_FAILURE;
    }
  
  // allocate memory for array of centroids
  Centroid * *centroids = Centroid_createArray (kval, dim);	
  if (centroids == NULL)
    {
      printf ("Error in creating centroids array\n");
      DataPoint_freeArray (datapoint_array, nval);
      cleanup (fpin);
      return EXIT_FAILURE;
    }
   
  // read the data from the file
  if (readData (fpin, datapoint_array, nval, dim) == false)
    {
      printf ("Error in reading data array\n");
      cleanup (fpin);
      DataPoint_freeArray (datapoint_array, nval);
      return EXIT_FAILURE;
    }
     
  // calling kmean function to find the cetroids
  kmean (kval, nval, datapoint_array, centroids);

  //writing those centroids to the file
  writeCentroids (argv[3], centroids, kval);
  
  // free all the allocated spaces
  DataPoint_freeArray (datapoint_array, nval);
  Centroid_freeArray (centroids, kval);
  cleanup (fpin);
  return EXIT_SUCCESS;
}


