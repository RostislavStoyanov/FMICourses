(* ::Package:: *)

(*\:041c\:0435\:0442\:043e\:0434 \:043d\:0430 \:0434\:044f\:0441\:043d\:0430\:0442\:0430 \:043f\:0440\:043e\:0433\:043e\:043d\:043a\:0430/\:0422\:043e\:043c\:0430\:0441*)
TriDiagThomas[f_,Ai_,Bi_,Ci_,B0_,C0_,An_,Cn_,h_,x0_,X_]:= (
	n = Ceiling[(X - x0)/h];
	alpha = Table[0,{n+1}];
	beta = Table[0,{n+2}];
	t = Table[x0+i*h,{i,0,n+1}];
	
	alpha[[1]] = B0/C0;
	beta[[1]] = -(f[t[[1]]]/C0);
	
	For[i = 1,i<=n,i++,
	currDenom = Ci-(Ai*alpha[[i]]);
	alpha[[i+1]] = Bi/currDenom;
	beta[[i+1]] = (Ai*beta[[i]] - f[t[[i]]])/currDenom];
	
	beta[[n+2]] = (An*beta[[n+1]]-f[t[[n+1]]])/(Cn-(An*alpha[[n+1]]));
	
	y = Table[0,{n+1}];
	y[[n+1]] = beta[[n+2]];
	For[i = n,i>0,i--,
	y[[i]] = (alpha[[i+1]]*y[[i+1]])+beta[[i+1]]];
	
	Table[{t[[i+1]], y[[i+1]]},{i, 0, n}]
	
)
