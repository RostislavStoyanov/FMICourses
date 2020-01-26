(* ::Package:: *)

h = 0.01;
list = List[0.1];
i = 1;
currVal = list[[i]]+h*list[[i]]*Sqrt[4-2*list[[i]]];
While[currVal<=2,
	AppendTo[list,currVal];
	i++;
	currVal=list[[i]]+h*list[[i]]*Sqrt[4-2*list[[i]]]];
ListPlot[Table[{j*h, list[[j]]},{j, 1, i}]]
