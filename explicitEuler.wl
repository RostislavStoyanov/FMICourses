(* ::Package:: *)

ExplicitEuler[x0_,u0_,X_,f_,h_]:=(
	n = Ceiling[(X-x0)/h];
	y = Table[0,{n+1}];
	t = Table[x0+i*h, {i,0,n+1}];
	y[[1]] = u0;
	For[i = 1,i<n+1,i++,
	y[[i+1]] = y[[i]] + h*f[t[[i]],y[[i]]];
	];
	g1 = ListPlot[Table[{t[[i+1]], y[[i+1]]},{i, 0, n}]]
)

F[x_,y_]:=(
	(-x+Sqrt [(x*x+(4*y*y))]/(2*y))
)
ExplicitEuler[-0.5,0.1,0.5,F,0.001]











(* ::InheritFromParent:: *)
(*$Failed*)
