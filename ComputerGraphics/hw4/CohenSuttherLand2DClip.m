o1 = CalculateOutCode(x1,y1,XMin,XMax,YMin,YMax);
o2 = CalculateOutCode(x2,y2,XMin,XMax,YMin,YMax);

while(1)
    if(~(bitor(o1,o2)))
        break;
    end
    
    if(bitand(o1,o2))
        shouldDraw = false;
        break;
    end
    
    if(o1==0)
        currOut = o2;
    else
        currOut = o1;
    end
    
    if(bitand(currOut,8))
        currX = x1 + (x2-x1)*(YMax-y1)/(y2-y1);
        currY=YMax;
    elseif(bitand(currOut,4))
        currX = x1 + (x2-x1)*(YMin-y1)/(y2-y1);
        currY=YMin;
    elseif(bitand(currOut,2))
        currY = y1 + (y2-y1)*(XMax-x1)/(x2-x1);
        currX=XMax;
    else
        currY = y1 + (y2-y1)*(XMin-x1)/(x2-x1);
        currX=XMin;
    end
    
    if(currOut == o1)
        x1 = currX;
        y1 = currY;
        o1 = CalculateOutCode(x1,y1,XMin,XMax,YMin,YMax);
    else
        x2 = currX;
        y2 = currY;
        o2 = CalculateOutCode(x1,y1,XMin,XMax,YMin,YMax);
    end
end