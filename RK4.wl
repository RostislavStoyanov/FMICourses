(* ::Package:: *)

RK4[x0_,u0_,X_,f_,h_] := (
	n = Ceiling[(X-x0)/h];
	y = Table[0,{n+1}];
	t = Table[x0+i*h,{i,0,n+1}];
	y[[1]] = u0;
	For[i = 1,i<n+1,i++,
		currX = t[[i]];
		currY = y[[i]];
		k1 = h*f[currX,currY];
		k2 = h*f[currX + h/2,currY + k1/2];
		k3 = h*f[currX + h/2,currY + k2/2];
		k4 = h*f[currX + h,currY + k3];
		y[[i+1]] = currY + (k1/6) + (k2/3) + (k3/3) + (k4/6)
	];
	ListPlot[Table[{t[[i]],y[[i]]},{i,0,n}]]
)	
	F[x_,y_]:=(
	(-x+Sqrt [(x*x+(4*y*y))]/(2*y))
)

RK4[-0.5,0.1,0.5,F,0.001]



