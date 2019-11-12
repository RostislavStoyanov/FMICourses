M = BersenhamLine(X1,X1+RVal,Y1+RVal,Y1,M,color);
M = BersenhamLine(X1-RVal,X1+RVal,Y1,Y1,M,color);
try
    M = BersenhamLine(X1,X1-RVal,Y1-RVal,Y1,M,color);
catch
end
xVal=0;
yVal=RVal;
dVal=2-2*RVal;
while (1)
    if (dVal>-yVal)
        yVal=yVal-1;
        dVal=dVal+1-2*yVal;
    end
    if (dVal<=xVal)
        xVal=xVal+1;
        dVal=dVal+1+2*xVal;
    end
    if (yVal<xVal) 
        break; 
    end;
    EightSymmetricModified;
end