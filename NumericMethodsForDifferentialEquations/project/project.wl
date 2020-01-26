(* ::Package:: *)

SetDirectory[NotebookDirectory[]];
Import["thomas.wl"];

f[x_]:=(
	x^4 - 2*x^3 - 12*x^2 + 12*x
)

solve[f_,h_,x0_,X_]:=(
	n = Ceiling[(X - x0)/h];
	
	B0 = 1/h;
	C0 = (2+h^2)/(2*h);
	
	An = 0;
	Cn = -1;
	
	Ai = Bi = 1/(h^2);
	Ci = (2+h^2)/h^2;
	
	ListPlot[TriDiagThomas[f,Ai,Bi,Ci,B0,C0,An,Cn,h,x0,X]]
)

solve[f,0.001,0,1]







