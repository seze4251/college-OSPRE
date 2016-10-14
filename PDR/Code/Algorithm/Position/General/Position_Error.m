function [error] = Position_Error(r_E_SC_calc, r_E_SC_actual)
%%% Calculates the spacecraft position error.
%
% Inputs:   r_E_SC_calc     Calculated ECI position vector  (km)
%           r_E_SC_actual   Actual ECI position vector      (km)
%
% Author:   Cameron Maywood
% Created:  9/29/2016
% Modified: 9/29/2016
%
%%
error = norm(r_E_SC_actual - r_E_SC_calc);

end