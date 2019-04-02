// phys3071 as11 melsom 42593249

/*_____________________________________________________________________________
Description: This program simulates traffic flow.

Inputs: The user is required to enter the maximum velocity (v_max), the maximum
density of cars (rho_max), the time steps (delta_t), the spatial steps 
(delta_x), and for how long the simulation should run for (t_final). All of 
these values are doubles.

Calculations: The program solves, for each time step, the spatial values. The 
main function steps over the time values, and calls a function to solve the 
positional values using the FTCS scheme with the Lax-Friedrich approximation.
For each time step, the maximum density is found.

outputs: The program will output the nth row of the calculations for time(n) is
and integer value. At this time step, the  program will also output to terminal 
the maximum density from the nth row.

Compiled as gcc as11-melsom-42593249.c -o as11 -Wall -lm
_____________________________________________________________________________*/

// Included Libraries ---------------------------------------------------------
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function Prototypes --------------------------------------------------------
void spatial(double rho_max, double v_max, double delta_x, 
             double delta_t, double t_old[], double t_new[], int n);

// Begin main function --------------------------------------------------------
int main () {
  double v_max, rho_max, delta_t, delta_x, t_final; // User defined values.
  int x_steps; // Number of steps to be taken.
  int j; // Generic counter.
  int n; // nth row counter.
  double t_position; // Temporal position.
  double x_position; // Spatial position.
  
  printf("This program will now calculate the flow of traffic where the "
          "density function (rho) evolves in time.\nThe program also displays "
          "the maximum densities for particular time steps.\n\n");

  // User input section -------------------------------------------------------
  printf("Please enter the maximum velocity (v_max): ");
  scanf("%lf", &v_max);
  printf("Please enter the maximum density (rho_max): ");
  scanf("%lf", &rho_max);
  printf("Please enter the time step size (Delta_t): ");
  scanf("%lf", &delta_t);
  printf("Please enter the grid size (Delta_x): ");
  scanf("%lf", &delta_x);
  printf("Please enter the end time for integration (t_fin): ");
  scanf("%lf", &t_final);
  
  x_steps= (int) ceil(4.0/delta_x);
  double t_old[x_steps];
  double t_new[x_steps];
  
  // Setting the initial conditions.
  for (j= 1; j< x_steps; j++) {
    x_position= j* delta_x;
    if (x_position< 2.0) 
          (t_old[j]= 0.5* rho_max* sin((M_PI/2.0)* x_position));
    else (t_old[j]= 0.0);
  // printf("%lf\t%lf\t%lf\n",x_position, sin(M_PI/(2.0*x_position)), t_old[j]);
  }
  
  j=0;
  n= 0;
  do {
    spatial(rho_max, v_max, delta_x, delta_t, t_old, t_new, n);

    // Update the old position with the last calculated values.
    for (j=0; j< x_steps; j++) (t_old[j]= t_new[j]);

    n++; // nth row counter.
    t_position = n* delta_t; // To avoid error build up from adding doubles.
  } while (t_position<= t_final); 
  
  return (EXIT_SUCCESS);
}


// FUNCTIONS ------------------------------------------------------------------

// Solves over the spatial dimension for a given time step.
void spatial(double rho_max, double v_max, double delta_x, 
             double delta_t, double t_old[], double t_new[], int n) {
  
  int j_max, j= 1; // Row element counter for the nth row.
  int max_loc= 0; // Stores the location of the maximum of the row.
  double x_position= 0.0; // The current spatial position
  int output_val= (int) 1.0/delta_t; // Used to check if at a row output value.
  double v; // Velocity to be calculated to rho.
  
  t_new[0]= 0.0; // Setting the boundary condition.
  
  FILE *out; // output file
  char filename[100]= "rho-";  // Beginning of file name.
  char filemiddle[100];        // Middle of file name, to be assigned
  char endname[100]= "-j.dat"; // End of file name
  sprintf(filemiddle,"%d",n);  // Assign integer to char - middle of file name.
  strcat(filename, filemiddle);// Concatenate first 2 of 3 strings
  strcat(filename, endname);   // Concatenate last 2 of 3 strings.
  
  do {
    // Checks if the latest value is the largest in the row so far.
    if (t_old[j]> t_old[max_loc]) (max_loc= j);
    
    // Calculates values of rho ^{n+1} over all 
    t_new[j] = (1.0/2.0)* (t_old[j-1] + t_old[j+1]) // Eq (5) from 
               - ((v_max* delta_t)/(2.0* delta_x))* // Assignment 11
                 (t_old[j+1]- t_old[j-1])*
                 (1.0- ((2.0* t_old[j])/(rho_max)));
    
    j++; // Increment j counter.
    x_position= j* delta_x; //recalculate x_position.
  
  } while (x_position<= 4.0); // keep calculating elements while x < 4
  t_new[j+1]= t_old[j];
  
  j_max= j+1; // Record the maximum value for j;
  
  // Printing condition for if t_position is whole number.
  if (n% output_val== 0) {
    v= v_max* (1.0- t_old[max_loc]/ rho_max); 
    printf("rho_max for %dth time step is rho^%d_%d = %lf \t v(rho_max) = %lf\n" // Print the maximum x
            , n, n, max_loc, t_old[max_loc], v);         // value of nth row
   
    // Print to file.
    out= fopen(filename, "w"); // Create the file to be written to
    for(j= 0; j< j_max; j++) { // Populate the file.
      fprintf(out, "%d\t%lf\n", j, t_old[j]/*variables*/ );
    }
    fclose(out);
  }
}
