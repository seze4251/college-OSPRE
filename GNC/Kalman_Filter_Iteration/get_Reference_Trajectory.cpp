#include "../../include/structs/Referance_Trajectory.h"

void get_Reference_Trajectory(const double X_ref[6], Reference_Trajectory ref_traj){
    // Need GNC data message time to interpolate ref_traj state
    
    // Declare state components
    X_ref[0] = ref_traj.X[?];
    X_ref[1] = ref_traj.Y[?]; 
    X_ref[2] = ref_traj.Z[?]; 
    X_ref[3] = ref_traj.VX[?]; 
    X_ref[4] = ref_traj.VY[?]; 
    X_ref[5] = ref_traj.VZ[?];   
}